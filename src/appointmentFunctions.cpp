#pragma warning( disable : 4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fileFunctions.h"
#include "formFunctions.h"
#include "accountFunctions.h"
#include <iostream>
#include "appointmentFunctions.h"
#include <time.h>

/*
	Cover your eyes, this is stupid.
*/
char* fixTime(char *t) {
	char *tmpStr = (char*)malloc(sizeof(char) * 6);

	tmpStr[0] = t[0];
	tmpStr[1] = t[1];
	tmpStr[2] = ':';
	tmpStr[3] = t[5];
	tmpStr[4] = t[6];
	tmpStr[5] = '\0';

	return tmpStr;
}

/*
	This functions returns an timestamp from a date and time
	char *date          takes a date as "yyyy-mm-dd"
	char *time			takes a time as "hh:mm"
	returns             date as timestamp (comparable with >, <, ==, ...)
*/
time_t getTimestamp(char *date, char *time) {
	tm tmdate = { 0 };
	tmdate.tm_year = atoi(&date[0]) - 1900;
	tmdate.tm_mon = atoi(&date[5]) - 1;
	tmdate.tm_mday = atoi(&date[8]);
	tmdate.tm_hour = atoi(&time[0]);
	tmdate.tm_min = atoi(&time[2]);
	time_t timestamp = mktime(&tmdate);

	return timestamp;
}

/*
	This is the compare function for qsort

	Usage:
		Pass the following as last parameter for qsort:
		int(*compare)(const void *, const void*)
*/
int compare(const void *p1, const void *p2) {
	time_t t1 = getTimestamp(((Appointment*)p1)->date, ((Appointment*)p1)->time);
	time_t t2 = getTimestamp(((Appointment*)p2)->date, ((Appointment*)p2)->time);

	if (t1 < t2) return -1;
	if (t1 > t2) return 1;
	return 0;
}

bool appointmentAdd(const char *fname, int aUserID, char *postData) {
	Appointment* appointments = NULL;
	Appointment* tmpAppointment = NULL;
	size_t amount = 0;

	char *aDate = NULL;
	char *aTime = NULL;
	char *aDescription = NULL;

	aDate = getValueOfKey(postData, (char*)"date");
	if (aDate == NULL) {
		return false;
	}

	aTime = getValueOfKey(postData, (char*)"time");
	if (aTime == NULL) {
		free(aDate);
		return false;
	}

	aDescription = getValueOfKey(postData, (char*)"description");
	if (aDescription == NULL) {
		free(aDate);
		free(aTime);
		return false;
	}


	// Read all appointments
	appointments = (Appointment*)readStructs(fname, &amount, sizeof(Appointment));

	if (appointments == NULL) {
		// Create first Appointment
		appointments = (Appointment*)malloc((amount + 1) * sizeof(Appointment));
		
		appointments[amount].appointmentId = 0;
		appointments[amount].userId = aUserID;
		strcpy(appointments[amount].date, aDate);
		strcpy(appointments[amount].time, aTime);
		strcpy(appointments[amount].description, aDescription);
	} else {
		// Expand array and add new appointment
		tmpAppointment = (Appointment*)realloc(appointments, (amount + 1) * sizeof(Appointment));

		if (tmpAppointment == NULL) {
			free(appointments);
			free(aDate);
			free(aTime);
			free(aDescription);
			return false;
		}

		appointments = tmpAppointment;

		appointments[amount].appointmentId = appointments[amount - 1].appointmentId + 1;
		appointments[amount].userId = aUserID;
		strcpy(appointments[amount].date, aDate);
		strcpy(appointments[amount].time, aTime);
		strcpy(appointments[amount].description, aDescription);
	}

	// Quick fix for time
	char *tmpTime = NULL;
	tmpTime = fixTime(appointments[amount].time);

	if (tmpTime == NULL) {
		return false;
	}

	strcpy(appointments[amount].time, tmpTime);
	free(tmpTime);


	writeStructs((char*)fname, appointments, amount + 1, sizeof(Appointment));
	
	free(aDate);
	free(aTime);
	free(aDescription);

	return true;
}

bool appointmentChange(const char *fname, int aUserID, char *postData) {
	Appointment *appointments;
	size_t amount = 0;

	char *aDate = NULL;
	char *aTime = NULL;
	char *aDescription = NULL;
	char *caID = NULL;
	int aID = -1;

	aDate = getValueOfKey(postData, (char*)"date");
	if (aDate == NULL) {
		return false;
	}

	aTime = getValueOfKey(postData, (char*)"time");
	if (aTime == NULL) {
		free(aDate);
		return false;
	}

	aDescription = getValueOfKey(postData, (char*)"description");
	if (aDescription == NULL) {
		free(aDate);
		free(aTime);
		return false;
	}

	caID = getValueOfKey(postData, (char*)"id");
	if (caID == NULL) {
		free(aDate);
		free(aTime);
		free(aDescription);
		return false;
	}
	aID = atoi(caID);
	free(caID);

	appointments = (Appointment*)readStructs(fname, &amount, sizeof(Appointment));

	if (appointments == NULL) {
		free(aDate);
		free(aTime);
		free(aDescription);
		return false;
	}

	for (size_t i = 0; i < amount; i++) {
		if (appointments[i].userId == aUserID && appointments[i].appointmentId == aID) {
			strcpy(appointments[i].date, aDate);
			strcpy(appointments[i].time, aTime);
			strcpy(appointments[i].description, aDescription);

			// Quick fix for time
			char *tmpTime = NULL;
			tmpTime = fixTime(appointments[i].time);

			if (tmpTime == NULL) {
				return false;
			}

			strcpy(appointments[i].time, tmpTime);
			free(tmpTime);

			break;
		}
	}

	writeStructs((char*)fname, appointments, amount, sizeof(Appointment));

	free(aDate);
	free(aTime);
	free(aDescription);

	return true;
}

bool deleteAppointment(const char *fname, int aUserID, int aID) {
	Appointment *appointments = NULL;
	Appointment *tmpAppointment = NULL;
	size_t amount = 0;
	
	appointments = (Appointment*)readStructs(fname, &amount, sizeof(Appointment));
	
	if (appointments == NULL) {
		return false;
	}

	if (amount <= 1) {
		free(appointments);
		return remove(fname) == 0;
	}

	// Find position of appointment
	int appointmentPos = -1;
	for (int i = 0; i < amount; i++) {
		if (appointments[i].userId == aUserID && appointments[i].appointmentId == aID) {
			appointmentPos = i;
			break;
		}
	}

	if (appointmentPos == -1) {
		free(appointments);
		return false;
	}

	// Move content to the left
	for (int i = appointmentPos; i < (amount - 1); i++) {
		appointments[i].userId = appointments[i + 1].userId;
		appointments[i].appointmentId = appointments[i + 1].appointmentId;
		strcpy(appointments[i].date, appointments[i + 1].date);
		strcpy(appointments[i].time, appointments[i + 1].time);
		strcpy(appointments[i].description, appointments[i + 1].description);
	}

	// Decrease array size by 1
	tmpAppointment = (Appointment*)realloc(appointments, (amount - 1) * sizeof(Appointment));

	if (tmpAppointment == NULL) {
		free(appointments);
		return false;
	}

	appointments = tmpAppointment;
	
	writeStructs(fname, appointments, amount - 1, sizeof(Appointment));

	free(appointments);

	return true;
}
