#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileFunctions.h"
#include "formFunctions.h"
 
using namespace std;
 
struct Appointment {
	char *date[100];
	char *time[100];
	char *description[200];
	char userId;
	char appointmentId;
};

bool appointmentHTMLausgabe(const char fname, char *user){
	Appointment * test1 = 0;
	size_t num = 0;
	test1 = (Appointment*)readStructs(&fname, &num, sizeof(Appointment));

char savedUserId[8] = "13,";
	char *givenUserId = "13";
/*	char *userID;
	userID = getValueOfKey(cookieData, (char*)"id", ';'); */
 
/*	if (userID != user)*/
if(givenUserId != savedUserId)
{
		//Der User hat eine falschee Id
		return 0;
	}
	else{
		for (int i = 0; i <= num; i++){
			cout << "Content-type:text/html\r\n\r\n";
			cout << "<tr>";
			cout << "<td>" << test1[num].date << "< / td>";
			cout << "<td>" << test1[num].description << ";< / td>";
			cout << "<td><button><i class = 'fa fa - pencil'>ändern< / i>< / button><button><i class = 'fa fa - trash'>löschen< / i>< / button>< / td>";
			cout << "< / tr>";
		}
	}
}

bool appointmentAdd(const char fname,char *des, char appointmentId, char *user){
	Appointment * addAp;
	Appointment * tmpAdd;
	size_t nr = 0;
	
	addAp = (Appointment*)readStructs(&fname, &nr, sizeof(Appointment));
	
	if(appointmentId == appointmentId){
		return false;
	}
	else if(appointmentId != appointmentId || appointmentId == NULL){
		addAp = (Appointment*)malloc((nr+1)* sizeof(Appointment));
		//PRÜFUNG muss noch rein	
		addAp[num].appointmentId = addAp[num].userId + nr+1;
		strcpy_s(addAp[num].appointmentId, AappointmentId);
		strcpy_s(addAp[num].userId, Auser);
		strcpy_s(addAp[num].date, Adate);
		strcpy_s(addAp[num].time, Atime);
		strcpy_s(addAp[num].description, Ades);
	}
	writeStructs(&fname, addAp, nr + 1, sizeof(Appointment));
 
	return 1;
}
	char *date[100];
	char *time[100];
	char *description[200];
	char userId;
	char appointmentId;
 
//void writeStructs(const char *fname, void *data, size_t num, size_t element_size);
 
//appointmentDelete
 
//appointmentChange
