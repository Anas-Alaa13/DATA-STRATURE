#pragma once
#include <string>
#include <vector>
#include<map>
#include "User.h"
using namespace std;

class Student:public User {
private:
    int id;
    string UserName;
    string Password;
    vector<string> enrolledCourses;
    map<string, double>grades;

public:
    Student();
    Student(int id, string password, vector<string>enrolledCourses, map<string, double>grades);
    
   

  

};
