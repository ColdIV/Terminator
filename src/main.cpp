#include <iostream>
#include "fileFunctions.h"
#include "formFunctions.h"

struct Test {
	int num;
};

void fileFunctionsExample() {
	/*
		This is an example program for the file functions
		Remember to increase the array for writeStructs()
	*/
	char filename[] = "test.bin";
	size_t amount = 0;
	Test *arr = 0;

	// For readNthStruct()
	Test *tmpArr = 0;
	size_t n;

	int choice = 0;
	while (choice != 5) {
		system("cls");
		std::cout << "Menu\n"
			<< "-------------------\n"
			<< "Write \t\t[1]\n"
			<< "Read \t\t[2]\n"
			<< "Read nth \t[3]\n"
			<< "Show \t\t[4]\n"
			<< "Exit \t\t[5]\n"
			<< "-------------------\n"
			<< "Choice: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			// Increase array by 1
			arr = (Test*)realloc(arr, sizeof(Test) * (amount + 1));

			std::cout << "Enter a number: ";
			std::cin >> arr[amount].num;

			amount++;
			writeStructs(filename, arr, amount, sizeof(Test));
			break;

		case 2:
			arr = (Test*)readStructs(filename, &amount, sizeof(Test));
			break;

		case 3:
			n = 0;

			std::cout << "Enter n: ";
			std::cin >> n;

			tmpArr = new Test[1];
			tmpArr = (Test*)readNthStruct(filename, n, sizeof(Test));

			std::cout << "\nThe " << n << ". struct contains: " << tmpArr[0].num << std::endl;
			system("pause");
			break;

		case 4:
			std::cout << "-------------------\n"
				<< "Result:\n"
				<< std::endl;
			for (size_t i = 0; i < amount; ++i) {
				std::cout << "i: " << i << " num: " << arr[i].num << std::endl;
			}
			std::cout << "-------------------\n";
			system("pause");

		default:
			break;
		}
	}
}

void formFunctionsExample() {
	/*
		This is an example program for the form functions
	*/

	// For parser
	char str[] = "?vorname=hans&name1=test1&name2=test2&password=pass&name=test&name3=test3&name4=&name5=";
	char *tmpStr;
	// Only for input, usually you can just set the string in here like: *find = "name1";
	char *find = new char[100];

	// For timestamp
	char date1[] = "2011-04-01";
	char *date2 = new char[strlen(date1)];
	time_t t1;
	time_t t2;

	int choice = 0;
	while (choice != 3) {
		system("cls");
		std::cout << "Menu\n"
			<< "-------------------\n"
			<< "Parser \t\t[1]\n"
			<< "Timestamp \t[2]\n"
			<< "Exit \t\t[3]\n"
			<< "-------------------\n"
			<< "Choice: ";
		std::cin >> choice;
		std::cout << "-------------------\n";

		switch (choice) {
			case 1:
				std::cout << "String: " << str << std::endl;
				std::cout << "Find: ";
				std::cin >> find;

				tmpStr = getValueOfKey(str, find);

				std::cout << "-------------------\n";

				if (tmpStr == NULL) {
					std::cout << "Error! Key not found." << std::endl;
				}
				else {
					std::cout << "Result: " << tmpStr << std::endl;
				}

				std::cout << "-------------------\n";
				system("pause");
				break;
			case 2:
				std::cout << "Date: " << date1 << std::endl;
				std::cout << "Compare with: ";
				std::cin >> date2;

				t1 = getTimestamp(date1);
				t2 = getTimestamp(date2);

				std::cout << "-------------------\n" 
						  << "Result: ";
				if (t1 > t2) std::cout << date1 << " is bigger!";
				else std::cout << date2 << " is bigger!";

				std::cout << "\n-------------------"
						  << std::endl;
				system("pause");
				break;
			default:
				break;
		}
	}

	system("pause");
}

int main(int argc, char** argv) {
	int cho = 0;

	while (cho == 0) {
		std::cout << "Examples\n"
			<< "-------------------\n"
			<< "Choose program to run:\n"
			<< "fileFunctions \t[1]\n"
			<< "formFunctions \t[2]\n"
			<< "-------------------\n"
			<< "Choice: ";
		std::cin >> cho;

		if (cho == 1) fileFunctionsExample();
		else if (cho == 2) formFunctionsExample();
		else cho = 0;
		system("cls");
	}

	return 0;
}