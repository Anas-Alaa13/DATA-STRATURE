#include <iostream>
#include <fstream>
#include <string>
#include<vector>
using namespace std;

void Admin::UploadCourse() {


    string title, code, syllabus, instructorName;
    int creditHours;
    string choice;
    vector<Course>courses;
    ofstream file("Test.csv", ios::app);
    file << "Title,Code,Syllabus,creditHourses,Instructor\n";
    file.close();
    do {


        cout << "enter title of course\n";
        cin >> title;
        cout << "enter code of course\n";
        cin >> code;
        cout << "enter syllabus of course\n";
        cin >> syllabus;
        cout << "enter instructorName\n";
        cin >> instructorName;
        cout << "enter creditHours\n";
        cin >> creditHours;

        Course course(title,code,syllabus, creditHours,instructorName);

        courses.push_back(course);
        ofstream file("Test.csv", ios::app);

        file << title << "," << code << "," << syllabus << "," << instructorName << "," << creditHours;
        file.close();


        cout << "Do you want to add another course? (y/n): ";
        cin >> choice;

    } while (choice == "yes" || choice == "y");
