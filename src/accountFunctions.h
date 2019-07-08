#ifndef _accountFunctions_h_
#define _accountFunctions_h_

struct Account {
	int id;
	char name[21];
	char password[21];
};

bool validateLength(const char *input);
int validateLogin(const char *fname, char *user, char *password);
bool createAccount(const char *fname, char *user, char *password);
bool login(const char *fname, char *data);
bool registerUser(const char *fname, char *data);
bool changePassword(const char *fname, int userID, char *data);

#endif
