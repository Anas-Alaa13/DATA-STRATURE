#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <limits>
using namespace std;







void UserManager::login() {
    string username, password, storedUser, storedPass;
    string id, fName, lName, phone, email;
    bool isLoggedIn = false;

    system("cls");
    cout << "Please enter the following details:\n";
    cout << "USERNAME: ";
    cin >> username;
    cout << "PASSWORD: ";
    cin >> password;

    ifstream input("database.txt");
    while (input >> id >> fName >> lName >> phone >> storedUser >> storedPass >> email) {
        if (storedUser == username && storedPass == password) {
            isLoggedIn = true;
            break;
        }
    }
    input.close();

    if (isLoggedIn) {
        cout << "\nHello " << username << "\n<LOGIN SUCCESSFUL>\nThanks for logging in..\n";
    }
    else {
        cout << "\nLOGIN ERROR\nPlease check your username and password.\n";
    }
    system("pause");
}

void UserManager::registerUser() {
    int id = 1;
    string username, password, confirmPassword, PhoneNumber, Email, FirstName, LastName;

    ifstream input("database.txt");
    string line, lastId;
    while (getline(input, line)) {
        istringstream iss(line);
        iss >> lastId;
    }
    input.close();

    if (!lastId.empty()) {
        id = stoi(lastId) + 1;
    }

    system("cls");
    cout << "Please enter the following details:\n";
    cout << " Enter the First Name: ";
    cin >> FirstName;
    cout << " Enter the Last Name: ";
    cin >> LastName;
    cout << " Enter the Phone Number: ";
    cin >> PhoneNumber;
    cout << " Enter the Email: ";
    cin >> Email;
    cout << " Enter the username: ";
    cin >> username;
    cout << " Enter the password: ";
    cin >> password;
    while (true) {
        cout << " Confirm the password: ";
        cin >> confirmPassword;

        if (password == confirmPassword) {
            break;
        }
        else {
            cout << "\nPasswords do not match. Please try again.\n";
        }

}
        ofstream reg("database.txt", ios::app);
        reg << id << ' ' << FirstName << ' ' << LastName << ' ' << PhoneNumber << ' ' << username << ' ' << password << ' ' << Email << endl;
        reg.close();
        /*ofstream reg("database.csv", ios::app);
  reg << id << ',' << FirstName << ',' << LastName << ',' << PhoneNumber << ',' << username << ',' << password << ',' << Email << '\n';
        */
        cout << "\nRegistration Successful\n";
        system("pause");
    }

void UserManager::forgot() {
    int choice;
    system("cls");
    cout << "Forgotten? We're here to help.\n";

    while (true) {
        cout << "1. Search your ID by username\n";
        cout << "2. Search your ID by password\n";
        cout << "3. Main menu\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "\nInvalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1: {
            string searchUser, storedUser, storedPass;
            string id, fName, lName, phone, email;
            bool found = false;

            cout << "\nEnter your remembered username: ";
            cin >> searchUser;

            ifstream search("database.txt");
            while (search >> id >> fName >> lName >> phone >> storedUser >> storedPass >> email) {
                if (storedUser == searchUser) {
                    found = true;
                    cout << "\nAccount found!\nYour password is: " << storedPass << endl;
                    break;
                }
            }
            search.close();

            if (!found) {
                cout << "\nSorry, your username is not found in our database.\n";
            }
            system("pause");
            break;
        }
        case 2: {
            string searchPass, storedUser, storedPass;
            string id, fName, lName, phone, email;
            bool found = false;

            cout << "\nEnter your remembered password: ";
            cin >> searchPass;

            ifstream search("database.txt");
            while (search >> id >> fName >> lName >> phone >> storedUser >> storedPass >> email) {
                if (storedPass == searchPass) {
                    found = true;
                    cout << "\nPassword found!\nYour username is: " << storedUser << endl;
                    break;
                }
            }
            search.close();

            if (!found) {
                cout << "\nSorry, your password is not found in our database.\n";
            }
            system("pause");
            break;
        }
        case 3:
            return;
        default:
            cout << "\nInvalid choice, please try again.\n";
            system("pause");
        }
    }
}
