#include <iostream>
#include <time.h>

/*
	This functions returns an timestamp from a date

	char *date			takes a date as "yyyy-mm-dd"
	returns				date as timestamp (compareable with >, <, ==, ...)
*/
time_t getTimestamp(char *date) {
	tm tmdate = { 0 };
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
int compare(const void *p1, const void *p2)
{
	time_t *pa = (time_t*)p1;
	time_t *pb = (time_t*)p2;

	if (*pa < *pb) return -1;
	if (*pa > *pb) return 1;
	return 0;
}

int main() {
	char date1[] = "2011-04-01";
	char date2[] = "2017-06-01";
	time_t t1;
	time_t t2;

	t1 = getTimestamp(date1);
	t2 = getTimestamp(date2);

	if (t1 > t2) std::cout << "t1 is klasse";
	else std::cout << "t2 ist cool";

	std::cout << std::endl;
	system("pause");
	return 0;
}