#include "Admin.h"
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <queue>  
#include <map>
#include <unordered_set>
#include <stack>
#include <unordered_map>
#include <list>
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
stack <User> deletedUsers; 
    cout << "\nList of Users:\n";
    cout << "-----------------------------------\n";

    map<int, User*> userMap;
    unordered_set<int> idSet;

    for (auto& user : dm.users) {
        cout << "ID: " << user.ID << " | Username: " << user.Username
            << " | Name: " << user.FirstName << " " << user.LastName << "\n";
        userMap[user.ID] = &user;
        idSet.insert(user.ID);
    }

    cout << "-----------------------------------\n";
    cout << "Enter the ID of the user you want to delete: ";
    string targetID;
    cin >> targetID;

    int id;
    try {
        id = stoi(targetID);
    }
    catch (...) {
        cout << " Invalid input. Please enter a valid numeric ID.\n";
        system("pause");
        return;
    }

    if (idSet.find(id) == idSet.end()) {
        cout << " Invalid ID. No user found with the given ID.\n";
        system("pause");
        return;
    }
    auto it = find_if(dm.users.begin(), dm.users.end(), [id](const User& u) { return u.ID == id; });
    if (it != dm.users.end()) {
        deletedUsers.push(*it);  
        dm.users.erase(it);
        cout << " User removed from users list.\n";
    }
    if (dm.registrations.erase(id)) {
        cout << " User removed from registrations.\n";
    }

    auto before = dm.grades.size();
    dm.grades.erase(remove_if(dm.grades.begin(), dm.grades.end(),
        [id](const Grade& g) { return g.ID == id; }), dm.grades.end());
    if (before != dm.grades.size()) {
        cout << " User removed from grades.\n";
    }

    cout << " User deletion process completed.\n";

    cout << "Do you want to undo the deletion? (y/n): ";
    string choice;
    cin >> choice;
    if (choice == "y" || choice == "Y") {
        if (!deletedUsers.empty()) {
            dm.users.push_back(deletedUsers.top());  // رجع المستخدم
            deletedUsers.pop();
            cout << " Deletion undone. User restored.\n";
        }
    }

    system("pause");
}
void Admin::editStudentData()  {
    system("cls");
    cout << "=== Edit Student Data ===\n";
    map<string, User*> usernameMap;

    cout << "\nList of all students:\n";
    cout << "------------------------\n";

    for (auto& user : dm.users) {
        if (user.Username != "admin") {
            cout << "- Username: " << user.Username
                << " | Name: " << user.FirstName << " " << user.LastName
                << " | ID: " << user.ID << endl;

            usernameMap[user.Username] = &user; 
        }
    }

    string targetUsername;
    cout << "\nEnter the username of the student you want to edit: ";
    cin >> targetUsername;

    auto it = usernameMap.find(targetUsername);
    if (it != usernameMap.end()) {
        User* student = it->second;
        cout << "\nStudent found!\n";
        cout << "ID: " << student->ID << "\n";
        cout << "First Name: " << student->FirstName << "\n";
        cout << "Last Name: " << student->LastName << "\n";
        cout << "Phone: " << student->PhoneNumber << "\n";
        cout << "Username: " << student->Username << "\n";
        cout << "Password: " << student->Password << "\n";
        cout << "Email: " << student->Email << "\n";

        string input;
        cout << "\nChange ID? (y/n): ";
        cin >> input;
        if (input == "y") {
            cout << "Enter new ID: ";
            cin >> student->ID;
        }
        cout << "Change First Name? (y/n): ";
        cin >> input;
        if (input == "y") {
            cout << "Enter new First Name: ";
            cin >> student->FirstName;
        }
        cout << "Change Last Name? (y/n): ";
        cin >> input;
        if (input == "y") {
            cout << "Enter new Last Name: ";
            cin >> student->LastName;
        }
        cout << "Change Phone? (y/n): ";
        cin >> input;
        if (input == "y") {
            cout << "Enter new Phone: ";
            cin >> student->PhoneNumber;
        }

        cout << "Change Username? (y/n): ";
        cin >> input;
        if (input == "y") {
            string newUsername;
            cout << "Enter new Username: ";
            cin >> newUsername;

            set<string> existingUsernames;
            for (const auto& pair : usernameMap) {
                if (pair.first != student->Username) {
                    existingUsernames.insert(pair.first);
                }
            }

            if (existingUsernames.find(newUsername) != existingUsernames.end()) {
                cout << " Error: Username already exists.\n";
            }
            else {
                student->Username = newUsername;
                cout << " Username updated.\n";
            }
        }

        cout << "Change Password? (y/n): ";
        cin >> input;
        if (input == "y") {
            cout << "Enter new Password: ";
            cin >> student->Password;
        }

        cout << "Change Email? (y/n): ";
        cin >> input;
        if (input == "y") {
            cout << "Enter new Email: ";
            cin >> student->Email;
        }

        cout << "\n Student data updated.\n";
    }
    else {
        cout << "\n Username not found.\n";
    }

    system("pause");
}

