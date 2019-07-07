#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fileFunctions.h"
#include "formFunctions.h"
#include "accountFunctions.h"
#include <iostream>

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

	int id = 0;
	Account *accounts = NULL;
	size_t size = 0;
	accounts = (Account*)readStructs(fname, &size, sizeof(Account));

	if (accounts == NULL) {
		return 0;
	}

	for (size_t i = 0; i < size; i++) {
		if (!strcmp(accounts[i].name, user) && !strcmp(accounts[i].password, password)) {
			id = accounts[i].id + 1;
			free(accounts);
			return id;
		}
	}

	free(accounts);
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
	Account *tmpAccounts;
	size_t size = 0;

	accounts = (Account*)readStructs(fname, &size, sizeof(Account));

	if (accounts == NULL) {
		// Create first Account
		accounts = (Account*)malloc((size + 1) * sizeof(Account));
		
		if (accounts == NULL) {
			return false;
		}

		accounts[size].id = 0;
		strcpy_s(accounts[size].name, user);
		strcpy_s(accounts[size].password, password);

	} else {
		// Check if user already exists, if so: return false
		for (size_t i = 0; i < size; i++) {
			if (!strcmp(accounts[i].name, user)) {
				return false;
			}
		}

		// Create user
		tmpAccounts = (Account*)realloc(accounts, (size + 1) * sizeof(Account));

		if (tmpAccounts == NULL) {
			// Failed to allocate new memory, free old memory and return false
			free(accounts);
			return false;
		}

		accounts = tmpAccounts;

		accounts[size].id = accounts[size - 1].id + 1;
		strcpy_s(accounts[size].name, user);
		strcpy_s(accounts[size].password, password);
	}

	writeStructs(fname, accounts, size + 1, sizeof(Account));

	free(accounts);

	return true;
}

/*
	This functions extracts the data to user and password and then validates it
	const char *fname		takes a filename as string
	char *data				takes data as string
	returns					true on success, false on failure
*/
bool login(const char *fname, char *data) {
	char *user = NULL;
	char *password = NULL;
	
	user = getValueOfKey(data, (char*)"username");
	if (user == NULL) {
		return false;
	}

	password = getValueOfKey(data, (char*)"password");
	if (password == NULL) {
		free(user);
		return false;
	}

	int userID = validateLogin(fname, user, password);
	char id[100];
	
	if (userID) {
		userID--;
		_itoa_s(userID, id, 10);
		setCookie("id", id);
		setCookie("name", user);

		free(user);
		free(password);
		return true;
	}

	free(user);
	free(password);
	return false;
}

/*
	This function extracts the data to user, password and repeat password and then creates an new account
	const char *fname		takes a filename as string
	char *data				takes data as string
	returns					true on success, false on failure
*/
bool registerUser(const char *fname, char *data) {
	char *user = NULL;
	char *password = NULL;
	char *repeatPassword = NULL;

	bool valuesValid = true;

	user = getValueOfKey(data, (char*)"username");

	if (user == NULL) {
		return false;
	}
	
	password = getValueOfKey(data, (char*)"password");
	if (password == NULL) {
		free(user);
		return false;
	}

	repeatPassword = getValueOfKey(data, (char*)"repeatPassword");
	if (repeatPassword == NULL) {
		free(user);
		free(password);
		return false;
	}

	if (strlen(user) > 20 || strlen(user) < 3 || strlen(password) < 1){
		valuesValid = false;
	}

	if (strcmp(password, repeatPassword) != 0) {
		valuesValid = false;
	}

	if (valuesValid && createAccount(fname, user, password)) {
		login(fname, data);
		return true;
	}

	free(user);
	free(password);
	free(repeatPassword);
	return false;
}