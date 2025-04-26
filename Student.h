#pragma once
#include <string>
#include <vector>
#include<map>
#include "Course.h"
using namespace std;

class Student  {
private:
    std::string username;


public:
    Student();
    string name;
    int id;
    student(string name, int id);
    vector<Course> courses;
    void displayMenu();
    bool Prerequisites();
    bool findcourse();
    void setUsername(const std::string& user);
    void registercourse();
    void viewRegisteredCourses();
    float calcGPA();
    void printReport();
    void addCourse(Course c);



};
