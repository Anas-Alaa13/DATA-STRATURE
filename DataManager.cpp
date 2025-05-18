#include "DataManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
DataManager::DataManager() {
    readUsers("database.csv");
    readCourses("courses.csv");
    readRegistrations("registrations.csv");
    readGrades("grades.csv");
}

void DataManager::readUsers(const  string& filename) {
     ifstream file(filename);
    if (!file.is_open()) {
         cerr << "Error opening " << filename <<  endl;
        return;
    }
     string line;
     getline(file, line); 
    while ( getline(file, line)) {
         stringstream ss(line);
        User user;
         string temp;
         getline(ss, temp, ','); user.ID =  stoi(temp);
         getline(ss, user.FirstName, ',');
         getline(ss, user.LastName, ',');
         getline(ss, user.PhoneNumber, ',');
         getline(ss, user.Username, ',');
         getline(ss, user.Password, ',');
         getline(ss, user.Email, ',');
        users.push_back(user);
    }
    file.close();
}

void DataManager::readCourses(const  string& filename) {
     ifstream file(filename);
    if (!file.is_open()) {
         cerr << "Error opening " << filename <<  endl;
        return;
    }
     string line;
     getline(file, line); 
    while ( getline(file, line)) {
         stringstream ss(line);
        Course course;
         getline(ss, course.title, ',');
         getline(ss, course.syllabus, ',');
         getline(ss, course.creditHours, ',');
         getline(ss, course.instructor, ',');
         getline(ss, course.prerequisites, ',');
        courses.push_back(course);
        courseTitles.insert(course.title); 

    }
    file.close();
}

void DataManager::readRegistrations(const  string& filename) {
     ifstream file(filename);
    if (!file.is_open()) {
         cerr << "Error opening " << filename <<  endl;
        return;
    }
     string line;
     getline(file, line); // Skip header
    while ( getline(file, line)) {
         stringstream ss(line);
         string userIDStr;
         getline(ss, userIDStr, ',');
        int userID =  stoi(userIDStr);
         vector< string> subjects;
         string subject;
        while ( getline(ss, subject, ',')) {
            if (!subject.empty()) subjects.push_back(subject);
        }
        registrations[userID] = subjects;
    }
    file.close();
}

void DataManager::readGrades(const  string& filename) {
     ifstream file(filename);
    if (!file.is_open()) {
         cerr << "Error opening " << filename <<  endl;
        return;
    }
     string line;
     getline(file, line); // Skip header
    while ( getline(file, line)) {
         stringstream ss(line);
        Grade grade;
         string temp;
         getline(ss, temp, ','); grade.ID =  stoi(temp);
         getline(ss, grade.Subject, ',');
         getline(ss, temp, ','); grade.Quiz =  stoi(temp);
         getline(ss, temp, ','); grade.Assignment =  stoi(temp);
         getline(ss, temp, ','); grade.Midterm =  stoi(temp);
         getline(ss, temp, ','); grade.Practical =  stoi(temp);
         getline(ss, temp, ','); grade.Final =  stoi(temp);
         getline(ss, temp, ','); grade.Total =  stoi(temp);
         getline(ss, temp, ','); grade.GPA =  stod(temp);
        grades.push_back(grade);
    }
    file.close();
}

void DataManager::writeUsers(const  string& filename) {
     ofstream file(filename);
    if (!file.is_open()) {
         cerr << "Error writing to " << filename <<  endl;
        return;
    }
    file << "ID,FirstName,LastName,PhoneNumber,Username,Password,Email\n";
    for (const auto& user : users) {
        file << user.ID << ',' << user.FirstName << ',' << user.LastName << ','
            << user.PhoneNumber << ',' << user.Username << ',' << user.Password
            << ',' << user.Email << '\n';
    }
    file.close();
}

void DataManager::writeCourses(const  string& filename) {
     ofstream file(filename);
    if (!file.is_open()) {
         cerr << "Error writing to " << filename <<  endl;
        return;
    }
    file << "Course_Title,Syllabus,Credit_Hours,Instructor,Prerequisites\n";
    for (const auto& course : courses) {
        file << course.title << ',' << course.syllabus << ',' << course.creditHours << ','
            << course.instructor << ',' << course.prerequisites << '\n';
    }
    file.close();
}

void DataManager::writeRegistrations(const  string& filename) {
     ofstream file(filename);
    if (!file.is_open()) {
         cerr << "Error writing to " << filename <<  endl;
        return;
    }
    int maxCourses = 0;
    for (const auto& entry : registrations) {
        if (entry.second.size() > maxCourses) maxCourses = entry.second.size();
    }
    file << "UserID";
    for (int i = 1; i <= maxCourses; i++) file << ",Subject" << i;
    file << '\n';
    for (const auto& entry : registrations) {
        file << entry.first;
        for (const auto& subject : entry.second) {
            file << ',' << subject;
        }
        file << '\n';
    }
    file.close();
}

void DataManager::writeGrades(const  string& filename) {
     ofstream file(filename);
    if (!file.is_open()) {
         cerr << "Error writing to " << filename <<  endl;
        return;
    }
    file << "ID,Subject,Quiz,Assignment,Midterm,Practical,Final,Total,GPA\n";
    for (const auto& grade : grades) {
        file << grade.ID << ',' << grade.Subject << ',' << grade.Quiz << ','
            << grade.Assignment << ',' << grade.Midterm << ',' << grade.Practical << ','
            << grade.Final << ',' << grade.Total << ',' << grade.GPA << '\n';
    }
    file.close();
}

void DataManager::saveAllData() {
    writeUsers("database.csv");
    writeCourses("courses.csv");
    writeRegistrations("registrations.csv");
    writeGrades("grades.csv");
}