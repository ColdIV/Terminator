#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fileFunctions.h"
#include "formFunctions.h"
#include "accountFunctions.h"

/*
	This function checks if login credentials are correct
	const char *fname		takes a filename as string
	char *user				takes the username as string
	char *password			takes the password as string
	returns					the ID + 1 of the user or 0 (ID + 1 will always be positive, so it can be handled like "true" / "false")
*/
int validateLogin(const char *fname, char *user, char *password) {
	// Check input length (I don't really care about password, but it should at least be 1 char...)
	if (strlen(user) > 20 || strlen(user) < 3 || strlen(password) < 1) {
		return 0;
	}

	Account *accounts;
	size_t size = 0;
	accounts = (Account*)readStructs(fname, &size, sizeof(Account));

	for (size_t i = 0; i < size; i++) {
		if (!strcmp(accounts[i].name, user) && !strcmp(accounts[i].password, password)) {
			return accounts[i].id + 1;
		}
	}

	return 0;
}

/*
	This function creates an account with given user details
	const char *fname		takes a filename as string
	char *user				takes the username as string
	char *password			takes the password as string
	returns					true on success, false on failure
*/
bool createAccount(const char *fname, char *user, char *password) {
	Account *accounts;
	size_t size = 0;
	accounts = (Account*)readStructs(fname, &size, sizeof(Account));

	// Check if user already exists, if so: return false
	for (size_t i = 0; i < size; i++) {
		if (!strcmp(accounts[i].name, user)) {
			return false;
		}
	}

	// Create user
	accounts = (Account*)realloc(accounts, sizeof(Account) * (size + 1));
	if (accounts) {
		accounts[size].id = accounts[size - 1].id + 1;
		strcpy(accounts[size].name, user);
		strcpy(accounts[size].password, password);

		writeStructs(fname, accounts, size, sizeof(Account));
	} else {
		// Error occurred whilst trying to allocate new memory for our array
		return false;
	}

	return true;
}

/*
	This functions extracts the data to user and password and then validates it
	const char *fname		takes a filename as string
	char *data				takes data as string
	returns					true on success, false on failure
*/
bool login(const char *fname, char *data) {
	char *user = getValueOfKey(data, (char*)"name");
	char *password = getValueOfKey(data, (char*)"password");

	int userID = validateLogin(fname, user, password);
	char *id = NULL;
	
	if (userID) {
		sprintf(id, "%d", --userID);
		setCookie((char*)"id", id);
		setCookie((char*)"name", user);
		return true;
	}
	
	return false;
}

/*
	This function extracts the data to user, password and repeat password and then creates an new account
	const char *fname		takes a filename as string
	char *data				takes data as string
	returns					true on success, false on failure
*/
bool registerUser(const char *fname, char *data) {
	char *user = getValueOfKey(data, (char*)"name");
	char *password = getValueOfKey(data, (char*)"password");
	char *repeatPassword = getValueOfKey(data, (char*)"repeatPassword");

	if (strcmp(password, repeatPassword) != 0) {
		return false;
	}

	if (createAccount(fname, user, password)) {
		login(fname, data);
		return true;
	}

	return false;
}