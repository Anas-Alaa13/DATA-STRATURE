#pragma once
#include <string>
#include <vector>
#include<map>
using namespace std;

class Student  {
private:
    std::string username;


public:
    Student();
    string name;
    int id;
    void displayMenu();
    bool Prerequisites();
    bool findcourse();
    void setUsername(const std::string& user);
    void registercourse();
    void viewRegisteredCourses();
    float calcGPA();
    void printReport();



};
