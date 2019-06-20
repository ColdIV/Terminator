#define _CRT_SECURE_NO_WARNINGS
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
	int end = 0;
	char *tmpStr;
	char *tmpKey = key;

	if (*str == '?') str++;

	if (*str && *str != *tmpKey) {
		do {
			while (*str && *str != separator) str++;
			str++;
		} while (*str && *str != *tmpKey);
	}

	while (*tmpKey && *str && *str == *tmpKey) {
		str++;
		tmpKey++;

		if (!*tmpKey && *str == '=') {
			str++;

			for (end = 0; *(str + end) && *(str + end) != separator; end++);

			tmpStr = new char[strlen(str)];
			strcpy(tmpStr, str);
			tmpStr[end] = '\0';

			return tmpStr;
		}

		if ((!*tmpKey && *str != '=') || (*str != *tmpKey)) {
			tmpKey = key;

			if (*str && *str != *key) {
				do {
					while (*str && *str != separator) str++;
					str++;
				} while (*str && *str != *tmpKey);
			}
		}
	}

	return NULL;
}

/*
	This functions returns an timestamp from a date
	char *date          takes a date as "yyyy-mm-dd"
	returns             date as timestamp (comparable with >, <, ==, ...)
*/
time_t getTimestamp(char *date) {
	tm tmdate = {0};
	tmdate.tm_year = atoi(&date[0]) - 1900;
	tmdate.tm_mon = atoi(&date[5]) - 1;
	tmdate.tm_mday = atoi(&date[8]);
	time_t timestamp = mktime(&tmdate);

	return timestamp;
}

/*
	This is the compare function for qsort
	
	Usage:
		Pass the following as last parameter for qsort:
		int(*compare)(const void *, const void*)
*/
int compare(const void *p1, const void *p2) {
	time_t *pa = (time_t*)p1;
	time_t *pb = (time_t*)p2;

	if (*pa < *pb) return -1;
	if (*pa > *pb) return 1;
	return 0;
}


/*
	This functions sets a cookie
	char *key           takes a string as key
	char *value         takes a string as value
	
	ATTENTION: Cookies have to be set before any other output!
*/
void setCookie(char *key, char *value) {
	std::cout << "Set-Cookie:" << key << " = " << value << ";\r\n";
}
