#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileFunctions.h"
#include "formFunctions.h"

using namespace std;

struct Appointment {
	char* date[100];
	char* time[100];
	char* description[200];
	int userId;
	int appointmentId;
};
const char* fileTplError = "templates/error.html";
//@TODO: Error Tenplate erstellen

bool appointmentHTMLausgabe(const char fname, char* user) {
	Appointment *test1 = 0;
	size_t num = 0;
	test1 = (Appointment*)readStructs(&fname, &num, sizeof(Appointment));

	int givenUserId = 13;
	/* givenuserID = getValueOfKey(cookieData, (char*)"id", ';'); */

	for (size_t i = 0; i < num; i++) {
		if (strcmp((char*)test1[i].userId,(char*) givenUserId))
		{
			//@TODO: Error Tenplate erstellen
			//Der User hat eine falschee Id
			return false;
		}
		else(!strcmp((char*)test1[i].userId, (char*)givenUserId)){
			for (size_t i = 0; i <= num; i++) {
				while (!strcmp((char*)test1[i].userId, (char*)givenUserId)) {
					cout << "Content-type:text/html\r\n\r\n";
					cout << "<tr>";
					cout << "<td>" << test1[num].appointmentId << "< / td>";
					cout << "<td>" << test1[num].date << "< / td>";
					cout << "<td>" << test1[num].time << "< / td>";
					cout << "<td>" << test1[num].description << ";< / td>";
					cout << "<td><button><i class = 'fa fa - pencil'>ändern< / i>< / button><button><i class = 'fa fa - trash'>löschen< / i>< / button>< / td>";
					cout << "< / tr>";
				}
			}
		}
	
	}
}

bool makeAppointmentID(const char fname) {
	size_t numb = 0;
	Appointment* makeApp = 0;

	makeApp = (Appointment*)readStructs(&fname, &numb, sizeof(Appointment));

	int tmp = 0;
	//search for the highest appointmentId
	for (size_t i = 0; i < numb; i++) {
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

	sdate = getValueOfKey(data, (char*)"date");
	stime = getValueOfKey(data, (char*)"time");
	sdescription = getValueOfKey(data, (char*)"description");
}

bool appointmentAdd(const char fname, char* sdate, char* stime, char* sdescription) {
	Appointment* addAp;
	Appointment* tmpAdd;
	int givenUserId = 13;
	size_t nr = 0;

	// prüfen ob der cookie noch stimmt

	//die neuen daten in struct als tmp reinschreiben
	//makeApp ausführen
	addAp = (Appointment*)readStructs(&fname, &nr, sizeof(Appointment));

	if (addAp == NULL) {
		// Create first Appointment
		addAp = (Appointment*)malloc((nr + 1) * sizeof(Appointment));
		//addAp[nr].appointmentId = 0;extra leer gelassen wg makeAppointmentID
		
		strcpy_s(addAp[nr].date, sdate);
		strcpy_s(addAp[nr].time, stime);
		strcpy_s(addAp[nr].description, sdescription);

		makeAppointmentID(fname);
		if (addAp == NULL) {
			return false;
		}
	}
	if (addAp != NULL) {
		tmpAdd = (Appointment*)realloc(addAp, (nr + 1) * sizeof(Appointment));

		addAp = tmpAdd;

		if (tmpAdd == NULL) {
			std::free(addAp);
			return false;
		}

		strcpy_s(addAp[nr].date, sdate);
		strcpy_s(addAp[nr].time, stime);
		strcpy_s(addAp[nr].description, sdescription);
		makeAppointmentID(fname);

	}
	writeStructs((char*)fname, addAp, nr + 1, sizeof(Appointment));

	return 1;
}

bool appointmentChange(const char fname, char* sdate, char* stime, char* sdescription) {
	Appointment* apChange;
	Appointment* tmpChange;
	size_t nur = 0;
	int givenAppID = 13;

	// prüfen ob der cookie noch stimmt

	apChange = (Appointment*)readStructs(&fname, &nur, sizeof(Appointment));

	if (apChange == NULL) {
		//@TODO: Template error
		return false;
	}
	for (size_t i = 0; i < nur; i++) {
		if (!strcmp((char*)apChange[nur].appointmentId, (char*)givenAppID)) {
			return false;
		}
		else if (!strcmp((char*)apChange[nur].appointmentId, (char*)givenAppID)) {
			
			strcpy_s(apChange[nur].date, sdate);
			strcpy_s(apChange[nur].time, stime);
			strcpy_s(apChange[nur].description, sdescription);
		}
	}

	writeStructs((char*)fname, apChange, nur + 1, sizeof(Appointment));

	return 1;
}
bool deleteAppoi(const char fname) {

	Appointment* deleteApp;
	Appointment* tmpdeleteApp;
	Appointment* tmpdeleteApp2;
	size_t number = 0;
	int givenAppID = 12; //@TODO: woher kriege ich diese IDDDDD

	deleteApp = (Appointment*)readStructs(&fname, &number, sizeof(Appointment));

	for (size_t i = 0; i < number; i++) {
		if (!strcmp((char*)deleteApp[number].appointmentId, (char*)givenAppID)) {
			return false;
		}
		else if (strcmp((char*)deleteApp[number].appointmentId, (char*)givenAppID)) {
			tmpdeleteApp = (Appointment*)readStructs(&fname, &number, sizeof(Appointment));
			tmpdeleteApp2 = (Appointment*)readStructs(&fname, &number, sizeof(Appointment));
			/*
			tmp[n] =n+1;
			m[n] = n+1;
			m[n-1] = tmp[2];
			*/
			if (number == sizeof(Appointment)) {
				//@TODO: Template gelöscht
				return true;
			}
			else if(number < sizeof(Appointment)) {
				for (size_t i = 0; i = number; i ++ ) {
					tmpdeleteApp2[i].appointmentId = tmpdeleteApp2[number + 1].appointmentId;
					tmpdeleteApp[i].appointmentId = tmpdeleteApp[number + 1].appointmentId;
					tmpdeleteApp[i].appointmentId = tmpdeleteApp2[i].appointmentId;
				}
				//@TODO: Template gelöscht
			}
		else {
			//@TODO: Tempalte error
			return false;
		}

		deleteApp = (Appointment*)realloc(tmpdeleteApp, (number - 1) * sizeof(Appointment));

		writeStructs(&fname, deleteApp, number, sizeof(Appointment));
		}
	}
	std::free(tmpdeleteApp);
	std::free(tmpdeleteApp2);
}
