#include "LoginSystem.h"
#include "UserManager.h"
#include "Student.h"
#include "Admin.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
using namespace std;

void LoginSystem::displayMenu() {
    UserManager user;
    while (true) {
        system("cls");
        cout << "***********************************************************************\n\n";
        cout << "                      Welcome to Login Page                            \n\n";
        cout << "*******************        MENU        *******************************\n\n";
        cout << "1. LOGIN" << endl;
        cout << "2. REGISTER" << endl;
        cout << "3. FORGOT PASSWORD ?? " << endl;
        cout << "4. EXIT" << endl;

        while (true) {
            cout << "\nEnter your choice: ";
            string inputStr;
            int choice;

            while (true) {
                cout << "Enter your choice: ";
                getline(cin, inputStr);  

                bool isNumber = true;
                for (char ch : inputStr) {
                    if (!isdigit(ch)) {
                        isNumber = false;
                        break;
                    }
                }

                if (isNumber && !inputStr.empty()) {
                    choice = stoi(inputStr);  
                    break;
                }
                else {
                    cout << "\nInvalid input. Please enter a valid number.\n";
                }
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
