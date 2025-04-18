#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <limits>
#include <algorithm>
using namespace std;





void UserManager::login() {
    string username, password, line;
    string id, fname, lname, phone, storedUser, storedPass, email;
    bool isLoggedIn = false;

    system("cls");
    cout << "Please enter the following details:\n";
    cout << "USERNAME: ";
    cin >> username;
    cout << "PASSWORD: ";
    cin >> password;

    ifstream input("database.csv");
    while (getline(input, line)) {
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, fname, ',');
        getline(ss, lname, ',');
        getline(ss, phone, ',');
        getline(ss, storedUser, ',');
        getline(ss, storedPass, ',');
        getline(ss, email, ',');

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

    ifstream input("database.csv");
    string line, lastLine;
    while (getline(input, line)) {
        if (!line.empty() && line.find(',') != string::npos) {
            lastLine = line;
        }
    }
    input.close();

    if (!lastLine.empty()) {
        stringstream ss(lastLine);
        string lastId;
        getline(ss, lastId, ',');
        id = stoi(lastId) + 1;
    }

    system("cls");
    cout << "Please enter the following details:\n";
    cout << " Enter the First Name: ";
    cin >> FirstName;
    cout << " Enter the Last Name: ";
    cin >> LastName;
    while (true) {
        cout << " Enter the Phone Number: ";
        cin >> PhoneNumber;
        bool isValid = true;
        if (PhoneNumber.length() != 11) {
            isValid = false;
        }
        else {
            for (int i = 0; i < 11; i++) {
                if (!isdigit(PhoneNumber[i])) {
                    isValid = false;
                    break;
                }
            }
        }
        if (isValid) {
            break;
        }
        else {
            cout << "\nInvalid phone number. It must be exactly 11 digits.\n";
        }
    }

    cout << " Enter the Email: ";
    cin >> Email;
    while (true) {
        cout << " Enter the username: ";
        cin >> username;
        ifstream checkUsername("database.csv");
        getline(checkUsername, line); 
        bool userExists = false;
        while (getline(checkUsername, line)) {
            stringstream ss(line);
            string temp;
            for (int i = 0; i < 4; ++i) getline(ss, temp, ','); 
            getline(ss, temp, ','); 
            if (temp == username) {
                userExists = true;
                break;
            }
        }
        checkUsername.close();

        if (userExists) {
            cout << "\nUsername already exists. Please try another one.\n";
        }
        else {
            break;
        }
    }
    while (true) {
        cout << " Enter the password (min 8 characters): ";
        cin >> password;

        if (password.length() >= 8) {
            break;
        }
        else {
            cout << "\nPassword too short. Please enter at least 8 characters.\n";
        }
    }

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

    ifstream checkFile("database.csv");
    bool isEmpty = checkFile.peek() == ifstream::traits_type::eof();
    checkFile.close();

    ofstream reg("database.csv", ios::app);
    if (isEmpty) {
        reg << "ID,FirstName,LastName,PhoneNumber,Username,Password,Email\n"; 
    }

    reg << id << ',' << FirstName << ',' << LastName << ',' << PhoneNumber << ',' << username << ',' << password << ',' << Email << '\n';
    reg.close();

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
        case 1: {
            string searchUser, line;
            string id, fname, lname, phone, storedUser, storedPass, email;
            bool found = false;

            cout << "\nEnter your remembered username: ";
            cin >> searchUser;

            ifstream search("database.csv");
            while (getline(search, line)) {
                stringstream ss(line);
                getline(ss, id, ',');
                getline(ss, fname, ',');
                getline(ss, lname, ',');
                getline(ss, phone, ',');
                getline(ss, storedUser, ',');
                getline(ss, storedPass, ',');
                getline(ss, email, ',');

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
            string searchPass, line;
            string id, fname, lname, phone, storedUser, storedPass, email;
            bool found = false;

            cout << "\nEnter your remembered password: ";
            cin >> searchPass;

            ifstream search("database.csv");
            while (getline(search, line)) {
                stringstream ss(line);
                getline(ss, id, ',');
                getline(ss, fname, ',');
                getline(ss, lname, ',');
                getline(ss, phone, ',');
                getline(ss, storedUser, ',');
                getline(ss, storedPass, ',');
                getline(ss, email, ',');

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
