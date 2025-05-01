#include "Admin.h"
# include <map>
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include "Course.h"
#include <sstream>
#include "LoginSystem.h"


using namespace std;
Admin::Admin() {
}

//Anas
void Admin::displayMenu() {
    int choice;
    while (true) {
        system("cls");
        cout << "***********************************************************************\n\n";
        cout << "                      Welcome Yaaa Admin                            \n\n";
        cout << "*******************        MENU        *******************************\n\n";
        cout << "1. UploadCourse " << endl;
        cout << "2. Set Prerequistes" << endl;     
        cout << "3. Edit Student Data " << endl;
        cout << "4. Manage Student Grade " << endl;
        cout << "5. Delete user " << endl;
        cout << "6. EXIT" << endl;

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
            case 2:
                Set_Prerequistes();
                break;
            case 3:
                editStudentData();
                break;
            case 4:
                manageStudentGrades();
                break; 
            case 5:
                deleteUser();
                    break;
            case 6:
                cout << "Salaaaam Yaaa Admin.\n";
                LoginSystem l;
              l.displayMenu() ;
            default:
                cout << "Invalid choice, please try again.\n";
                continue;
            }
            break;
        }
    }
}
void Admin::deleteUser() {
    ifstream dbFile("database.csv");
    if (!dbFile.is_open()) {
        cout << "Error: Could not open database.csv.\n";
        system("pause");
        return;
    }

    map<string, string> userMap;
    vector<string> allLines; 
    string line;
    cout << "\nList of Users:\n";
    cout << "-----------------------------------\n";

    while (getline(dbFile, line)) {
        allLines.push_back(line);
        stringstream ss(line);
        string id, firstName, lastName, phone, username, password, email;
        getline(ss, id, ',');
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, phone, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, email, ',');

        userMap[id] = username;
        cout << "ID: " << id << " | Username: " << username << " | Name: " << firstName << " " << lastName << "\n";
    }
    dbFile.close();

    if (userMap.empty()) {
        cout << "No users found in the database.\n";
        system("pause");
        return;
    }

    cout << "-----------------------------------\n";
    cout << "Enter the ID of the user you want to delete: ";
    string targetID;
    cin >> targetID;

    if (userMap.find(targetID) == userMap.end()) {
        cout << "Invalid ID. No user found with the given ID.\n";
        system("pause");
        return;
    }

    {
        ofstream dbFileOut("database.csv", ios::trunc); 
        for (const auto& l : allLines) {
            if (l.find(targetID + ",") != 0) {
                dbFileOut << l << "\n";
            }
        }
        dbFileOut.close();
    }
    cout << "User removed from database.csv.\n";

    {
        ifstream regFile("registrations.csv");
        if (!regFile.is_open()) {
            cout << "Error: Could not open registrations.csv.\n";
            system("pause");
            return;
        }

        vector<string> regLines;
        while (getline(regFile, line)) {
            if (line.find(targetID + ",") != 0) {
                regLines.push_back(line);
            }
        }
        regFile.close();

        ofstream regFileOut("registrations.csv", ios::trunc);
        for (const auto& l : regLines) {
            regFileOut << l << "\n";
        }
        regFileOut.close();
    }
    cout << "User removed from registrations.csv.\n";

    {
        ifstream gradesFile("grades.csv");
        if (!gradesFile.is_open()) {
            cout << "Error: Could not open grades.csv.\n";
            system("pause");
            return;
        }

        vector<string> gradeLines;
        while (getline(gradesFile, line)) {
            if (line.find(targetID + ",") != 0) {
                gradeLines.push_back(line);
            }
        }
        gradesFile.close();

        ofstream gradesFileOut("grades.csv", ios::trunc);
        for (const auto& l : gradeLines) {
            gradesFileOut << l << "\n";
        }
        gradesFileOut.close();
    }
    cout << "User removed from grades.csv.\n";

    cout << "User deletion process completed.\n";
    system("pause");
}



