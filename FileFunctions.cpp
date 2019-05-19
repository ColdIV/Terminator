#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

struct Test {
	int num;
};


/*
	This function reads array of structs from a file
	const char *fname		takes a filename
	size_t *num				takes the address of a variable which will then hold the amount of data read
	size_t element_size		takes the sizeof the struct

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
	This function writes an array of structs to a file
	const char *fname		takes a filename
	void *data				takes array of structs
	size_t num				takes the amount of structs (length of array)
	size_t element_size		takes the sizeof the struct
*/
void writeStructs(const char *fname, void *data, size_t num, size_t element_size) {
	FILE *f = fopen(fname, "wb");

	if (f == NULL) return;

	fwrite(data, element_size, num, f);
	fclose(f);
}

int main(int argc, char** argv) {
	/* 
		This is an example program for the functions 
		Remember to increase the array for writeStructs()
	*/
	char filename[] = "test.bin";
	size_t amount = 0;
	Test *arr = 0;
	Test *tmpArr = 0;

	int choice = 0;
	while (choice != 4) {		
		std::cout << "Write [1]\nRead [2]\nShow [3]\nExit [4]\nChoice: ";
		std::cin >> choice;
		system("cls");
		switch (choice) {
			case 1:
				// Increase array by 1
				arr = (Test*)realloc(arr, sizeof(Test) * (amount + 1));

				std::cout << "Enter a number: ";
				std::cin >> arr[amount].num;
			
				amount++;
				writeStructs(filename, arr, amount, sizeof(Test));
				break;

			case 2:
				arr = (struct Test*) readStructs(filename, &amount, sizeof(struct Test));
				break;

			case 3:
				for (size_t i = 0; i < amount; ++i) {
					std::cout << "i: " << i << " num: " << arr[i].num << std::endl;
				}

			default:
				break;
		}
	}
	
	return 0;
}