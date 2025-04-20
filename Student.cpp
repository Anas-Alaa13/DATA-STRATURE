#include "Student.h"
#include <iostream>
#include<sstream>
#include<fstream>
#include<algorithm>
using namespace std;
Student::Student() {}

Student::Student(int id, string username, string password, vector<string> enrolledCourses,map<string ,double> grades) {
    this->id = id;
    this->UserName = username;
    this->Password = password;
    this->enrolledCourses = enrolledCourses;
    this->grades = grades;
}

bool Student::alreadyregistered(string courseCode) {
    return find(enrolledCourses.begin(), enrolledCourses.end(), courseCode)
        != enrolledCourses.end(); /*  لو لا يساوي هو كده لقاه رترن ترو
    لقاه يبقى متسجلوش تاني*/
}


void Student::registercourse(string coursecode) {

    if (!alreadyregistered(coursecode) && check(coursecode)) {

        enrolledCourses.push_back(coursecode);

         
        ofstream file("database.csv", ios::app);
        if (file.is_open()) {
            file << UserName << "," << coursecode << "\n";
            file.close();
            cout << "Course registered successfully." << endl;
        }
    }
    else {
        cout << "either course is registed before or prerequists arenot met ." << endl;
    }
}
  
Course Student::findcourse(string search) {
    ifstream file("course.csv");
    string line;
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        string courseCodeFromFile, courseTitle, creditHoursStr, syllabus, prereqStr;

        getline(ss, courseCodeFromFile, ',');
        getline(ss, courseTitle, ',');
        getline(ss, creditHoursStr, ',');
        getline(ss, syllabus, ',');
        getline(ss, prereqStr);

        int creditHours = stoi(creditHoursStr);
        Course course(courseTitle, courseCodeFromFile, syllabus, creditHours);

        stringstream preSS(prereqStr);
        string pre;
        while (getline(preSS, pre, '|')) {
            course.addPrerequisite(pre);
        }

       
        if (search == courseCodeFromFile || search == courseTitle) {
            file.close();
            return course;
        }
    }

    file.close();
    return Course();
}