//Abdallah
void Admin::uploadCourse(const string& filename) {
    string title, syllabus, instructor;
    string creditHours;

    cout << "Enter course title: ";
    getline(cin, title);
    cout << "Enter syllabus: ";
    getline(cin, syllabus);
    cout << "Enter credit hours: ";
    cin >> creditHours;
    getline(cin, creditHours);
    cout << "Enter instructor name: ";
    getline(cin, instructor);

    Course newCourse(title, syllabus, creditHours, instructor);
    newCourse.saveToFile(filename);
}
void Admin::editStudentData() {
    system("cls");
    cout << "=== Edit Student Data ===\n";

    map<string, vector<string>> students; // المفتاح هو اسم المستخدم، والقيمة هي بيانات الطالب
    vector<string> headers = { "ID", "First Name", "Last Name", "Phone", "Username", "Password", "Email" };

    ifstream infile("database.csv");
    string line;

    cout << "\nList of all students:\n";
    cout << "------------------------\n";

    while (getline(infile, line)) {
        stringstream ss(line);
        vector<string> studentData;
        string field;

        while (getline(ss, field, ',')) {
            studentData.push_back(field);
        }

        if (studentData.size() == headers.size()) {
            students[studentData[4]] = studentData; 
            cout << "- Username: " << studentData[4] << " | Name: " << studentData[1] << " " << studentData[2] << " | ID: " << studentData[0] << endl;
        }
    }
    infile.close();

    string targetUsername;
    cout << "\nEnter the username of the student you want to edit: ";
    cin >> targetUsername;

    auto it = students.find(targetUsername);
    if (it != students.end()) {
        vector<string>& studentData = it->second;

        cout << "\nStudent found!\n";
        for (size_t i = 0; i < headers.size(); ++i) {
            cout << headers[i] << ": " << studentData[i] << "\n";
        }

        string input;
        for (size_t i = 0; i < headers.size(); ++i) {
            cout << "\nChange " << headers[i] << "? (y/n): ";
            cin >> input;
            if (input == "y") {
                cout << "Enter new " << headers[i] << ": ";
                cin >> studentData[i];
            }
        }

        cout << "\nStudent data updated.\n";
        ofstream outfile("database.csv");
        for (const auto& pair : students) {
            const string& username = pair.first;
            const vector<string>& data = pair.second;

            for (size_t i = 0; i < data.size(); ++i) {
                outfile << data[i];

                if (i < data.size() - 1) outfile << ",";
            }
            outfile << "\n";
        }

        outfile.close();
    }
    else {
        cout << "\nUsername not found.\n";
    }

    system("pause");
}


//Ahmed
void Admin::Set_Prerequistes() {
    ifstream inFile("courses.csv");
    if (!inFile.is_open()) {
        cout << "Failed to open courses file.\n";
        return;
    }

    ofstream tempFile("temp.csv");
    if (!tempFile.is_open()) {
        cout << "Failed to create temp file.\n";
        return;
    }

    string line;
    getline(inFile, line); 
    tempFile << "Course_title,syllabus,creditHours,instructor,prerequisites\n";

    vector<string> updatedCourses;
    bool updatedAny = false;

    cout << "\n Current Courses List:\n";
    cout << "-----------------------------------------------------------\n";

    vector<string> allLines;
    vector<string> courseTitles;

    while (getline(inFile, line)) {
        allLines.push_back(line);

        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);

        string t = line.substr(0, pos1);
        string s = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string chStr = line.substr(pos2 + 1, pos3 - pos2 - 1);
        string i = line.substr(pos3 + 1, pos4 - pos3 - 1);
        string p = line.substr(pos4 + 1);

        courseTitles.push_back(t);
        cout << " Title: " << t << " | Credit Hours: " << chStr << " | Instructor: " << i << "\n";
    }

    cout << "-----------------------------------------------------------\n";
    cout << "\n";

    inFile.clear();
    inFile.seekg(0);
    getline(inFile, line); 

    size_t idx = 0;
    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);

        string t = line.substr(0, pos1);
        string s = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string chStr = line.substr(pos2 + 1, pos3 - pos2 - 1);
        string i = line.substr(pos3 + 1, pos4 - pos3 - 1);
        string p = line.substr(pos4 + 1);

        cout << "\nCourse [" << idx + 1 << "/" << courseTitles.size() << "] - " << t << "\n";
        cout << "Do you want to set/change prerequisites? (y = yes, n = no, x = cancel all): ";
        string choice;
        getline(cin, choice);

        if (choice == "x" || choice == "X") {
            cout << "\n Operation canceled by user.\n";
            inFile.close();
            tempFile.close();
            remove("temp.csv");
            return;
        }

        if (choice == "y" || choice == "Y") {
            cout << "Enter new prerequisites: ";
            getline(cin, p);
            updatedCourses.push_back(t);
            updatedAny = true;
        }

        tempFile << t << "," << s << "," << chStr << "," << i << "," << p << "\n";
        idx++;
    }

    inFile.close();
    tempFile.close();

    if (!updatedAny) {
        cout << "\nNo changes made. Operation ended.\n";
        remove("temp.csv");
        return;
    }

    cout << "\n You updated prerequisites for:\n";
    for (const string& course : updatedCourses) {
        cout << "Done " << course << "\n";
    }

    cout << "\n Confirm saving changes? (y/n): ";
    string confirm;
    getline(cin, confirm);

    if (confirm == "y" || confirm == "Y") {
        remove("courses.csv");
        rename("temp.csv", "courses.csv");
        cout << "\n Changes saved successfully!\n";
    }
    else {
        remove("temp.csv");
        cout << "\n Changes discarded.\n";
    }
}


