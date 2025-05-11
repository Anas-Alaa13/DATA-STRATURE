#include "LoginSystem.h"
#include "UserManager.h"
#include "Student.h"
#include "Admin.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>

using namespace std;

LoginSystem::LoginSystem(DataManager& data) : dm(data) {}

void LoginSystem::displayMenu() {
    UserManager user;
    int choice;
    while (true) {
        system("cls");
        cout << "\t\t\t---------------------------------\n";
        cout << "\t\t\t   STUDENT MANAGEMENT SYSTEM\n";
        cout << "\t\t\t---------------------------------\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Forgot Password\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            user.login(dm);
            break;
        case 2:
            user.registerUser(dm);
            break;
        case 3:
            user.forgot(dm);
            break;
        case 4:
            cout << "Thanks for using this program.\n";
            dm.saveAllData(); 
            exit(0);
        default:
            cout << "Invalid choice, please try again.\n";
        }
    }
}