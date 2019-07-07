#ifndef _appointmentFunctions_h_
#define _appointmentFunctions_h_

struct Appointment {
	char date[100];
	char time[100];
	char description[200];
	int userId;
	int appointmentId;
};

bool getDataApp(char* data); 
bool appointmentAdd(const char *fname, int aUserID, char *postData);
bool appointmentChange(const char fname, char* sdate, char* stime, char* sdescription);
bool deleteAppoi(const char fname, char* sappointmentId);

#endif