//Anas-Nabil
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

    ifstream infile("registrations.csv");
    if (!infile) {
        cout << " Could not open registrations.csv\n";
        return;
    }

    string headerLine;
    getline(infile, headerLine);
    vector<string> headers;
    stringstream hs(headerLine);
    string col;
    while (getline(hs, col, ',')) headers.push_back(col);

    vector<string> ids;
    map<string, vector<string>> studentSubjects;
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, ',');
        ids.push_back(id);

        vector<string> subjects;
        string subject;
        while (getline(ss, subject, ',')) {
            if (!subject.empty()) subjects.push_back(subject);
        }

        studentSubjects[id] = subjects;
    }
    infile.close();

    cout << "\nList of Students (IDs):\n";
    for (const string& id : ids) cout << "- " << id << endl;

    string targetID;
    cout << "\nEnter student ID to enter grades for: ";
    cin >> targetID;

    if (studentSubjects.find(targetID) == studentSubjects.end()) {
        cout << "\n ID not found!\n";
        system("pause");
        return;
    }

    map<string, map<string, string>> existingGrades;
    vector<string> allGrades; 
    ifstream gradesIn("grades.csv");
    string gradeHeader;
    if (gradesIn) {
        getline(gradesIn, gradeHeader); 
        while (getline(gradesIn, line)) {
            allGrades.push_back(line);
            stringstream ss(line);
            string id, subject;
            getline(ss, id, ',');
            getline(ss, subject, ',');
            existingGrades[id][subject] = line;
        }
        gradesIn.close();
    }
    vector<string> subjects = studentSubjects[targetID];
    cout << "\n Subjects registered for student " << targetID << ":\n";
    for (const string& subj : subjects) cout << "- " << subj << endl;

    string selectedSubject;
    cin.ignore();
    cout << "\nEnter subject name to enter grades for: ";
    getline(cin, selectedSubject);

    bool valid = false;
    for (const string& subj : subjects) {
        if (subj == selectedSubject) {
            valid = true;
            break;
        }
    }

    if (!valid) {
        cout << "❌ Invalid subject for this student.\n";
        system("pause");
        return;
    }

    if (existingGrades[targetID].count(selectedSubject)) {
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
        cout << "\nEnter Quiz (0-5): ";
        while (!(cin >> quiz) || quiz < 0 || quiz > 5) { cin.clear(); cin.ignore(1000, '\n'); cout << "Try again: "; }

        cout << "Enter Assignment (0-10): ";
        while (!(cin >> assignment) || assignment < 0 || assignment > 10) { cin.clear(); cin.ignore(1000, '\n'); cout << "Try again: "; }

        cout << "Enter Midterm (0-15): ";
        while (!(cin >> midterm) || midterm < 0 || midterm > 15) { cin.clear(); cin.ignore(1000, '\n'); cout << "Try again: "; }

        cout << "Enter Practical (0-20): ";
        while (!(cin >> practical) || practical < 0 || practical > 20) { cin.clear(); cin.ignore(1000, '\n'); cout << "Try again: "; }

        cout << "Enter Final (0-50): ";
        while (!(cin >> finalExam) || finalExam < 0 || finalExam > 50) { cin.clear(); cin.ignore(1000, '\n'); cout << "Try again: "; }

        total = quiz + assignment + midterm + practical + finalExam;
        if (total > 100) cout << " Total exceeds 100. Try again.\n";
    } while (total > 100);

    float gpa = calculateGPA(total);
    stringstream newline;
    newline << targetID << "," << selectedSubject << ","
        << quiz << "," << assignment << "," << midterm << ","
        << practical << "," << finalExam << "," << total << "," << gpa;

    bool updated = false;
    for (string& existingLine : allGrades) {
        if (existingLine.find(targetID + "," + selectedSubject) == 0) {
            existingLine = newline.str();
            updated = true;
            break;
        }
    }
    if (!updated) {
        allGrades.push_back(newline.str());
    }
    ofstream out("grades.csv");
    out << "ID,Subject,Quiz,Assignment,Midterm,Practical,Final,Total,GPA\n";
    for (const string& l : allGrades) out << l << "\n";
    out.close();

    cout << "\n Grades saved for " << selectedSubject << " (Student: " << targetID << ")\n";
    system("pause");
}

