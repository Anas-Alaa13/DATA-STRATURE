#include "Student.h"
#include "LoginSystem.h"

#include"Course.h"
#include <iostream>
#include<sstream>
#include<fstream>
#include<algorithm>
#include "UserManager.h"
#include <set>
using namespace std;
Student::Student() {}
void Student::setUsername(const std::string& user) {
    username = user;
}
void Student::displayMenu() {
    int choice;
    while (true) {
        system("cls");
        cout << "***********************************************************************\n\n";
        cout << "                      Welcome Yaaa TaleB                            \n\n";
        cout << "*******************        MENU        *******************************\n\n";
        cout << "1. Serch For Courses " << endl;
        cout << "2. Regester" << endl;
        cout << "3. viewRegisteredCourses"<<endl;
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

            UserManager user;
            switch (choice) {
            case 1:
                findcourse();
                break;
            case 2:
                registercourse();
                break;
            case 3:
                viewRegisteredCourses();
                    break;
                case 4:
                    cout << "Salaaaam Yaaa TaleB.\n";
                    LoginSystem l;
                    l.displayMenu();
             break;
            default:
                cout << "Invalid choice, please try again.\n";
                continue;
            }
            break;
        }
    }
}
bool Student::findcourse() {
}
void Student::registercourse() { 
}
void Student::viewRegisteredCourses() {  
}