//Framawy-Ahmed
void Admin::ShowCourses() {
    cout << "\nCurrent Courses List:\n---------------------------------------\n";

    queue<pair<int, Course>> courseQueue;
    int i = 1;
    for (const auto& course : dm.courses) {
        courseQueue.push({ i++, course });
    }
    while (!courseQueue.empty()) {
        auto entry = courseQueue.front();
        int index = entry.first;
        const Course& course = entry.second;

        cout << index << ". Title: " << course.title
            << " | Syllabus: " << course.syllabus
            << " | Credit Hours: " << course.creditHours
            << " | Instructor: " << course.instructor
            << " | Prerequisites: " << course.prerequisites << endl;

        courseQueue.pop();  
    }

    cout << "---------------------------------------\n";
	system("pause");
}
bool Admin::isValidPrerequisites(const string& prereqList) {
    unordered_set<string> courseTitles;
    for (const auto& course : dm.courses)
        courseTitles.insert(course.title);

    stringstream ss(prereqList);
    string prereq;

    while (getline(ss, prereq, ',')) {
        prereq.erase(remove_if(prereq.begin(), prereq.end(), ::isspace), prereq.end());
        if (!prereq.empty() && courseTitles.find(prereq) == courseTitles.end()) {
            cout << "Warning: prerequisite '" << prereq << "' is not a valid course title.\n";
            return false;
        }
    }
    return true;
}
void Admin::SetPrerequisites() {
    system("cls");
    cout << "--- Set Course Prerequisites ---\n";
    ShowCourses();

    cout << "Enter the title of the course to set prerequisites: ";
    string courseTitle;
    getline(cin, courseTitle);

    auto it = find_if(dm.courses.begin(), dm.courses.end(),
        [&courseTitle](const Course& c) { return c.title == courseTitle; });

    if (it != dm.courses.end()) {
        cout << "Enter prerequisites for '" << it->title << "' (comma separated, leave empty for none): ";
        string prereqs;
        getline(cin, prereqs);

        if (isValidPrerequisites(prereqs)) {
            it->prerequisites = prereqs;
            cout << "Prerequisites updated successfully.\n";
            dm.writeCourses("courses.csv");
        }
        else {
            cout << "Invalid prerequisites. Update failed.\n";
        }
    }
    else {
        cout << "❌ Course not found.\n";
    }

    system("pause");
}
void Admin::UploadCourse() {
    Course newCourse;
    cout << "\n--- Add New Course ---\n";
    cout << "Enter course title: ";
    getline(cin, newCourse.title);

    // نستخدم set للتحقق من وجود العنوان
    if (dm.courseTitles.find(newCourse.title) != dm.courseTitles.end()) {
        cout << "Error: Course with title '" << newCourse.title << "' already exists.\n";
        system("pause");
        return;
    }

    cout << "Enter syllabus: ";
    getline(cin, newCourse.syllabus);
    cout << "Enter credit hours: ";
    getline(cin, newCourse.creditHours);
    cout << "Enter instructor name: ";
    getline(cin, newCourse.instructor);

    newCourse.prerequisites = "";

    dm.courses.push_back(newCourse);
    dm.courseTitles.insert(newCourse.title); 

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
    unordered_map<int, string> idToUsername;
    for (const auto& user : dm.users) {
        if (user.Username != "admin") {
            cout << "- " << user.ID << endl;
            idToUsername[user.ID] = user.Username;
        }
    }

    string targetID;
    cout << "\nEnter student ID to enter grades for: ";
    cin >> targetID;

    int id;
    try {
        id = stoi(targetID);
    }
    catch (...) {
        cout << "Invalid input!\n";
        system("pause");
        return;
    }

    if (idToUsername.find(id) == idToUsername.end()) {
        cout << "\n❌ ID not found!\n";
        system("pause");
        return;
    }

    list<string> subjects;
    if (dm.registrations.count(id)) {
        subjects = std::list<std::string>(dm.registrations[id].begin(), dm.registrations[id].end());
    }

    if (subjects.empty()) {
        cout << "No subjects registered for this student.\n";
        system("pause");
        return;
    }

    cout << "\nSubjects registered for student " << id << ":\n";
    for (const auto& subj : subjects) {
        cout << "- " << subj << endl;
    }

    string selectedSubject;
    cin.ignore();
    cout << "\nEnter subject name to enter grades for: ";
    getline(cin, selectedSubject);

    auto subIt = find(subjects.begin(), subjects.end(), selectedSubject);
    if (subIt == subjects.end()) {
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
        if (total > 100) cout << "Total exceeds 100. Try again.\n";
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
