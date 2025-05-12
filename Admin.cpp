#include "Admin.h"
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

Admin::Admin(DataManager& dm) : dm(dm) {}


//Anas
void Admin::displayMenu() {
    int choice;
    while (true) {
        system("cls");
        cout << "***********************************************************************\n\n";
        cout << "                      Welcome Yaaa Admin                            \n\n";
        cout << "*******************        MENU        *******************************\n\n";
        cout << "1. UploadCourse " << endl;
        cout << "2. Set Prerequisites" << endl;
        cout << "3. Edit Student Data " << endl;
        cout << "4. Show Courses " << endl;
        cout << "5. Manage Student Grade " << endl;
        cout << "6. Delete user " << endl;
        cout << "7. EXIT" << endl;

        string inputStr;
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
            UploadCourse();
            break;
        case 2:
            SetPrerequisites();
            break;
        case 3:
            editStudentData();
            break;  
        case 4:
                ShowCourses();
                break;
        case 5:
            manageStudentGrades();
            break;
        case 6:
            deleteUser();
            break;
        case 7:
            cout << "Salaaaam Yaaa Admin.\n";
            return;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    }
}
void Admin::deleteUser() {
    cout << "\nList of Users:\n";
    cout << "-----------------------------------\n";
    for (const auto& user : dm.users) {
        cout << "ID: " << user.ID << " | Username: " << user.Username << " | Name: " << user.FirstName << " " << user.LastName << "\n";
    }
    cout << "-----------------------------------\n";
    cout << "Enter the ID of the user you want to delete: ";
    string targetID;
    cin >> targetID;

    int id = stoi(targetID);
    auto it = find_if(dm.users.begin(), dm.users.end(), [id](const User& u) { return u.ID == id; });
    if (it != dm.users.end()) {
        dm.users.erase(it);
        cout << "User removed from users list.\n";

        dm.registrations.erase(id);
        cout << "User removed from registrations.\n";

        dm.grades.erase(remove_if(dm.grades.begin(), dm.grades.end(), [id](const Grade& g) { return g.ID == id; }), dm.grades.end());
        cout << "User removed from grades.\n";

        cout << "User deletion process completed.\n";
    }
    else {
        cout << "Invalid ID. No user found with the given ID.\n";
    }
    system("pause");
}
void Admin::editStudentData() {
    system("cls");
    cout << "=== Edit Student Data ===\n";

    cout << "\nList of all students:\n";
    cout << "------------------------\n";
    for (const auto& user : dm.users) {
        if (user.Username != "admin") {
            cout << "- Username: " << user.Username << " | Name: " << user.FirstName << " " << user.LastName << " | ID: " << user.ID << endl;
        }
    }

    string targetUsername;
    cout << "\nEnter the username of the student you want to edit: ";
    cin >> targetUsername;

    auto it = find_if(dm.users.begin(), dm.users.end(), [&targetUsername](const User& u) { return u.Username == targetUsername; });
    if (it != dm.users.end()) {
        User& student = *it;
        cout << "\nStudent found!\n";
        cout << "ID: " << student.ID << "\n";
        cout << "First Name: " << student.FirstName << "\n";
        cout << "Last Name: " << student.LastName << "\n";
        cout << "Phone: " << student.PhoneNumber << "\n";
        cout << "Username: " << student.Username << "\n";
        cout << "Password: " << student.Password << "\n";
        cout << "Email: " << student.Email << "\n";

        string input;
        cout << "\nChange ID? (y/n): ";
        cin >> input;
        if (input == "y") {
            cout << "Enter new ID: ";
            cin >> student.ID;
        }
        cout << "Change First Name? (y/n): ";
        cin >> input;
        if (input == "y") {
            cout << "Enter new First Name: ";
            cin >> student.FirstName;
        }
        cout << "Change Last Name? (y/n): ";
        cin >> input;
        if (input == "y") {
            cout << "Enter new Last Name: ";
            cin >> student.LastName;
        }
        cout << "Change Phone? (y/n): ";
        cin >> input;
        if (input == "y") {
            cout << "Enter new Phone: ";
            cin >> student.PhoneNumber;
        }
        cout << "Change Username? (y/n): ";
        cin >> input;
        if (input == "y") {
            cout << "Enter new Username: ";
            cin >> student.Username;
        }
        cout << "Change Password? (y/n): ";
        cin >> input;
        if (input == "y") {
            cout << "Enter new Password: ";
            cin >> student.Password;
        }
        cout << "Change Email? (y/n): ";
        cin >> input;
        if (input == "y") {
            cout << "Enter new Email: ";
            cin >> student.Email;
        }

        cout << "\nStudent data updated.\n";
    }
    else {
        cout << "\nUsername not found.\n";
    }
    system("pause");
}


