// Anas

#include "UserManager.h"
#include "Admin.h"
#include "Student.h"
#include "Course.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
using namespace std;

void UserManager::login()
{
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
    while (getline(input, line))
    {
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, fname, ',');
        getline(ss, lname, ',');
        getline(ss, phone, ',');
        getline(ss, storedUser, ',');
        getline(ss, storedPass, ',');
        getline(ss, email, ',');

        if (storedUser == username && storedPass == password)
        {
            isLoggedIn = true;
            if (username == "admin")
            {
                Admin admin;
                admin.displayMenu();
            }
            else
            {
                Student student;
                student.setUsername(username);
                student.setStudentID(stoi(id));
                student.displayMenu();
            }
            break;
        }
    }
    input.close();

    if (isLoggedIn)
    {
        cout << "\nHello " << username << "\n<LOGIN SUCCESSFUL>\nThanks for logging in..\n";
    }
    else
    {
        cout << "\nLOGIN ERROR\nPlease check your username and password.\n";
    }
    system("pause");
}
void UserManager::registerUser()
{
    int id = 1;
    string username, password, confirmPassword, PhoneNumber, Email, FirstName, LastName;

    ifstream input("database.csv");
    string line;
    getline(input, line);
    int maxID = 0;
    while (getline(input, line))
    {
        if (!line.empty())
        {
            stringstream ss(line);
            string temp;
            getline(ss, temp, ',');
            int currentID = stoi(temp);
            if (currentID > maxID)
            {
                maxID = currentID;
            }
        }
    }
    input.close();
    id = maxID + 1;

    system("cls");
    cout << "Please enter the following details:\n";
    cout << " Enter the First Name: ";
    cin >> FirstName;
    cout << " Enter the Last Name: ";
    cin >> LastName;

    while (true)
    {
        cout << " Enter the Phone Number: ";
        cin >> PhoneNumber;
        bool isValid = PhoneNumber.length() == 11;
        for (char c : PhoneNumber)
        {
            if (!isdigit(c))
            {
                isValid = false;
                break;
            }
        }
        if (isValid)
            break;
        cout << "\nInvalid phone number. It must be exactly 11 digits.\n";
    }

    cout << " Enter the Email: ";
    cin >> Email;

    while (true)
    {
        cout << " Enter the username: ";
        cin >> username;
        if (username == "admin")
        {
            id = 0;
        }

        ifstream checkUsername("database.csv");
        getline(checkUsername, line);
        bool userExists = false;
        while (getline(checkUsername, line))
        {
            stringstream ss(line);
            string temp;
            for (int i = 0; i < 4; ++i)
                getline(ss, temp, ',');
            getline(ss, temp, ',');
            if (temp == username)
            {
                userExists = true;
                break;
            }
        }
        checkUsername.close();

        if (userExists)
        {
            cout << "\nUsername already exists. Please try another one.\n";
        }
        else
        {
            break;
        }
    }

    while (true)
    {
        cout << " Enter the password (min 8 characters): ";
        cin >> password;
        if (password.length() >= 8)
            break;
        cout << "\nPassword too short. Please enter at least 8 characters.\n";
    }

    while (true)
    {
        cout << " Confirm the password: ";
        cin >> confirmPassword;
        if (password == confirmPassword)
            break;
        cout << "\nPasswords do not match. Please try again.\n";
    }

    struct UserData
    {
        int ID;
        string FirstName, LastName, PhoneNumber, Username, Password, Email;
    };

    vector<UserData> users;
    ifstream readFile("database.csv");
    string header;
    bool hasHeader = false;
    if (getline(readFile, header))
    {
        if (header.find("ID,") != string::npos)
        {
            hasHeader = true;
        }
        else
        {
            stringstream ss(header);
            UserData user;
            string temp;
            getline(ss, temp, ',');
            user.ID = stoi(temp);
            getline(ss, user.FirstName, ',');
            getline(ss, user.LastName, ',');
            getline(ss, user.PhoneNumber, ',');
            getline(ss, user.Username, ',');
            getline(ss, user.Password, ',');
            getline(ss, user.Email);
            users.push_back(user);
        }
    }

    while (getline(readFile, line))
    {
        stringstream ss(line);
        UserData user;
        string temp;
        getline(ss, temp, ',');
        user.ID = stoi(temp);
        getline(ss, user.FirstName, ',');
        getline(ss, user.LastName, ',');
        getline(ss, user.PhoneNumber, ',');
        getline(ss, user.Username, ',');
        getline(ss, user.Password, ',');
        getline(ss, user.Email);
        users.push_back(user);
    }
    readFile.close();

    users.push_back({id, FirstName, LastName, PhoneNumber, username, password, Email});

    sort(users.begin(), users.end(), [](const UserData &a, const UserData &b)
         { return a.ID < b.ID; });

    ofstream writeFile("database.csv");
    writeFile << "ID,FirstName,LastName,PhoneNumber,Username,Password,Email\n";
    for (const auto &user : users)
    {
        writeFile << user.ID << ',' << user.FirstName << ',' << user.LastName << ','
                  << user.PhoneNumber << ',' << user.Username << ',' << user.Password
                  << ',' << user.Email << '\n';
    }
    writeFile.close();

    cout << "\nRegistration Successful\n";
    if (username == "admin")
    {
        Admin admin;
        admin.displayMenu();
    }
    else
    {
        Student student;
        student.setUsername(username);
        student.displayMenu();
    }
    system("pause");
}
void UserManager::forgot()
{
    system("cls");
    cout << "Forgot your password? No problem, let's reset it.\n";

    string searchUser, searchPhone, line;
    string id, fname, lname, phone, storedUser, storedPass, email;
    bool found = false;

    cout << "\nEnter your username: ";
    cin >> searchUser;

    cout << "Enter your phone number: ";
    cin >> searchPhone;

    ifstream infile("database.csv");
    ofstream temp("temp.csv");

    while (getline(infile, line))
    {
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, fname, ',');
        getline(ss, lname, ',');
        getline(ss, phone, ',');
        getline(ss, storedUser, ',');
        getline(ss, storedPass, ',');
        getline(ss, email, ',');

        if (storedUser == searchUser && phone == searchPhone)
        {
            found = true;

            cout << "\nAccount found!\n";
            cout << "Name: " << fname << " " << lname << endl;
            cout << "Email: " << email << endl;

            string newPass;
            cout << "\nPlease enter your new password: ";
            cin >> newPass;

            temp << id << "," << fname << "," << lname << "," << phone << ","
                 << storedUser << "," << newPass << "," << email << endl;
        }
        else
        {
            temp << id << "," << fname << "," << lname << "," << phone << ","
                 << storedUser << "," << storedPass << "," << email << endl;
        }
    }

    infile.close();
    temp.close();

    remove("database.csv");
    rename("temp.csv", "database.csv");

    if (!found)
    {
        cout << "\nSorry, the username or phone number you entered is incorrect.\n";
    }
    else
    {
        cout << "\nYour password has been updated successfully!\n";
    }

    system("pause");
}
