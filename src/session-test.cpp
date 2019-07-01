#include <iostream>
#include <string.h>

/*
	Changes:
		cookies will have user id username and maybe tmpVal
		file will have user id and res string
		program will have alphabet and key and username
*/

struct Session {
	int id;
	char value[62];
};

int main() {
	Session test = { 0 };
	int KEY = 13;

	test.id = 1;
	char *username = "testname";


	int tmpVal = test.id + KEY;

	for (int i = 0; i < strlen(username); i++) {
		tmpVal += username[i];
	}

	char *alphabet = "pekRrNfwYTOZsXLbmu0t6l18gIoJqcCB9y2KQixGv57aDhASzn3VFjMWPUEdH4";

	char res[62];

	for (int i = 0; i < strlen(alphabet); i++) {
		res[i] = alphabet[i] ^ tmpVal;
	}

	std::cout << "Alphabet: " << alphabet << std::endl;
	std::cout << "Username: " << username << std::endl;
	std::cout << "ID: " << test.id << std::endl;
	std::cout << "tmpVal: " << tmpVal << std::endl;
	std::cout << "Result: " << res << std::endl;
	std::cout << "Result as int: " << std::endl;
	for (int i = 0; i < strlen(alphabet); i++) {
		std::cout << (int)res[i] << ", ";
	}


	std::cout << "\nReversed: " << std::endl;
	for (int i = 0; i < strlen(alphabet); i++) {
		std::cout << (char)(res[i] ^ tmpVal);
	}

	strcpy_s(test.value, res);

	system("pause");


	return 0;
}