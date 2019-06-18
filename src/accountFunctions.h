#ifndef _accountFunctions_h_
#define _accountFunctions_h_

struct Account {
	int id;
	char name[20];
	char password[20];
};

bool validateLogin(const char *fname, char *user, char *password);
bool createAccount(const char *fname, char *user, char *password);
bool login(const char *fname, char *data);
bool registerUser(const char *fname, char *data);

#endif