//Framawy-Ahmed
void Admin::ShowCourses() {
    cout << "\nCurrent Courses List:\n---------------------------------------\n";
    int i = 1;
    for (const auto& course : dm.courses) {
        cout << i++ << ". Title: " << course.title << " | Syllabus: " << course.syllabus
            << " | Credit Hours: " << course.creditHours << " | Instructor: " << course.instructor
            << " | Prerequisites: " << course.prerequisites << endl;
    }
    cout << "---------------------------------------\n";
}
bool Admin::isValidPrerequisites(const string& prereqList) {
    stringstream ss(prereqList);
    string prereq;
    while (getline(ss, prereq, ',')) {
        prereq.erase(remove_if(prereq.begin(), prereq.end(), ::isspace), prereq.end());
        bool found = false;
        for (size_t i = 0; i < dm.courses.size(); ++i) {
            const auto& course = dm.courses[i];
            if (course.title == prereq) {
                found = true;
                break;
            }
        }
        if (!found && !prereq.empty()) {
            cout << "Warning: prerequisite '" << prereq << "' is not a valid course title.\n";
            return false;
        }
    }
    return true;
}
void Admin::UpdatePrerequisites() {
    string answer;
    do {
        string courseToUpdate;
        cout << "Enter title of the course to update prerequisites for: ";
        getline(cin, courseToUpdate);

        auto it = find_if(dm.courses.begin(), dm.courses.end(), [&courseToUpdate](const Course& c) { return c.title == courseToUpdate; });
        if (it == dm.courses.end()) {
            cout << "Warning: Course title '" << courseToUpdate << "' is not a valid course title.\n";
            return;
        }

        cout << "Enter new prerequisites (comma separated, leave empty for none): ";
        string newPrereq;
        getline(cin, newPrereq);
        if (isValidPrerequisites(newPrereq)) {
            it->prerequisites = newPrereq;
            cout << "Prerequisites updated for " << courseToUpdate << ".\n";
        }
        else {
            cout << "Invalid prerequisites for " << courseToUpdate << ".\n";
        }

        cout << "Do you want to update prerequisites for another course? (Y = Yes, N = No): ";
        getline(cin, answer);
    } while (answer == "Y" || answer == "y");
}
void Admin::SetPrerequisites() {
    system("cls");
    cout << "--- Set Course Prerequisites ---\n";
    ShowCourses(); 

    cout << "Enter the title of the course to set prerequisites: ";
    string courseTitle;
    getline(cin, courseTitle);

    bool found = false;
    for (auto& course : dm.courses) {
        if (course.title == courseTitle) {
            found = true;
            cout << "Enter prerequisites for '" << course.title << "' (comma separated, leave empty for none): ";
            string prereqs;
            getline(cin, prereqs);

            if (isValidPrerequisites(prereqs)) {
                course.prerequisites = prereqs;
                cout << " Prerequisites updated successfully.\n";
                dm.writeCourses("courses.csv"); 
            }
            else {
                cout << " Invalid prerequisites. Update failed.\n";
            }
            break;
        }
    }

    if (!found) {
        cout << "❌ Course not found.\n";
    }

    system("pause");
}
void Admin::UploadCourse() {
    Course newCourse;
    cout << "\n--- Add New Course ---\n";
    cout << "Enter course title: ";
    getline(cin, newCourse.title);
    for (const auto& course : dm.courses) {
        if (course.title == newCourse.title) {
            cout << "Error: Course with title '" << newCourse.title << "' already exists.\n";
            system("pause");
            return;
        }
    }
    cout << "Enter syllabus: ";
    getline(cin, newCourse.syllabus);
    cout << "Enter credit hours: ";
    getline(cin, newCourse.creditHours);
    cout << "Enter instructor name: ";
    getline(cin, newCourse.instructor);

    // Initially, prerequisites are empty
    newCourse.prerequisites = "";

    dm.courses.push_back(newCourse);
    cout << "New course added successfully! You can set prerequisites separately.\n";

    system("pause");
}





