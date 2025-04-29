#pragma once
#include <string>
#include<iostream>
using namespace std;

class Admin {
public:
    Admin();
    //Anas
    void displayMenu();
    void deleteUser();

    //Abdallah
    void uploadCourse(const string& filename);
    void editStudentData();

    //Ahmed
	void Set_Prerequistes();


	//Anas-Nabil
    void manageStudentGrades();
	float calculateGPA(int total);
};
