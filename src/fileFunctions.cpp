#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileFunctions.h"

/*
	This function reads array of structs from a file
	const char *fname           takes a filename
	size_t *num                 takes the address of a variable which will then hold the amount of data read
	size_t element_size         takes the sizeof the struct

	ATTENTION: This function returns void*, to get the struct you will have to convert the type
	Example:
		TestStruct *test = 0;
		size_t num = 0;
		char fname[] = "test.bin";
		test = (TestStruct*) readStructs(fname, &num, sizeof(TestStruct));
*/
void* readStructs(const char *fname, size_t *num, size_t element_size) {
	void *data;
	FILE *f = fopen(fname, "rb");

	if (f == NULL) return NULL;

	fseek(f, 0, SEEK_END);
	*num = ftell(f) / element_size;
	fseek(f, 0, SEEK_SET);
	data = malloc(element_size * (*num));
	fread(data, element_size, (*num), f);
	fclose(f);

	return data;
}


/*
	This function reads the nth struct from a file
	const char *fname           takes a filename
	size_t n                    takes the position of the desired struct
	size_t element_size         takes the sizeof the struct

	ATTENTION: This function returns void*, to get the struct you will have to convert the type
	The target array should only hold one element as this function only returns an array with a length of 1
*/
void* readNthStruct(const char *fname, size_t n, size_t element_size) {
	void *data;
	FILE *f = fopen(fname, "rb");

	if (f == NULL) return NULL;

	fseek(f, (n - 1) * element_size, SEEK_SET);
	data = malloc(element_size);
	fread(data, element_size, 1, f);
	fclose(f);

	return data;
}

/*
	This function writes an array of structs to a file
	const char *fname       takes a filename
	void *data              takes array of structs
	size_t num              takes the amount of structs (length of array)
	size_t element_size     takes the sizeof the struct
*/
void writeStructs(const char *fname, void *data, size_t num, size_t element_size) {
	FILE *f = fopen(fname, "wb");

	if (f == NULL) return;

	fwrite(data, element_size, num, f);
	fclose(f);
}

/*
	This function reads     the content of a file and returns it as a string (char*)
	char *fname			    takes a string
	returns				    the content of a file as string or NULL
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