//Nabil
float Admin::calculateGPA(int total) {
    if (total >= 90) return 4.0;
    if (total >= 80) return 3.0;
    if (total >= 70) return 2.0;
    if (total >= 60) return 1.0;
    return 0.0;
}
void Admin::manageStudentGrades() {
    system("cls");
    cout << "=== Manage Student Grades ===\n";

    cout << "\nList of Students (IDs):\n";
    for (const auto& user : dm.users) {
        if (user.Username != "admin") {
            cout << "- " << user.ID << endl;
        }
    }

    string targetID;
    cout << "\nEnter student ID to enter grades for: ";
    cin >> targetID;

    int id = stoi(targetID);
    auto it = find_if(dm.users.begin(), dm.users.end(), [id](const User& u) { return u.ID == id; });
    if (it == dm.users.end()) {
        cout << "\n ID not found!\n";
        system("pause");
        return;
    }

    vector<string> subjects = dm.registrations[id];
    if (subjects.empty()) {
        cout << "No subjects registered for this student.\n";
        system("pause");
        return;
    }

    cout << "\n Subjects registered for student " << targetID << ":\n";
    for (const string& subj : subjects) cout << "- " << subj << endl;

    string selectedSubject;
    cin.ignore();
    cout << "\nEnter subject name to enter grades for: ";
    getline(cin, selectedSubject);

    if (find(subjects.begin(), subjects.end(), selectedSubject) == subjects.end()) {
        cout << "❌ Invalid subject for this student.\n";
        system("pause");
        return;
    }

    auto gradeIt = find_if(dm.grades.begin(), dm.grades.end(), [id, &selectedSubject](const Grade& g) {
        return g.ID == id && g.Subject == selectedSubject;
        });

    if (gradeIt != dm.grades.end()) {
        cout << "Grades already exist for this subject.\n";
        cout << "Do you want to overwrite them? (y/n): ";
        char c;
        cin >> c;
        if (c != 'y' && c != 'Y') {
            cout << "Skipping...\n";
            system("pause");
            return;
        }
    }

    int quiz, assignment, midterm, practical, finalExam, total = 0;
    do {
        cout << "\nEnter Quiz (0-10): ";
        while (!(cin >> quiz) || quiz < 0 || quiz > 10) { cin.clear(); cin.ignore(1000, '\n'); cout << "Try again: "; }

        cout << "Enter Assignment (0-10): ";
        while (!(cin >> assignment) || assignment < 0 || assignment > 10) { cin.clear(); cin.ignore(1000, '\n'); cout << "Try again: "; }

        cout << "Enter Midterm (0-15): ";
        while (!(cin >> midterm) || midterm < 0 || midterm > 15) { cin.clear(); cin.ignore(1000, '\n'); cout << "Try again: "; }

        cout << "Enter Practical (0-20): ";
        while (!(cin >> practical) || practical < 0 || practical > 20) { cin.clear(); cin.ignore(1000, '\n'); cout << "Try again: "; }

        cout << "Enter Final (0-60): ";
        while (!(cin >> finalExam) || finalExam < 0 || finalExam > 60) { cin.clear(); cin.ignore(1000, '\n'); cout << "Try again: "; }

        total = quiz + assignment + midterm + practical + finalExam;
        if (total > 100) cout << " Total exceeds 100. Try again.\n";
    } while (total > 100);

    float gpa = calculateGPA(total);

    if (gradeIt != dm.grades.end()) {
        gradeIt->Quiz = quiz;
        gradeIt->Assignment = assignment;
        gradeIt->Midterm = midterm;
        gradeIt->Practical = practical;
        gradeIt->Final = finalExam;
        gradeIt->Total = total;
        gradeIt->GPA = gpa;
    }
    else {
        Grade newGrade = { id, selectedSubject, quiz, assignment, midterm, practical, finalExam, total, gpa };
        dm.grades.push_back(newGrade);
    }

    cout << "\n Grades saved for " << selectedSubject << " (Student: " << targetID << ")\n";
    system("pause");
}
