#include <iostream>
#include "fileFunctions.h"
#include "formParser.h"

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

void formParserExample() {
	/*
		This is an example program for the formParser functions
	*/
	char str[] = "?name3=test&name5=name&password=test2&name=test3&name2=test4";
	char *tmpStr;
	char find[] = "name5";

	tmpStr = getValueOfKey(str, find);

	if (tmpStr == NULL) {
		std::cout << "Error! Key not found." << std::endl;
	}
	else {
		std::cout << "Result: " << tmpStr << std::endl;
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
			<< "formParser \t[2]\n"
			<< std::endl;
		std::cin >> cho;

		if (cho == 1) fileFunctionsExample();
		else if (cho == 2) formParserExample();
		else cho = 0;
		system("cls");
	}

	return 0;
}
