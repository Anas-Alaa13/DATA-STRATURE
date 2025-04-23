#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include "Course.h"
#include<unordered_map>


using namespace std;
Admin::Admin() {
    // Constructor implementation (can be empty if no initialization is needed)
    // Constructor implementation (can be empty if no initialization is needed)
}

void Admin::displayMenu() {
    int choice;
    while (true) {
        system("cls");
        cout << "***********************************************************************\n\n";
        cout << "                      Welcome Yaaa Admin                            \n\n";
        cout << "*******************        MENU        *******************************\n\n";
        cout << "1. UploadCourse " << endl;
        cout << "2. Set Prerequistes" << endl;
        cout << "3. Manage Student Grade " << endl;
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
                uploadCourse("courses.csv");
                break;
            /*case 2:
                Set_Prerequistes();
                break;
            case 3:
                Manage_Student_Grade();
                break;*/
            case 4:
                cout << "Salaaaam Yaaa Admin.\n";
                exit(0);
            default:
                cout << "Invalid choice, please try again.\n";
                continue;
            }
            break;
        }
    }
}




unordered_map<int, Course>courses;
void Admin::uploadCourse(const string& filename) {
    string title, syllabus, instructor;
    int creditHours,code;
    cout << "Enter course title: ";
    getline(cin, title);
    cout << "Enter course code: ";
    cin >> code;
    cin.ignore();
    cout << "Enter syllabus: ";
    getline(cin, syllabus);
    cout << "Enter credit hours: ";
    cin >> creditHours;
    cin.ignore();
    cout << "Enter instructor name: ";
    getline(cin, instructor);


    Course newCourse(title, syllabus, creditHours, instructor);
    courses.insert(make_pair(code, newCourse));

        newCourse.saveToFile(filename);
}
