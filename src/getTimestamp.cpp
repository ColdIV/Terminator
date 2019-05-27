#include <iostream>
#include <time.h>

/*
	This functions returns an timestamp from a date

	char *date			takes a date as "yyyy-mm-dd"
	returns				  date as timestamp (compareable with >, <, ==, ...)
*/
time_t getTimestamp(char *date) {
	tm tmdate = { 0 };
	tmdate.tm_year = atoi(&date[0]) - 1900;
	tmdate.tm_mon = atoi(&date[5]) - 1;
	tmdate.tm_mday = atoi(&date[8]);
	time_t timestamp = mktime(&tmdate);

	return timestamp;
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