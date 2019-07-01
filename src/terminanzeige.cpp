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
	int userId;
	int appointmentId;
};

void appointmentHTMLausgabe(const char fname, int userId){
	Appointment * test1 = 0;
	size_t num = 0;
	test1 = (Appointment*)readStructs(&fname, &num, sizeof(Appointment));

	char *cookieData = getenv("HTTP_COOKIE");// getenv wird schon in der Main verwendent! 
	char *userID;
	userID = getValueOfKey(cookieData, (char*)"id", ';');

	if ((char)*userID != userId){
		cout << "Der User hat keine oder eine falsche id";
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
}bool appointmentAdd(const char fname,int appointmentId, int userId){
	Appointment * addAp = 0;
	size_t num = 0;
	
	addAp = (Appointment*)readStructs(&fname, &num, sizeof(Appointment));
	if (appointmentId == NULL){
		return 0;
	}
	else
	{
	}
	writeStructs(&fname, &num, sizeof(Appointment));

	return 1;
}
void writeStructs(const char *fname, void *data, size_t num, size_t element_size);
/*
void dateTime(){
//This functions returns an timestamp from a date
//char *date          takes a date as "yyyy-mm-dd"
//returns             date as timestamp (comparable with >, <, ==, ...)
time_t getTimestamp(char *date);
}*/
void descriptionF(){
	cout << "Test"; //aus lesen aus struct
}

//appointmentDelete

//appointmentChange
