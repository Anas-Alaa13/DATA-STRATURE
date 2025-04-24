#pragma once
#include <string>
#include<iostream>
using namespace std;

class Admin {
public:
    Admin();
    void displayMenu();
    void uploadCourse(const string& filename);
	void Set_Prerequistes();
	void Manage_Student_Grade(); 
    void editStudentData();
    void manageStudentGrades();
	float calculateGPA(int total);
};
