#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "fileFunctions.h"
#include "formFunctions.h"
#include <string.h>

struct User {
	int id;
	char name[20];
	bool loggedIn;
};


int main(int argc, char** argv) {
	/*
		Main Program, which should handle the routing and call the correct functions / templates 
		GET data will be used for routing (it will tell us which template to send and which functions to call)
	*/
		
	// Get length of POST data
	int contentLen = atoi(getenv("CONTENT_LENGTH"));

	// Get GET and POST request data
	char *getData = getenv("QUERY_STRING");
	char *postData = new char[contentLen];
	if (contentLen > 0) {
		std::cin >> postData;
	}

	// Get Cookie data
	char *cookieData = getenv("HTTP_COOKIE");
	
	
	// Get page from getData
	char *page = getValueOfKey(getData, (char*)"page");

	// Check if user logged in, if yes: create user, else: route to register
	User user = { 0 };
	if (page != "register" && page != "login" && strcmp(getValueOfKey(cookieData, (char*)"name", ';'), "") != 0) {
		// Create user
		// @TODO: Check if data is valid, maybe some security stuff. No clue, need sleep.
		user.id = atoi(getValueOfKey(cookieData, (char*)"id", ';'));
		strcpy(user.name, getValueOfKey(cookieData, (char*)"name", ';'));
		user.loggedIn = true;
	} 
	// else {
		// @TODO: Delete this comment.
		// route to "register" or "login", will happen below
	// }

	
	// Routing
	if (!strcmp(page, "login") || (!user.loggedIn && strcmp(page, "register") != 0)) {
		if (!contentLen) {
			// Show Login HTML
		} else {
			// Handle Login (Login should set cookie)
			if (login(postData, "accounts.txt")) {
				// Login successfull
				// Show menu
			} else {
				// Login failed, show error
			}
		}
	} else if (!strcmp(page, "register")) {
		if (!contentLen) {
			// Show Register HTML
		}
		else {
			// Handle Register
			if (registerUser(postData, "accounts.txt")) {
				// Register successfull
				// Auto-Login user
				// Show Men�
			}
			else {
				// Register failed, show error (@TODO: maybe add error codes, lazy though.)
			}
		}
	} else if (!strcmp(page, "appointments")) {
		if (!contentLen) {
			// Show Appointments HTML
		} else {
			// Handle appointments postData (add, edit, delete?, maybe add more "pages" for that)
			// Add Appointment
			if (handleAppointment) {
				// Success, show appointments
			} else {
				// Failed, show error
			}
		}
	}
	else if (!strcmp(page, "menu")) {
		// Show Menu
	} else if (!strcmp(page, "logout")) {
		setCookie((char*)"name", (char*)"");
		// Show Login
	} else {
		// Error 404 (Lazy, so just back to menu / login)
	}

	return 0;
}
