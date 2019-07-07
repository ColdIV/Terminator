#include <iostream>
#include <string.h>
#include "fileFunctions.h"

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

int main2() {
	// Alphabet for 'encrypting'
	const char *alphabet = "pekRrNfwYTOZsXLbmu0t6l18gIoJqcCB9y2KQixGv57aDhASzn3VFjMWPUEdH4";


	// Check if a cookie is set, if so:
	// Read structs
	size_t amount = 0;
	Session *tests = (Session*)readStructs("sessions.bin", &amount, sizeof(Session));

	// Fake User ID and Username (Should be read from Cookie)
	int userID = 0;
	const char *username = "testname";

	// # of our Session
	int sessionPos = -1;

	// Find struct with matching ID
	for (int i = 0; i < amount; i++) {
		if (tests[i].id == userID) {
			sessionPos = i;
		}
	}

	if (sessionPos == -1) {
		// Whoops, not in file I guess...
		// Throw some kind of error
		return 0;
	}

	// If we reach this, we may continue
	// We now got our struct:
	// tests[sessionPos]
	// And we can verify the cookie with reversing the shitty encrypting:
	int tmpVal = userID;

	for (int i = 0; i < strlen(username); i++) {
		tmpVal += username[i];
	}

	for (int i = 0; i < strlen(alphabet); i++) {
		// make this better, but should be clear how it works
		if ((char)(tests[sessionPos].value[i] ^ tmpVal) != alphabet[i]) return false;
	}

	// If we reach this, yay! They match, I guess.

	// Now if no Cookie was set, we will have to create the shitty session
	// we also might have to expand an array
	// check if the file is empty
	// write to file etc, but I don't want to do that right now.





	// Shitty old stuff, don't bother scrolling.
	
	
	/*Session test = { 0 };


	test.id = 1;
	const char *username = "testname";


	int tmpVal = test.id;

	for (int i = 0; i < strlen(username); i++) {
		tmpVal += username[i];
	}


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

	strcpy_s(test.value, res);*/

	system("pause");


	return 0;
}