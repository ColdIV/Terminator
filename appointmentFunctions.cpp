#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileFunctions.h"
#include "formFunctions.h"
#include "appointmentFunctions.h"
#include "fileFunctions.h"
#include "formFunctions.h"
#include "accountFunctions.h"

const char* fileTplError = "templates/error.html";
//@TODO: Error Tenplate erstellen

bool appointmentHTMLausgabe(const char fname, char* user) {
	Appointment *test1 = 0;
	size_t size = 0;
	test1 = (Appointment*)readStructs(&fname, &size, sizeof(Appointment));

	int givenUserId = 13;
	/* givenuserID = getValueOfKey(cookieData, (char*)"id", ';'); */

	for (size_t i = 0; i < size; i++) {
		if (strcmp((char*)test1[i].userId,(char*) givenUserId)){
			//@TODO: Error Tenplate erstellen
			//Der User hat eine falschee Id
			return false;
		}
		else(!strcmp((char*)test1[i].userId, (char*)givenUserId)){
			for(size_t i = 0; i <= size; i++) {
				while (!strcmp((char*)test1[i].userId, (char*)givenUserId)) {
					std::cout << "Content-type:text/html\r\n\r\n";
					std::cout << "<tr>";
					std::cout << "<td>" << test1[size].appointmentId << "< / td>";
					std::cout << "<td>" << test1[size].date << "< / td>";
					std::cout << "<td>" << test1[size].time << "< / td>";
					std::cout << "<td>" << test1[size].description << ";< / td>";
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
			//@TODO: Fehlermeldung mit getTemplate
			return false;
		}
	}
}
bool getDataApp(char* data) {
	char* sdate = NULL;
	char* stime = NULL;
	char* sdescription = NULL;
	char* sappointmentId = NULL;

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

	//die neuen daten in struct als tmp reinschreiben
	//makeApp ausführen
	addAp = (Appointment*)readStructs(&fname, &size, sizeof(Appointment));

	if (addAp == NULL) {
		// Create first Appointment
		addAp = (Appointment*)malloc((size + 1) * sizeof(Appointment));
		//addAp[nr].appointmentId = 0;extra leer gelassen wg makeAppointmentID
		
		strcpy_s(addAp[size].date, sdate);
		strcpy_s(addAp[size].time, stime);
		strcpy_s(addAp[size].description, sdescription);

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

		strcpy_s(addAp[size].date, sdate);
		strcpy_s(addAp[size].time, stime);
		strcpy_s(addAp[size].description, sdescription);
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
		//@TODO: Template error
		return false;
	}
	for (size_t i = 0; i < size; i++) {
		if (!strcmp((char*)apChange[size].appointmentId, (char*)givenAppID)) {
			return false;
		}
		else if (!strcmp((char*)apChange[size].appointmentId, (char*)givenAppID)) {
			
			strcpy_s(apChange[size].date, sdate);
			strcpy_s(apChange[size].time, stime);
			strcpy_s(apChange[size].description, sdescription);
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
				//@TODO: Template gelöscht
				return true;
			}
			else if(size < sizeof(Appointment)) {
				for (size_t i = 0; i = size; i ++ ) {
					tmpdeleteApp2[i].appointmentId = tmpdeleteApp2[size + 1].appointmentId;
					tmpdeleteApp[i].appointmentId = tmpdeleteApp[size + 1].appointmentId;
					//tmpdeleteApp[i].appointmentId = tmpdeleteApp2[i].appointmentId; 
					tmpdeleteApp[i -1].appointmentId = tmpdeleteApp2[i].appointmentId;
				}
				//@TODO: Template gelöscht
			}
		else {
			//@TODO: Tempalte error
			return false;
		}

		deleteApp = (Appointment*)realloc(tmpdeleteApp, (size - 1) * sizeof(Appointment));

		writeStructs(&fname, deleteApp, size, sizeof(Appointment));
		}
	}
	std::free(tmpdeleteApp);
	std::free(tmpdeleteApp2);
}
