#include <iostream>
#include <string.h>
#include "fileFunctions.h"
#include "formFunctions.h"
#include "sessionFunctions.h"

/*
	This function returns the alphabet used for "encrypting" sessions
*/
const char* getAlphabet() {
	return "pekRrNfwYTOZsXLbmu0t6l18gIoJqcCB9y2KQixGv57aDhASzn3VFjMWPUEdH4";
}

/*
	This function generates the users key which will be stored in a cookie
	char *username		takes a string
	int userID			takes an integer
	returns				an integer
*/
int generateCookieKey(char *username, int userID) {
	int tmpVal = userID;

	for (int i = 0; i < strlen(username); i++) {
		tmpVal += username[i];
	}

	return tmpVal;
}


/*
	This function checks if the given cookie data is valid
	const char *fname	takes a filename as a string
	char *cookieData	takes a cookie as string
	returns				true if cookie is valid, false if not
*/
bool validateCookie(const char *fname, char *cookieData) {
	// Get Alphabet for 'encrypting'
	const char *alphabet = getAlphabet();

	// Get Cookie Data (name, id)
	char *username = NULL;
	char *tmpKey = NULL;
	int key = -1;
	char *tmpID = NULL;
	int userID = -1;

	username = getValueOfKey(cookieData, (char*)"name", ';');
	if (username == NULL) {
		return false;
	}

	tmpKey = getValueOfKey(cookieData, (char*)"key", ';');
	if (tmpKey == NULL) {
		free(username);
		return false;
	}
	key = atoi(tmpKey);
	free(tmpKey);

	tmpID = getValueOfKey(cookieData, (char*)"id", ';');
	if (tmpID == NULL) {
		free(username);
		return false;
	}
	userID = atoi(tmpID);
	free(tmpID);

	// Read structs
	size_t amount = 0;
	Session *sessions = (Session*)readStructs(fname, &amount, sizeof(Session));

	if (sessions == NULL) {
		free(username);
		return false;
	}

	// Pos of our Session
	int sessionPos = -1;

	// Find struct with matching ID
	for (int i = 0; i < amount; i++) {
		if (sessions[i].id == userID) {
			sessionPos = i;
		}
	}

	if (sessionPos == -1) {
		// Whoops, not in file I guess...
		// Throw some kind of error
		return false;
	}


	// Now we can verify the cookie with reversing the encrypting:
	int tmpVal = generateCookieKey(username, userID);
	if (tmpVal != key) {
		// Something is wrong here, do not continue as no user should be messing with the data
		return false;
	}

	for (int i = 0; i < strlen(alphabet); i++) {
		// make this better, but should be clear how it works
		if ((char)(sessions[sessionPos].value[i] ^ tmpVal) != alphabet[i]) return false;
	}

	free(username);
	free(sessions);
	return true;
}

/*
	This function creates a session and writes it to a file
	const char *fname	takes a filename as string
	char *username		takes a username as string
	int userID			takes the user ID as integer
	returns				true on success, false on failure
*/
bool createSession(const char *fname, char *username, int userID) {
	const char* alphabet = getAlphabet();
	int tmpVal = generateCookieKey(username, userID);

	int sessionPos = -1;
	size_t amount = 0;
	Session *sessions = (Session*)readStructs(fname, &amount, sizeof(Session));

	if (sessions == NULL) {
		// Create first Session
		sessions = (Session*)malloc(sizeof(Session) * (amount + 1));

		if (sessions == NULL) {
			return false;
		}

		sessionPos = 0;
		amount++;
	}
	else {
		// Check if user already had a session
		// Find struct with matching ID
		for (int i = amount - 1; i > 0; i--) {
			if (sessions[i].id == userID) {
				sessionPos = i;
			}
		}
		if (sessionPos == -1) {
			// Create new session and append to array
			Session *tmpSessions = (Session*)realloc(sessions, (amount + 1) * sizeof(Session));

			if (tmpSessions == NULL) {
				free(sessions);
				return false;
			}

			sessions = tmpSessions;
			sessionPos = amount;
			amount++;
		}
	}
	// Set ID
	sessions[sessionPos].id = userID;
	// Set value
	for (int i = 0; i < strlen(alphabet); i++) {
		sessions[sessionPos].value[i] = alphabet[i] ^ tmpVal;
	}

	writeStructs((char*)fname, sessions, amount, sizeof(Session));
	free(sessions);
	return true;
}