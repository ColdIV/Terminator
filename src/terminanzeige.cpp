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

	char *cookieData = getenv("HTTP_COOKIE");// getenv wird schon in der Main verwendent! 
	char *userID;
	userID = getValueOfKey(cookieData, (char*)"id", ';');

	if (userID != user){
		//Der User kann eine falschee Id
		return 0;
	}
	else{
		for (int i = 0; i <= num; i++){
			cout << "Content-type:text/html\r\n\r\n";
			cout << "<tr>";
			// Error weil beim ausgeben- > operator wird nicht erkannt
			//cout << "<td>" << dateTime() << "< / td>";
			//cout << "<td>" << descriptionF() << ";< / td>";
			cout << "<td><button><i class = 'fa fa - pencil'>ändern< / i>< / button><button><i class = 'fa fa - trash'>löschen< / i>< / button>< / td>";
			cout << "< / tr>";
		}
	}
}
bool appointmentAdd(const char fname,char *des, char appointmentId, char *user){
	Appointment * addAp;
	Appointment * tmpAdd;
	size_t num = 0;
	
	addAp = (Appointment*)readStructs(&fname, &num, sizeof(Appointment));
	if (appointmentId == NULL){
		addAp = (Appointment*)malloc((num+1)* sizeof(Appointment));
		//PRÜFUNG
	}
	else
	{	
		addAp[num].appointmentId = 0;
		strcpy_s(addAp[num].description, des);//char,const char 
	}
	writeStructs(&fname, addAp, num + 1, sizeof(Appointment));

	return 1;
}

//void writeStructs(const char *fname, void *data, size_t num, size_t element_size);

//appointmentDelete

//appointmentChange
