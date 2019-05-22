#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


/*
	This function reads the content of a file and returns it as a string (char*)
	char *fname			takes a string
	returns				the content of a file as string or NULL
*/
char* getTemplate(char *fname) {
	char *buffer;
	long size;
	FILE *f = fopen(fname, "rb");
	if (f != NULL) {
		fseek(f, 0, SEEK_END);
		size = ftell(f);
		fseek(f, 0, SEEK_SET);
		buffer = new char[size];
		
		if (buffer != NULL) {
			fread(buffer, size, 1, f);
			buffer[size] = '\0';
			
			fclose(f);
			return buffer;
		}
	}
	
	fclose(f);
	return NULL;
}

int main() {
	char *tmpStr;
	
	tmpStr = getTemplate("test.txt");
	
	if (tmpStr == NULL) {
		std::cout << "Error! File not found." << std::endl;
	} else {
		std::cout << "Result: \n" << tmpStr << std::endl;
	}

	system("pause");
	return 0;
}
