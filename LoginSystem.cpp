#include "LoginSystem.h"
#include "UserManager.h"
#include <iostream>
#include <cstdlib>
#include <limits>
using namespace std;

void LoginSystem::displayMenu() {
    UserManager user;
    int choice;

    while (true) {
        system("cls");
        cout << "***********************************************************************\n\n";
        cout << "                      Welcome to Login Page                            \n\n";
        cout << "*******************        MENU        *******************************\n\n";
        cout << "1. LOGIN" << endl;
        cout << "2. REGISTER" << endl;
        cout << "3. FORGOT PASSWORD (or) USERNAME" << endl;
        cout << "4. EXIT" << endl;

        while (true) {
            cout << "\nEnter your choice: ";
            if (!(cin >> choice)) {
                cout << "\nInvalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            switch (choice) {
            case 1:
                user.login();
                break;
            case 2:
                user.registerUser();
                break;
            case 3:
                user.forgot();
                break;
            case 4:
                cout << "Thanks for using this program.\n";
                exit(0);
            default:
                cout << "Invalid choice, please try again.\n";
                continue;
            }
            break;
        }
    }
}
