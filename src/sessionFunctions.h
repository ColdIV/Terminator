#ifndef _sessionFunctions_h_
#define _sessionFunctions_h_

struct Session {
	int id;
	// Same length as alphabet
	char value[62];
};

const char* getAlphabet();
int generateCookieKey(char *username, int userID);
bool validateCookie(const char *fname, char *cookieData);
bool createSession(const char *fname, char *username, int userID);

#endif