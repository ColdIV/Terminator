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
struct Appointment {
    char *date;
    char *time;
    char *description;
	int id;
};

int login() {   
	int i =0;
    Account account;

	char *data = "name=wassi&password=1234";
	
	account.user = getValueOfKey(data, "name");
	account.password = getValueOfKey(data, "password");

	if (validateLogin(account.user, account.password)){
		setCookie("name", account.user);
		setCookie("password", account.password);
		// Ausgabe des Menüs
		std::cout << getTemplate("../htdocs/menue.html");
	}
	else {
		// Fehlermeldung, Login falsch
		std::cout << getTemplate("../htdocs/login-error.html");
	}

    return 0;
}

bool validateLogin(char *user, char *password){
	Account *accounts;
	size_t size = 0;
	accounts = (Account*) readStructs("accounts.bin", &size, sizeof(Account));
	
	for (int i = 0; i < size; i++){
		if (accounts[i].user == user && accounts[i].password){
			return true;
		}
	}
	return false;
}
