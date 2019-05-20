#include <iostream>

char* getValue(char *str, char *key) {
     int end = 0;
     str++;
     while(*str && *str != *key) str++;
     if (*str == *key) {
        while(*key && *str && *(str) == *(key)) {
            std::cout << "Str: " << *str << " Key: " << *key << std::endl;
            str++;
            key++;
            
            if (!*key) {
                // It works!
                // Now get the next value
                str++;
                for (end = 0; *str && str[end] != '&'; end++);
                str[end] = '\0';
                return str;
            }
        }
        return NULL;
     }
     
     return NULL;
}


int main() {
    char str[] = "?name=test&password=test2";
    
    std::cout << "Result: " << getValue(str, "name") << std::endl;
    
    system("pause");
    return 0;
}
