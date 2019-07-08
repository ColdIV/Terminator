#pragma warning( disable : 4996)
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "fileFunctions.h"
#include "formFunctions.h"
#include "accountFunctions.h"
#include "appointmentFunctions.h"
#include "sessionFunctions.h"


struct User {
	int id;
	char name[21];
	bool loggedIn;
};

int main(int argc, char** argv) {
	/*
		Main Program, which should handle the routing and call the correct functions / templates 
		GET data will be used for routing (it will tell us which template to send and which functions to call)
	*/

	// Filenames
	const char *fileAccounts = "accounts.bin";
	const char *fileAppointments = "appointments.bin";
	const char *fileSessions = "sessions.bin";
	// Templates
	const char *fileTplHead = "templates/head.html";
	const char *fileTplLogin = "templates/login.html";
	const char *fileTplLoginError = "templates/loginError.html";
	const char *fileTplRegister = "templates/register.html";
	const char *fileTplMenue = "templates/menue.html";
	const char *fileTplChangePassword = "templates/changePassword.html";
	const char* fileTplAppointment1 = "templates/showAppointment1.html";
	const char* fileTplAppointment2 = "templates/showAppointment2.html";
	const char* fileTplAddAppointment = "templates/addAppointment.html";
	const char* fileTplEditAppointment = "templates/editAppointment.html";
	const char* fileTplError = "templates/error.html";
	const char* fileTplDeleted = "templates/delete.html";

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

	char *postData = (char*) malloc((contentLen + 1) * sizeof(char));
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
	char *htmlTemplatePart1 = NULL;
	char *htmlTemplatePart2 = NULL;

	// Get page from getData
	char *page = NULL;
	page = getValueOfKey(getData, (char*)"page");
	
	if (page == NULL) {
		page = (char*) malloc(8 * sizeof(char));
		strcpy(page, "default");
	}

	// Check if user logged in, if yes: create user, else: route to register
	User user = { 0 };
	user.loggedIn = false;

	char *cookieUsername = NULL;
	cookieUsername = getValueOfKey(cookieData, (char*)"name", ';');
	
	if (cookieUsername == NULL) {
		cookieUsername = (char*)"";
	}

	if (strcmp(cookieUsername, "") != 0) {
		// Create user
		char *userID;
		userID = getValueOfKey(cookieData, (char*)"id", ';');

		if (userID == NULL) {
			user.loggedIn = false;
		} else {
			if (validateCookie(fileSessions, cookieData)) {
				user.id = atoi(userID);
				free(userID);
				strcpy(user.name, cookieUsername);
				user.loggedIn = true;

				if (strcmp(page, "default") == 0 || strcmp(page, "register") == 0 || strcmp(page, "login") == 0) {
					page = (char*)malloc(5 * sizeof(char));
					strcpy(page, "menu");
				}
			}
		}
		
	} 

	// Variables we might need later
	Appointment *appointments = NULL;
	size_t appointmentAmount = 0;

	// @TODO: Delete this (DEBUG)
	/*std::cout << "Content-type:text/html\r\n\r\n";*/


	// Routing
	if (strcmp(page, "default") == 0 || strcmp(page, "login") == 0 || (!user.loggedIn && strcmp(page, "register") != 0)) {
		if (contentLen == 0) {
			htmlTemplatePart1 = getTemplate(fileTplLogin);
		} else {
			// Handle Login (Login should set cookie)
			if (login(fileAccounts, fileSessions, postData)) {
				// Login successfull
				char *tmpUser = NULL;
				tmpUser = getValueOfKey(postData, (char*)"username");
				strcpy(user.name, tmpUser);

				htmlTemplatePart1 = getTemplate(fileTplMenue, "{{user}}", user.name);
			} else {
				// Login failed, show error
				htmlTemplatePart1 = getTemplate(fileTplLoginError);
			}
		}
	} else if (strcmp(page, "register") == 0) {
		if (contentLen == 0) {
			// Show Register HTML
			htmlTemplatePart1 = getTemplate(fileTplRegister);
		}
		else {
			// Handle Register
			if (registerUser(fileAccounts, fileSessions, postData)) {
				// Register successfull
				// Auto-Login user
				char *tmpUser = NULL;
				tmpUser = getValueOfKey(postData, (char*)"username");
				strcpy(user.name, tmpUser);

				htmlTemplatePart1 = getTemplate(fileTplMenue, "{{user}}", user.name);
			}
			else {
				// Register failed, show error (@TODO: maybe add error codes, lazy though.)
				htmlTemplatePart1 = getTemplate(fileTplError);
			}
		}
	} else if(strcmp(page, "changePassword") == 0) {
		if (contentLen == 0) {
			// Show HTML
			htmlTemplatePart1 = getTemplate(fileTplChangePassword);
		} else {
			if (changePassword(fileAccounts, user.id, postData)) {
				// Successfull, show menu
				htmlTemplatePart1 = getTemplate(fileTplMenue, "{{user}}", user.name);
			} else {
				// Failed to change password, show error
				htmlTemplatePart1 = getTemplate(fileTplError);
			}
		}
	} else if (strcmp(page, "appointments") == 0) {
		// Show Appointments HTML (Handling of Appointments below)
		htmlTemplatePart1 = getTemplate(fileTplAppointment1, "{{user}}", user.name);
		htmlTemplatePart2 = getTemplate(fileTplAppointment2);
	} else if (strcmp(page, "appointmentAdd") == 0) {
		if (contentLen == 0) {
			// Show Form
			htmlTemplatePart1 = getTemplate(fileTplAddAppointment);
		} else {
			if (appointmentAdd(fileAppointments, user.id, postData)) {
				// Added appointment, show menu
				htmlTemplatePart1 = getTemplate(fileTplMenue, "{{user}}", user.name);
			} else {
				// Failed to add appointment, show error
				htmlTemplatePart1 = getTemplate(fileTplError);
			}
		}
	} else if (strcmp(page, "appointmentEdit") == 0) {
		// Show Form
		const char *appointmentEditID = getValueOfKey(postData, (char*)"id");
		if (appointmentEditID == NULL) {
			htmlTemplatePart1 = getTemplate(fileTplError);
		} else {
			htmlTemplatePart2 = getTemplate(fileTplEditAppointment);
		}
	} else if (strcmp(page, "appointmentEditP") == 0) {
		if (appointmentChange(fileAppointments, user.id, postData)) {
			// Changed appointment, show menu
			htmlTemplatePart1 = getTemplate(fileTplMenue, "{{user}}", user.name);
		}
		else {
			// Failed to change appointment, show error
			htmlTemplatePart1 = getTemplate(fileTplError);
		}
	} else if (strcmp(page, "appointmentDelete") == 0) {
		const char *appointmentDeleteID = getValueOfKey(postData, (char*)"id");
		if (appointmentDeleteID == NULL) {
			htmlTemplatePart1 = getTemplate(fileTplError);
		} else {
			if (deleteAppointment(fileAppointments, user.id, atoi(appointmentDeleteID))) {
				// Deleted appointment, show menu
				htmlTemplatePart1 = getTemplate(fileTplMenue, "{{user}}", user.name);
			}
		}
	} else if (strcmp(page, "menu") == 0) {
		htmlTemplatePart1 = getTemplate(fileTplMenue, "{{user}}", user.name);
	} else if (strcmp(page, "logout") == 0) {
		setCookie("name", (char*)"");
		setCookie("id", (char*)"");
		htmlTemplatePart1 = getTemplate(fileTplLogin);
	} else {
		// Error 404 (Lazy, so just back to login)
		htmlTemplatePart1 = getTemplate(fileTplLogin);
	}


	// Show HTML Template
	std::cout << "Content-type:text/html\r\n\r\n";
	char *htmlHead = getTemplate(fileTplHead);

	if (htmlHead == NULL || (htmlTemplatePart1 == NULL && htmlTemplatePart2 == NULL)) {
		std::cout << "Error! Could not find template files." << std::endl;
	} else {
		std::cout << htmlHead << std::endl;
		if (htmlTemplatePart1 != NULL) {
			std::cout << htmlTemplatePart1 << std::endl;
		}
	}

	if (strcmp(page, "appointments") == 0) {
		// Show appointments
		appointments = (Appointment*)readStructs(fileAppointments, &appointmentAmount, sizeof(Appointment));

		if (appointments != NULL) {
			qsort((void*)appointments, appointmentAmount, sizeof(Appointment), &compare);

			// Check if User has appointments to show
			for (int i = 0; i < appointmentAmount; i++) {
				if (user.id == appointments[i].userId) {
					std::cout	<< "<tr>"								
								<< "\t<td>" << appointments[i].appointmentId << "</td>"
								<< "\t<td>" << appointments[i].date << "</td>"
								<< "\t<td>" << appointments[i].time << "</td>"
								<< "\t<td>" << appointments[i].description << "</td>"								
								<< "\t<td>"
								<< "\t\t<form class=\"d-inline\" action=\"?page=appointmentEdit\" method=\"post\">"
								<< "\t\t\t<input type=\"hidden\" name=\"description\" value=\"" << appointments[i].description << "\">"
								<< "\t\t\t<input type=\"hidden\" name=\"time\" value=\"" << appointments[i].time << "\">"
								<< "\t\t\t<input type=\"hidden\" name=\"date\" value=\"" << appointments[i].date << "\">"
								<< "\t\t\t<input type=\"hidden\" name=\"id\" value=\"" << appointments[i].appointmentId << "\">"
								<< "\t\t\t<button type=\"submit\"><i class = 'fa fa - pencil'>&Auml;ndern</i></button>"
								<< "\t\t</form>"
								<< "\t\t<form class=\"d-inline\" action=\"?page=appointmentDelete\" method=\"post\">"
								<< "\t\t\t<input type=\"hidden\" name=\"id\" value=\"" << appointments[i].appointmentId << "\">"
								<< "<button type=\"submit\"><i class = 'fa fa - trash'>l&ouml;schen</i></button>"
								<< "\t\t</form>"
								<< "\t</td>"
								<< "</tr>";
				}
			}

			free(appointments);
		}
	} else if ((strcmp(page, "appointmentEdit") == 0) && htmlTemplatePart2 != NULL) {
		char *appointmentId = NULL;
		char *appointmentDate = NULL;
		char *appointmentTime = NULL;
		char *appointmentDescription = NULL;
		bool appointmentEditError = false;
		
		appointmentId = getValueOfKey(postData, (char*)"id");
		if (appointmentId == NULL) {
			appointmentEditError = true;
		}

		if (!appointmentEditError) {
			appointmentDate = getValueOfKey(postData, (char*)"date");
			if (appointmentDate == NULL) {
				free(appointmentId);
				appointmentEditError = true;
			}
		}

		if (!appointmentEditError) {
			appointmentTime = getValueOfKey(postData, (char*)"time");
			if (appointmentTime == NULL) {
				free(appointmentId);
				free(appointmentDate);
				appointmentEditError = true;
			}

			// Quick fix for time
			char *tmpTime = NULL;
			tmpTime = fixTime(appointmentTime);

			if (tmpTime == NULL) {
				appointmentEditError = true;
			}

			strcpy(appointmentTime, tmpTime);
			free(tmpTime);
		}

		if (!appointmentEditError) {
			appointmentDescription = getValueOfKey(postData, (char*)"description");
			if (appointmentDescription == NULL) {
				free(appointmentId);
				free(appointmentDate);
				free(appointmentTime);
				appointmentEditError = true;
			}
		}

		if (!appointmentEditError) {
			// Show Form
			std::cout << "<div class='card-body'>"
				<< "\t<h5 class='card-title text-center'>Termin anlegen</h5>"
				<< "\t<form action='?page=appointmentEditP' method='post' autocomplete='off'>"
				<< "\t\t<div class='form-group'>"
				<< "\t\t\t<label>Datum</label>"
				<< "\t\t\t<input class='form-control mb-1' id='date' name='date' type='date' value='" << appointmentDate << "' maxlength='10'>"
				<< "\t\t\t<label>Uhrzeit</label>"
				<< "\t\t\t<input class='form-control mb-1' id='time' name='time' type='time' value='" << appointmentTime << "' maxlength='4'>"
				<< "\t\t\t<label>Art</label>"
				<< "\t\t\t<input type='text' class='form-control' id='art' name='description' value='" << appointmentDescription << "' maxlength='100'>"
				<< "\t\t\t<input type='hidden' name='id' value='" << appointmentId << "'>"
				<< "\t\t</div>"
				<< "\t\t<button type='submit' id='lay_beside' class='btn btn-primary float-right'>Termin&auml;ndern</button>"
				<< "\t\t<a href='?page=menu'><button type='button' class='btn btn-primary float-left'>Zur&uuml;ck</button></a>"
				<< "\t</form>";

			free(appointmentId);
			free(appointmentDate);
			free(appointmentTime);
			free(appointmentDescription);
		} else {
			// Show Error
			htmlTemplatePart1 = getTemplate(fileTplError);
			if (htmlTemplatePart1 != NULL) {
				std::cout << htmlTemplatePart1 << std::endl;
			}
		}


	}

	if (htmlTemplatePart2 != NULL) {
		std::cout << htmlTemplatePart2 << std::endl;
	}
	
	// Wee Free Mem' (should free automatically on program exit, but who knows)
	if (postData != NULL) {
		free(postData);
	}

	if (page != NULL) {
		free(page);
	}

	if (cookieUsername != NULL && strcmp(cookieUsername, "") != 0) {
		free(cookieUsername);
	}

	if (htmlHead != NULL) {
		free(htmlHead);
	}

	if (htmlTemplatePart1 != NULL) {
		free(htmlTemplatePart1);
	}

	if (htmlTemplatePart2 != NULL) {
		free(htmlTemplatePart2);
	}

	return 0;
}
