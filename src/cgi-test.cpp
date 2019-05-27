#include <iostream>
#include <string.h>
#include "formFunctions.h"

int main() {
	char *cookies;
	
	// Get length of content
	int contentLen = atoi(getenv("CONTENT_LENGTH"));
	// Create variable for content with matching size
	char *postData = new char[contentLen];
	// Set a few cookies
	setCookie("name", "test");
	setCookie("password", "test_pass");
	
	// Get cookie string
	cookies = getenv("HTTP_COOKIE");
	
	
	// Read Post Data to variable
	std::cin >> postData;
	
	// Some test output
	std::cout << "Content-type:text/html\r\n\r\n";
	std::cout << "<b>Cookies:</b> " << cookies;
	std::cout << "<br><b>Post Data:</b> " << postData;
	std::cout << "<br><br>Password (Cookie): " << getValueOfKey(cookies, "password", ';');
	std::cout << "<br><br>Name (Form): " << getValueOfKey(postData, "name");
	
	std::cout << "<br>getEnvLen: " << getenv("CONTENT_LENGTH");
	std::cout << "<br>getPostDataLen: " << strlen(postData);
	return 0;
}