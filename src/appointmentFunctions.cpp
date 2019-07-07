#pragma warning( disable : 4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fileFunctions.h"
#include "formFunctions.h"
#include "accountFunctions.h"
#include <iostream>
#include "appointmentFunctions.h"

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
