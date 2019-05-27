#ifndef _formFunctions_h_
#define _formFunctions_h_

char* getValueOfKey(const char *str, char *key, char separator = '&');
time_t getTimestamp(char *date);
int compare(const void *p1, const void *p2);

#endif
