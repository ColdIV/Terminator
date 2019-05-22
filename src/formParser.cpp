#include <iostream>

/*
	This functions extracts the value of a specific key
	char *str		takes a string
	char *key		takes a string
	returns 		a string or NULL if key could not be found

	Example:
	getValueOfKey("?name=Admin&password=abc123", "name")
	// -> returns "Admin"
	getValueOfKey("?name=Admin&password=abc123", "password")
	// -> returns "abc123"

	Note: Those are NOT secure credentials!
*/
char* getValueOfKey(char *str, char *key) {
	int end = 0;
	str++;
	while (*str && *str != *key) str++;

	char *tmpKey = key;

	while (*tmpKey && *str && *str == *tmpKey) {
		str++;
		tmpKey++;

		if (!*tmpKey && *str == '=') {
			str++;
			for (end = 0; *(str + end) && *(str + end) != '&'; end++);
			*(str + end) = '\0';
			return str;
		}

		if ((!*tmpKey && *str != '=') || (*str != *tmpKey)) {
			tmpKey = key;
			while (*str && *str != *key) str++;
		}
	}

	return NULL;
}


int main() {
	char str[] = "?name3=test&name5=name&password=test2&name=test3&name2=test4";
	char *tmpStr;

	tmpStr = getValueOfKey(str, "name5");

	if (tmpStr == NULL) {
		std::cout << "Error! Key not found." << std::endl;
	}
	else {
		std::cout << "Result: " << tmpStr << std::endl;
	}

	system("pause");
	return 0;
}
