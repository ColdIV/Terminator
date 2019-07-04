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
	char userId;
	char appointmentId;
};

bool appointmentHTMLausgabe(const char fname, char* user) {
	Appointment* test1 = 0;
	size_t num = 0;
	test1 = (Appointment*)readStructs(&fname, &num, sizeof(Appointment));

	char savedUserId[8] = "13,";
	char givenUserId [8]= "13";
	/* char *userID;
	userID = getValueOfKey(cookieData, (char*)"id", ';'); */

	/* if (userID != user)*/
	if (givenUserId != savedUserId)
	{
		//Der User hat eine falschee Id
		return 0;
	}
	else {
		for (int i = 0; i <= num; i++) {
			cout << "Content-type:text/html\r\n\r\n";
			cout << "<tr>";
			cout << "<td>" << test1[num].date << "< / td>";
			cout << "<td>" << test1[num].time << "< / td>";
			cout << "<td>" << test1[num].description << ";< / td>";
			cout << "<td><button><i class = 'fa fa - pencil'>ändern< / i>< / button><button><i class = 'fa fa - trash'>löschen< / i>< / button>< / td>";
			cout << "< / tr>";
		}
	}
}

bool appointmentAdd(const char fname, char* des, char appointmentId, char* user) {
	Appointment* addAp;
	Appointment* tmpAdd;
	char givenappID[8] = "234";
	size_t nr = 0;

	addAp = (Appointment*)readStructs(&fname, &nr, sizeof(Appointment));

	for (size_t i = 0; i < nr; i++) {
		if (strcmp((char*)addAp[i].appointmentId, givenappID) || givenappID == NULL) {
			return 0;
			//@TODO: Fehlermeldung mit getTemplate
		}
		/* if(appointmentId == appointmentId){
		return false;
		}*/
		else if(!strcmp((char*)addAp[i].appointmentId, givenappID)) {
			addAp = (Appointment*)malloc((nr + 1) * sizeof(Appointment));
			//@TODO: TerminID muss vorher generiert werden
			//@TODO: speicherplatz wieder freigeben
			//@TODO: lösung finden da auf tmp= given und addAp= have kommt
			addAp[num].appointmentId = addAp[num].userId + nr + 1;
			strcpy_s(addAp[num].appointmentId, AappointmentId);
			strcpy_s(addAp[num].userId, Auser);
			strcpy_s(addAp[num].date, Adate);
			strcpy_s(addAp[num].time, Atime);
			strcpy_s(addAp[num].description, Ades);

			addAp = tmpAdd;
		}
	}
writeStructs(&fname, addAp, nr + 1, sizeof(Appointment));

return 1;
}

//void writeStructs(const char *fname, void *data, size_t num, size_t element_size);

//appointmentDelete
//@TODO: Löschen

//appointmentChange
bool appointmentChange(const char fname) {
	Appointment* apChange;
	Appointment* tmpChange;
	size_t nur = 0;
	//1appChange = have
	//2tmpChange = given
	//3appChange = tmpChange

	//1ready
	apChange = (Appointment*)readStructs(&fname, &nur, sizeof(Appointment));

	//2
	/* +writeStructs(&fname, addChange, nr + 1, sizeof(Appointment));
	tmpChange = given*/

	/*getValue Wert nimmt(abgeschickte veränderung vom User)*/

	//password = getValueOfKey(data, (char*)"password");

	//3
	/*suche nach id im array,*/
	apChange = tmpChange;

	}
