#pragma warning( disable : 4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fileFunctions.h"
#include "formFunctions.h"
#include "accountFunctions.h"
#include <iostream>
#include "appointmentFunctions.h"

const char* fileTplError = "templates/error.html";
const char* fileTplDeleted = "templates/delete.html";
char *htmlTemplatePart = NULL;
char *htmlTemplatePart3 = NULL;

//bool appointmentHTMLoutput(const char fname, char* user) {
//	Appointment *outputHTML = NULL;
//	size_t size = 0;
//	outputHTML = (Appointment*)readStructs(&fname, &size, sizeof(Appointment));
//
//	for (size_t i = 0; i < size; i++) {
//		if (strcmp((char*)outputHTML[i].userId,user)){
//			htmlTemplatePart = getTemplate(fileTplError);
//			return false;
//		}
//		if(!strcmp((char*)outputHTML[i].userId,user)){
//			for(int i = 0; i <= size; i++) {
//				while (!strcmp((char*)outputHTML[i].userId, user)); {
//					std::cout << "Content-type:text/html\r\n\r\n";
//					std::cout << "<tr>";
//					std::cout << "<td>" << outputHTML[size].appointmentId << "< / td>";
//					std::cout << "<td>" << outputHTML[size].date << "< / td>";
//					std::cout << "<td>" << outputHTML[size].time << "< / td>";
//					std::cout << "<td>" << outputHTML[size].description << ";< / td>";
//					std::cout << "<td><button><i class = 'fa fa - pencil'>ändern< / i>< / button><button><i class = 'fa fa - trash'>löschen< / i>< / button>< / td>";
//					std::cout << "< / tr>";
//				}
//			}
//		}
//	
//	}
//}

//bool makeAppointmentID(const char fname){
//	size_t size = 0;
//	Appointment* makeApp = 0;
//
//	makeApp = (Appointment*)readStructs(&fname, &size, sizeof(Appointment));
//
//	int tmp = 0;
//	//search for the highest appointmentId
//	for (size_t i = 0; i < size; i++) {
//		if (tmp < makeApp[i].appointmentId) {
//			tmp = makeApp[i].appointmentId;
//		}
//		//give the last(new) appointment an unique ID
//		else if (tmp == makeApp[i].appointmentId) {
//			tmp + 1;
//			makeApp[i+1].appointmentId = makeApp[i+1].appointmentId = tmp;
//			writeStructs(&fname, makeApp, i + 1, sizeof(Appointment));
//			return true;
//		}
//		else {
//			htmlTemplatePart = getTemplate(fileTplError);
//			return false;
//		}
//	}
//}
bool getDataApp(char* data) {
	char* sdate = NULL;
	char* stime = NULL;
	char* sdescription = NULL;
	char* sappointmentId = NULL;
	char* user = NULL;

	user = getValueOfKey(data, (char*)"username");
	sdate = getValueOfKey(data, (char*)"date");
	stime = getValueOfKey(data, (char*)"time");
	sdescription = getValueOfKey(data, (char*)"description");
	sappointmentId = getValueOfKey(data, (char*)"appointmentId");

	return false;
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
		}
	}

	writeStructs((char*)fname, appointments, amount + 1, sizeof(Appointment));

	free(aDate);
	free(aTime);
	free(aDescription);

	return true;
}
bool deleteAppoi(const char fname, char* sappointmentId) {

	Appointment* deleteApp;
	Appointment* tmpdeleteApp;
	Appointment* tmpdeleteApp2;
	size_t size = 0;
	int givenAppID = *sappointmentId; 

	deleteApp = (Appointment*)readStructs(&fname, &size, sizeof(Appointment));

	for (size_t i = 0; i < size; i++) {
		if (!strcmp((char*)deleteApp[size].appointmentId, (char*)givenAppID)) {
			return false;
		}
		else if (strcmp((char*)deleteApp[size].appointmentId, (char*)givenAppID)) {
			tmpdeleteApp = (Appointment*)readStructs(&fname, &size, sizeof(Appointment));
			tmpdeleteApp2 = (Appointment*)readStructs(&fname, &size, sizeof(Appointment));
			/*
			tmp[n] =n+1;
			m[n] = n+1;
			m[n-1] = tmp[2];
			*/
			if (size == sizeof(Appointment)) {
				htmlTemplatePart3 = getTemplate(fileTplDeleted);
				return true;
			}
			else if(size < sizeof(Appointment)) {
				for (size_t i = 0; i = size; i ++ ) {
					tmpdeleteApp2[i].appointmentId = tmpdeleteApp2[size + 1].appointmentId;
					tmpdeleteApp[i].appointmentId = tmpdeleteApp[size + 1].appointmentId;
					//tmpdeleteApp[i].appointmentId = tmpdeleteApp2[i].appointmentId; 
					tmpdeleteApp[i -1].appointmentId = tmpdeleteApp2[i].appointmentId;
				}
				htmlTemplatePart3 = getTemplate(fileTplDeleted);
			}
		else {
				htmlTemplatePart = getTemplate(fileTplError);
			return false;
		}

		deleteApp = (Appointment*)realloc(tmpdeleteApp, (size - 1) * sizeof(Appointment));

		writeStructs(&fname, deleteApp, size, sizeof(Appointment));
		}
	}
	std::free(deleteApp);
}
