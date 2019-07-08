#pragma warning( disable : 4996)
#include <iostream>
#include <time.h>
#include <string.h>
#include "formFunctions.h"

/*
	This functions extracts the value of a specific key
	const char *str     takes a string
	char *key           takes a string
	char separator      takes a char or nothing (default is '&')
	returns             a string or NULL if key could not be found

	ATTENTION: Make sure to free(value) when you are done using it!

	Example:
	getValueOfKey("?name=Admin&password=abc123", "name")
	// -> returns "Admin"
	getValueOfKey("?name=Admin&password=abc123", "password")
	// -> returns "abc123"
	getValueOfKey("name=test; password=test_pass;", "name", ';')
	// -> returns "test"
	
	Note: Those are NOT secure credentials!
*/
char* getValueOfKey(const char *str, char *key, char separator) {
	int start = 0, end = 0;
	char *tmpStr;
	char *tmpKey = key;

	if (str == NULL || key == NULL) {
		return NULL;
	}

	if (*(str + start) == '?') start++;

	if (*(str + start) && *(str + start) != *tmpKey) {
		do {
			while (*(str + start) && *(str + start) != separator) start++;
			start++;
			if (separator == ';') start++;
		} while (*(str + start) && *(str + start) != *tmpKey);
	}

	while (*tmpKey && *(str + start) && *(str + start) == *tmpKey) {
		start++;
		tmpKey++;

		if (!*tmpKey && *(str + start) == '=') {
			start++;

			for (end = 0; *(str + start + end) && *(str + start + end) != separator; end++);

			tmpStr = (char*)malloc((start + end + 2) * sizeof(char*));

			if (tmpStr == NULL) {
				return NULL;
			}

			strcpy(tmpStr, (str + start));
			*(tmpStr + end) = '\0';

			return tmpStr;
		}

		if ((!*tmpKey && *(str + start) != '=') || (*(str + start) != *tmpKey)) {
			tmpKey = key;

			if (*(str + start) && *(str + start) != *key) {
				do {
					while (*(str + start) && *(str + start) != separator) start++;
					start++;
					if (separator == ';') start++;
				} while (*(str + start) && *(str + start) != *tmpKey);
			}
		}
	}

	return NULL;
}


/*
	This functions sets a cookie
	char *key           takes a string as key
	char *value         takes a string as value
	
	ATTENTION: Cookies have to be set before any other output!
*/
void setCookie(const char *key, char *value) {
	std::cout << "Set-Cookie:" << key << " = " << value << ";\r\n";
}
