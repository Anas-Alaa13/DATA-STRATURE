#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Course.h"
using namespace std;

class Student {
private:
    int studentID;
    string username;

public:
    Student();

    //Kenzy
    void setUsername(const string& user);
    int getStudentID() const;
    unordered_map<int, vector<string>> readRegistrationsFile(const string& filename);
    bool alreadyRegistered(const string& courseName);
    bool prerequisitesMet(const string& prereq);
    void registercourse();
    Course findcourse(const string& searchName);
	void setStudentID(int id) { studentID = id; }
    bool isCourseValid(const string& courseName);


    //Mohamed
    Student(const std::string& uname) : username(uname) {}
    std::string getUsername() const { return username; }
    void viewGrades();
    void filterGrades();
    void exportGradesToCSV();



    //Anas
    void displayMenu();
    void viewRegisteredCourses();


    //Farah
    void generateReport(const string& id);

};

#endif