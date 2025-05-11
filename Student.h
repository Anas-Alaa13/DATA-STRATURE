#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include "DataManager.h"
#include "Structures.h"

class Student {
private:
    int studentID;
    std::string username;
    DataManager& dm;

public:
    Student(DataManager& dm);

    //Kenzy
    void setUsername(const std::string& user);
    void setStudentID(int id);
    int getStudentID() const;
    bool alreadyRegistered(const std::string& courseName);
    bool prerequisitesMet(const std::string& prereq);
    void registercourse();
    Course findcourse(const std::string& searchName);
    bool isCourseValid(const std::string& courseName);


	//Mohamed
    std::string getUsername() const;
    void viewGrades();
    void filterGrades();


	//Anas
    void displayMenu();
    void viewRegisteredCourses();




   //Frah
    void generateReport(const std::string& id);
};

#endif