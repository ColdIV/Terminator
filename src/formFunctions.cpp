#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

char* getValueOfKey(const char *str, char *key, char separator = '&') {
	int end = 0;
	char *tmpStr;
	char *tmpKey = key;

	if (*str && *str != *key) {
		while (*str && *str != separator) str++;
		str++;
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
				while (*str && *str != separator) str++;
				str++;
			}
		}
	}

	return NULL;
}


int main() {
	char *str = "vorname=hans&nachname=peter&name=hanspeter";
	char *key = "name";
	std::cout << getValueOfKey(str, key) << std::endl;

	system("pause");
	return 0;
}