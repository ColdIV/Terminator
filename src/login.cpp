#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileFunctions.h"
#include "formFunctions.h"

using namespace std;

struct Account {
    char *user;
    char *password;
    int id;
};

int login(char* user, char* password) {
	int i =0;
    Account account;
	char *reghtml = getenv("Key");
	char *data = (char*)"name=wassi&password=1234";

	account.user = getValueOfKey(data, (char*)"name");
	account.password = getValueOfKey(data, (char*)"password");

	if (validateLogin(account.user, account.password)){
		setCookie((char*)"name", account.user);
		setCookie((char*)"password", account.password);
		// Ausgabe des Menüs
		std::cout << getTemplate((char*)"../htdocs/menue.html");
	}
	else if((char*)*reghtml == (char*)"../htdocs/reg.html"){
		Account *accounts;
		size_t size = 0;
		writeStructs("accounts.bin",&data, size, sizeof(Account));

			for (size_t i = 0; i < size; i++){
				if (accounts[i].user == user && accounts[i].password == password){
				return true;
				}
			}
	}
	else {
		// Fehlermeldung, Login falsch
		std::cout << getTemplate((char*)"../htdocs/login.html");
	}

    return 0;
}

bool validateLogin(char *user, char *password){
	Account *accounts;
	size_t *size = 0;
	accounts = (Account*) readStructs("accounts.bin", size, sizeof(Account));

	for (size_t i = 0; i < (int)size; i++){
		if (!strcmp(accounts[i].user, user) && !strcmp(accounts[i].password, password)){
			return true;
		}
	}

	return false;
}
