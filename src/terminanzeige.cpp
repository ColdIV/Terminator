#define _CRT_SECURE_NO_WARNINGS
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
	char *description;
	int id;
};// feste größe in formFunction.h hab da die strukts abgelegt lol

void appointmentHTML(){
	Appointment * test1 = 0;
	size_t num = 0;
	test1 = (Appointment*)readStructs("termin.bin", &num, sizeof(Appointment));

	for (int i = 0; i<= num ;i++){
	cout << "Content-type:text/html\r\n\r\n";
	cout << "<tr>";
	// Error weil beim ausgeben- > operator wird nicht erkannt
	//cout << "<td>" << dateTime() << "< / td>";
	//cout << "<td>" << descriptionF() << ";< / td>";
	cout << "<td><button><i class = 'fa fa - pencil'>ändern< / i>< / button><button><i class = 'fa fa - trash'>löschen< / i>< / button>< / td>";
	cout << "< / tr>";
}
}

void dateTime(){
	/*
	This functions returns an timestamp from a date
	char *date          takes a date as "yyyy-mm-dd"
	returns             date as timestamp (comparable with >, <, ==, ...)
	*/
	time_t getTimestamp(char *date);
}

void descriptionF(){
	cout << "Test"; //
}