#pragma once
#include <string>
#include<iostream>
using namespace std;

class Admin {
public:
    Admin();
    void displayMenu();
    void uploadCourse(const string& filename);
};
