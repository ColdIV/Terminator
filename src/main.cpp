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
	char *tmpContentLen = getenv("CONTENT_LENGTH");
	int contentLen;
	if (tmpContentLen == NULL) {
		contentLen = 0;
	} else {
		contentLen = atoi(tmpContentLen);
	}

	// Get GET and POST request data
	char *getData = getenv("QUERY_STRING");

	char *postData = (char*) malloc(contentLen * sizeof(char));
	if (contentLen > 0 && postData != NULL) {
		std::cin >> postData;
	} else {
		// Either no postData sent or
		// failed to allocate memory, so act as if we had no input
		// @TODO: Less lazy future me, make it prettier.
		postData = NULL;
		contentLen = 0;
	}

	// Get Cookie data
	char *cookieData = getenv("HTTP_COOKIE");
	if (cookieData == NULL) {
		cookieData = (char*)"name=";
	}
	
	// Template
	char *htmlTemplate = NULL;

	// Get page from getData
	// @TODO: Why exactly doesn't tmpPage show the correct value? (std::cout << tmpPage; shows rubbish, page works.)
	char page[100];
	char *tmpPage = NULL;
	tmpPage = getValueOfKey(getData, (char*)"page");
	if (tmpPage == NULL) {
		strcpy(page, "login");
	} else {
		strcpy(page, tmpPage);
	}

	// Check if user logged in, if yes: create user, else: route to register
	User user = { 0 };
	char cookieUsername[50];
	char *tmpCookieUsername = NULL;
	tmpCookieUsername = getValueOfKey(cookieData, (char*)"name", ';');
	if (tmpCookieUsername == NULL) {
		strcpy(cookieUsername, "");
	} else {
		strcpy(cookieUsername, tmpCookieUsername);
	}

	if (strcmp(page, "register") != 0 && (page, "login") != 0 && strcmp(cookieUsername, "") != 0) {
		// Create user
		// @TODO: Check if data is valid, maybe some security stuff. No clue, need sleep.
		char userID[50];
		strcpy(userID, getValueOfKey(cookieData, (char*)"id", ';'));
		user.id = atoi(userID);
		strcpy(user.name, cookieUsername);
		user.loggedIn = true;
	} 
	// else {
		// @TODO: Delete this comment.
		// route to "register" or "login", will happen below
	// }

	// Routing
	if (!strcmp(page, "login") || (!user.loggedIn && strcmp(page, "register") != 0)) {
		if (!contentLen) {
			htmlTemplate = getTemplate("templates/login.html");
		} else {
			// Handle Login (Login should set cookie)
			if (login("accounts.bin", postData)) {
				// Login successfull
				htmlTemplate = getTemplate("templates/menue.html");
			} else {
				// Login failed, show error
			}
		}
	} else if (!strcmp(page, "register")) {
		if (!contentLen) {
			// Show Register HTML
			htmlTemplate = getTemplate("templates/register.html");
		}
		else {
			// Handle Register
			if (registerUser("accounts.bin", postData)) {
				// Register successfull
				// Auto-Login user
				htmlTemplate = getTemplate("templates/menue.html");
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
		htmlTemplate = getTemplate("templates/menue.html");
	} else if (!strcmp(page, "logout")) {
		setCookie("name", (char*)"");
		htmlTemplate = getTemplate("templates/login.html");
	} else {
		// Error 404 (Lazy, so just back to login)
		htmlTemplate = getTemplate("templates/login.html");
	}

	// Show HTML Template
	std::cout << "Content-type:text/html\r\n\r\n";
	char *htmlHead = getTemplate("templates/head.html");

	if (htmlHead == NULL || htmlTemplate == NULL) {
		std::cout << "Error! Could not find template files." << std::endl;
	} else {
		std::cout << htmlHead << std::endl;
		std::cout << htmlTemplate;
	}
	
	// Wee Free Mem' (should free automatically on program exit, but who knows)
	if (postData != NULL) {
		free(postData);
	}

	if (htmlTemplate != NULL) {
		free(htmlTemplate);
	}

	return 0;
}
