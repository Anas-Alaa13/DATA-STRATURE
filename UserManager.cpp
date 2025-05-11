#include "UserManager.h"
#include "Admin.h"
#include "Student.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

void UserManager::login(DataManager& dm) {
    string username, password;
    system("cls");
    cout << "Please enter the following details:\n";
    cout << "USERNAME: ";
    cin >> username;
    cout << "PASSWORD: ";
    cin >> password;

    bool isLoggedIn = false;
    for (const auto& user : dm.users) {
        if (user.Username == username && user.Password == password) {
            isLoggedIn = true;
            if (username == "admin") {
                Admin admin(dm);
                admin.displayMenu();
            }
            else {
                Student student(dm);
                student.setUsername(username);
                student.setStudentID(user.ID);
                student.displayMenu();
            }
            break;
        }
    }

    if (isLoggedIn) {
        cout << "\nHello " << username << "\n<LOGIN SUCCESSFUL>\nThanks for logging in..\n";
    }
    else {
        cout << "\nLOGIN ERROR\nPlease check your username and password.\n";
    }
    system("pause");
}

void UserManager::registerUser(DataManager& dm) {
    int id = dm.users.empty() ? 1 : dm.users.back().ID + 1;
    string username, password, confirmPassword, PhoneNumber, Email, FirstName, LastName;

    system("cls");
    cout << "Enter First Name: ";
    cin >> FirstName;
    cout << "Enter Last Name: ";
    cin >> LastName;
    cout << "Enter Phone Number: ";
    cin >> PhoneNumber;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Confirm Password: ";
    cin >> confirmPassword;
    cout << "Enter Email: ";
    cin >> Email;

    if (password != confirmPassword) {
        cout << "\nPasswords do not match!\n";
        system("pause");
        return;
    }

    bool userExists = false;
    for (const auto& user : dm.users) {
        if (user.Username == username) {
            userExists = true;
            break;
        }
    }
    if (userExists) {
        cout << "\nUsername already exists. Please try another one.\n";
        system("pause");
        return;
    }

    User newUser{ id, FirstName, LastName, PhoneNumber, username, password, Email };
    dm.users.push_back(newUser);

    cout << "\nRegistration Successful\n";
    if (username == "admin") {
        Admin admin(dm);
        admin.displayMenu();
    }
    else {
        Student student(dm);
        student.setUsername(username);
        student.setStudentID(id);
        student.displayMenu();
    }
    system("pause");
}

void UserManager::forgot(DataManager& dm) {
    system("cls");
    cout << "Forgot your password? No problem, let's reset it.\n";

    string searchUser, searchPhone;
    cout << "\nEnter your username: ";
    cin >> searchUser;
    cout << "Enter your phone number: ";
    cin >> searchPhone;

    bool found = false;
    for (auto& user : dm.users) {
        if (user.Username == searchUser && user.PhoneNumber == searchPhone) {
            found = true;
            cout << "\nAccount found!\n";
            cout << "Name: " << user.FirstName << " " << user.LastName << endl;
            cout << "Email: " << user.Email << endl;

            string newPass;
            cout << "\nPlease enter your new password: ";
            cin >> newPass;
            user.Password = newPass;
            cout << "\nYour password has been updated successfully!\n";
            break;
        }
    }

    if (!found) {
        cout << "\nSorry, the username or phone number you entered is incorrect.\n";
    }
    system("pause");
}