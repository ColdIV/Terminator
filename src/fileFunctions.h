#ifndef _fileFunctions_h_
#define _fileFunctions_h_

void* readStructs(const char *fname, size_t *num, size_t element_size);
void* readNthStruct(const char *fname, size_t n, size_t element_size);
void writeStructs(const char *fname, void *data, size_t num, size_t element_size);
char* getTemplate(char *fname);

#endif
