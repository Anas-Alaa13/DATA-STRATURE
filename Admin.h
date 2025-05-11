#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "DataManager.h"
#include "Structures.h"

class Admin {
private:
    DataManager& dm;

public:
    Admin(DataManager& dm);


    //Anas
    void displayMenu();
    void deleteUser();
    void editStudentData();




    //Framawy-Ahmed
    void ShowCourses();
    bool isValidPrerequisites(const std::string& prereqList);
    void UpdatePrerequisites();
    void EnsureCoursesFileExists(const std::string& FileName);
    void UploadCourse();
    void SetPrerequisites();



    //Nabil
    void manageStudentGrades();
    float calculateGPA(int total);
};

#endif