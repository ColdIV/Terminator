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

bool appointmentHTMLoutput(const char fname, char* user) {
	Appointment *outputHTML = NULL;
	size_t size = 0;
	outputHTML = (Appointment*)readStructs(&fname, &size, sizeof(Appointment));

	for (size_t i = 0; i < size; i++) {
		if (strcmp((char*)outputHTML[i].userId,user)){
			htmlTemplatePart = getTemplate(fileTplError);
			return false;
		}
		if(!strcmp((char*)outputHTML[i].userId,user)){
			for(int i = 0; i <= size; i++) {
				while (!strcmp((char*)outputHTML[i].userId, user)); {
					std::cout << "Content-type:text/html\r\n\r\n";
					std::cout << "<tr>";
					std::cout << "<td>" << outputHTML[size].appointmentId << "< / td>";
					std::cout << "<td>" << outputHTML[size].date << "< / td>";
					std::cout << "<td>" << outputHTML[size].time << "< / td>";
					std::cout << "<td>" << outputHTML[size].description << ";< / td>";
					std::cout << "<td><button><i class = 'fa fa - pencil'>ändern< / i>< / button><button><i class = 'fa fa - trash'>löschen< / i>< / button>< / td>";
					std::cout << "< / tr>";
				}
			}
		}
	
	}
}

bool makeAppointmentID(const char fname){
	size_t size = 0;
	Appointment* makeApp = 0;

	makeApp = (Appointment*)readStructs(&fname, &size, sizeof(Appointment));

	int tmp = 0;
	//search for the highest appointmentId
	for (size_t i = 0; i < size; i++) {
		if (tmp < makeApp[i].appointmentId) {
			tmp = makeApp[i].appointmentId;
		}
		//give the last(new) appointment an unique ID
		else if (tmp == makeApp[i].appointmentId) {
			tmp + 1;
			makeApp[i+1].appointmentId = makeApp[i+1].appointmentId = tmp;
			writeStructs(&fname, makeApp, i + 1, sizeof(Appointment));
			return true;
		}
		else {
			htmlTemplatePart = getTemplate(fileTplError);
			return false;
		}
	}
}
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
}

bool appointmentAdd(const char fname, char* sdate, char* stime, char* sdescription) {
	Appointment* addAp;
	Appointment* tmpAdd;
	int givenUserId = 13;
	size_t size = 0;

	// prüfen ob der cookie noch stimmt

	addAp = (Appointment*)readStructs(&fname, &size, sizeof(Appointment));

	if (addAp == NULL) {
		// Create first Appointment
		addAp = (Appointment*)malloc((size + 1) * sizeof(Appointment));
		//addAp[nr].appointmentId = 0;extra leer gelassen wg makeAppointmentID
		
		strcpy_s((char*)addAp[size].date,100, sdate);
		strcpy_s((char*)addAp[size].time,100, stime);
		strcpy_s((char*)addAp[size].description,200, sdescription);

		makeAppointmentID(fname);
		if (addAp == NULL) {
			return false;
		}
	}
	if (addAp != NULL) {
		tmpAdd = (Appointment*)realloc(addAp, (size + 1) * sizeof(Appointment));

		addAp = tmpAdd;

		if (tmpAdd == NULL) {
			std::free(addAp);
			return false;
		}

		strcpy_s((char*)addAp[size].date,100, sdate);
		strcpy_s((char*)addAp[size].time,100, stime);
		strcpy_s((char*)addAp[size].description,200, sdescription);
		makeAppointmentID(fname);

	}
	writeStructs((char*)fname, addAp, size + 1, sizeof(Appointment));

	return 1;
}

bool appointmentChange(const char fname, char* sdate, char* stime, char* sdescription) {
	Appointment* apChange;
	size_t size = 0;
	int givenAppID = 13;

	// prüfen ob der cookie noch stimmt

	apChange = (Appointment*)readStructs(&fname, &size, sizeof(Appointment));

	if (apChange == NULL) {
		htmlTemplatePart = getTemplate(fileTplError);
		return false;
	}
	for (size_t i = 0; i < size; i++) {
		if (strcmp((char*)apChange[size].appointmentId, (char*)givenAppID)) {
			return false;
		}
		else if (!strcmp((char*)apChange[size].appointmentId, (char*)givenAppID)) {
			
			strcpy_s((char*)apChange[size].date,100, sdate);
			strcpy_s((char*)apChange[size].time,100, stime);
			strcpy_s((char*)apChange[size].description,200, sdescription);
		}
	}

	writeStructs((char*)fname, apChange, size + 1, sizeof(Appointment));

	return 1;
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
