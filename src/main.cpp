#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "fileFunctions.h"
#include "formFunctions.h"
#include <string.h>

//struct Test {
//	int num;
//};
//
//struct Addr {
//	char name[200];
//};
//
//void fileFunctionsExample() {
//	/*
//		This is an example program for the file functions
//		Remember to increase the array for writeStructs()
//	*/
//	char filename[] = "test.bin";
//	size_t amount = 0;
//	Test *arr = 0;
//
//	// For readNthStruct()
//	Test *tmpArr = 0;
//	size_t n;
//
//	int choice = 0;
//	while (choice != 5) {
//		system("cls");
//		std::cout << "Menu\n"
//			<< "-------------------\n"
//			<< "Write \t\t[1]\n"
//			<< "Read \t\t[2]\n"
//			<< "Read nth \t[3]\n"
//			<< "Show \t\t[4]\n"
//			<< "Exit \t\t[5]\n"
//			<< "-------------------\n"
//			<< "Choice: ";
//		std::cin >> choice;
//		switch (choice) {
//		case 1:
//			// Increase array by 1
//			arr = (Test*)realloc(arr, sizeof(Test) * (amount + 1));
//
//			std::cout << "Enter a number: ";
//			std::cin >> arr[amount].num;
//
//			amount++;
//			writeStructs(filename, arr, amount, sizeof(Test));
//			break;
//
//		case 2:
//			arr = (Test*)readStructs(filename, &amount, sizeof(Test));
//			break;
//
//		case 3:
//			n = 0;
//
//			std::cout << "Enter n: ";
//			std::cin >> n;
//
//			tmpArr = new Test[1];
//			tmpArr = (Test*)readNthStruct(filename, n, sizeof(Test));
//
//			std::cout << "\nThe " << n << ". struct contains: " << tmpArr[0].num << std::endl;
//			system("pause");
//			break;
//
//		case 4:
//			std::cout << "-------------------\n"
//				<< "Result:\n"
//				<< std::endl;
//			for (size_t i = 0; i < amount; ++i) {
//				std::cout << "i: " << i << " num: " << arr[i].num << std::endl;
//			}
//			std::cout << "-------------------\n";
//			system("pause");
//
//		default:
//			break;
//		}
//	}
//}
//
//void formFunctionsExample() {
//	/*
//		This is an example program for the form functions
//	*/
//
//	// For parser
//	char str[] = "?vorname=hans&name1=test1&name2=test2&password=pass&name=test&name3=test3&name4=&name5=";
//	char *tmpStr;
//	// Only for input, usually you can just set the string in here like: *find = "name1";
//	char *find = new char[100];
//
//	// For timestamp
//	char date1[] = "2011-04-01";
//	char *date2 = new char[strlen(date1)];
//	time_t t1;
//	time_t t2;
//
//	int choice = 0;
//	while (choice != 3) {
//		system("cls");
//		std::cout << "Menu\n"
//			<< "-------------------\n"
//			<< "Parser \t\t[1]\n"
//			<< "Timestamp \t[2]\n"
//			<< "Exit \t\t[3]\n"
//			<< "-------------------\n"
//			<< "Choice: ";
//		std::cin >> choice;
//		std::cout << "-------------------\n";
//
//		switch (choice) {
//			case 1:
//				std::cout << "String: " << str << std::endl;
//				std::cout << "Find: ";
//				std::cin >> find;
//
//				tmpStr = getValueOfKey(str, find);
//
//				std::cout << "-------------------\n";
//
//				if (tmpStr == NULL) {
//					std::cout << "Error! Key not found." << std::endl;
//				}
//				else {
//					std::cout << "Result: " << tmpStr << std::endl;
//				}
//
//				std::cout << "-------------------\n";
//				system("pause");
//				break;
//			case 2:
//				std::cout << "Date: " << date1 << std::endl;
//				std::cout << "Compare with: ";
//				std::cin >> date2;
//
//				t1 = getTimestamp(date1);
//				t2 = getTimestamp(date2);
//
//				std::cout << "-------------------\n" 
//						  << "Result: ";
//				if (t1 > t2) std::cout << date1 << " is bigger!";
//				else std::cout << date2 << " is bigger!";
//
//				std::cout << "\n-------------------"
//						  << std::endl;
//				system("pause");
//				break;
//			default:
//				break;
//		}
//	}
//
//	system("pause");
//}

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
				// Show Menü
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
		setCookie("name", "");
		// Show Login
	} else {
		// Error 404 (Lazy, so just back to menu / login)
	}
	




	//int cho = 0;

	// SOME TESTS
	//Addr *addr = new Addr[1];
	//strcpy(addr[0].name, "dies ist kein name weil es zu lang ist\0");

	//writeStructs("test.txt", addr, 1, sizeof(Addr));
	//
	//size_t amount = 1;
	//Addr *res = new Addr[amount];
	//res = (Addr*)readStructs("test.txt", &amount, sizeof(Addr));

	//Addr *neu = new Addr[++amount];
	//strcpy(neu[0].name, res[0].name);
	//strcpy(neu[1].name, "neuer text nur viel langer!\0");
	//writeStructs("test.txt", neu, 2, sizeof(Addr));
	//
	//res = new Addr[amount];
	//res = (Addr*)readStructs("test.txt", &amount, sizeof(Addr));

	//std::cout << res[0].name << std::endl;
	//std::cout << res[1].name << std::endl;
	//system("pause");

	// TEST MENÜ
	//while (cho == 0) {
	//	std::cout << "Examples\n"
	//		<< "-------------------\n"
	//		<< "Choose program to run:\n"
	//		<< "fileFunctions \t[1]\n"
	//		<< "formFunctions \t[2]\n"
	//		<< "-------------------\n"
	//		<< "Choice: ";
	//	std::cin >> cho;

	//	if (cho == 1) fileFunctionsExample();
	//	else if (cho == 2) formFunctionsExample();
	//	else cho = 0;
	//	system("cls");
	//}

	return 0;
}
