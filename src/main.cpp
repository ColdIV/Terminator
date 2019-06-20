#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "fileFunctions.h"
#include "formFunctions.h"
#include "accountFunctions.h"
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
	char *postData = (char*) malloc(contentLen * sizeof(char));
	if (contentLen > 0 && postData) {
		std::cin >> postData;
	} else {
		// Either no postData sent or
		// failed to allocate memory, so act as if we had no input
		// @TODO: Less lazy future me, make it prettier.
		contentLen = 0;
	}

	// Get Cookie data
	char *cookieData = getenv("HTTP_COOKIE");
	
	// Template
	char *htmlTemplate = NULL;
	
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
			htmlTemplate = getTemplate("../htdocs/login.html");
		} else {
			// Handle Login (Login should set cookie)
			if (login("accounts.bin", postData)) {
				// Login successfull
				htmlTemplate = getTemplate("../htdocs/menue.html");
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
			if (registerUser("accounts.bin", postData)) {
				// Register successfull
				// Auto-Login user
				htmlTemplate = getTemplate("../htdocs/menue.html");
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
			if (1/*handleAppointment*/) {
				// Success, show appointments
			} else {
				// Failed, show error
			}
		}
	}
	else if (!strcmp(page, "menu")) {
		htmlTemplate = getTemplate("../htdocs/menue.html");
	} else if (!strcmp(page, "logout")) {
		setCookie("name", (char*)"");
		htmlTemplate = getTemplate("../htdocs/login.html");
	} else {
		// Error 404 (Lazy, so just back to menu / login)
	}

	// Show HTML Template
	std::cout << "Content-type:text/html\r\n\r\n";
	std::cout << htmlTemplate;
	
	// Free memory (should free automatically on program exit, but who knows)
	if (postData) free(postData);
	if (htmlTemplate) free(htmlTemplate);

	return 0;
}
