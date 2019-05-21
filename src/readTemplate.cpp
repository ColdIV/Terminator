#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


int main() {
	char *fname = "test.txt";
	char *buffer;
	FILE *f = fopen(fname, "rb");
	if (f != NULL) {
		fseek(f, 0, SEEK_END);
		long size = ftell(f);
		fseek(f, 0, SEEK_SET);
		buffer = new char[size];
		if (buffer != NULL) {
			fread(buffer, size, 1, f);
			buffer[size] = '\0';
			std::cout << buffer << std::endl;
		}
	}
	fclose(f);

	system("pause");
	return 0;
}