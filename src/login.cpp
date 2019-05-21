#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct Account{
    char user[100+1];
    char password[100+1];
    int id;
};
struct Appointment{
    char date[8+1];
    char time[5+1];
    char description[100+1];
};

int main()
{   int i =0;
    struct Account accounts[3];

    strcpy(accounts[0].user,"user");
    strcpy(accounts[0].password,"password");
    strcpy(accounts[1].user,"user1");
    strcpy(accounts[1].password,"password1");
    strcpy(accounts[2].user,"user2");
    strcpy(accounts[2].password,"password2");

    /*Passwort prüfung erste "Vorlage"*/
   /* bool accountsinSuccess = false;
    char dummy[100+1];
    do{
        cout << "Username:\n";
        cin >> accounts.user;
        cout << "Password:\n";
        cin >> accounts.password;

        if(accounts.user == "user" && accounts.password == "password" ){
            cout << "Die Anmeldung war erfolgreich.\n";
            bool accountsinSuccess = true;
            break;
        }
        else{
            cout << "Username or password incorrect!\n";
            cout << "Please try to accountsin again.\n";
        }
    }while(!accountsinSuccess);*/

    return 0;
}
