//Helper To File

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>
using namespace std;
struct User {
    int ID;
     string FirstName;
     string LastName;
     string PhoneNumber;
     string Username;
     string Password;
     string Email;
};

struct Course {
     string title;
     string syllabus;
     string creditHours;
     string instructor;
     string prerequisites;
};

struct Grade {
    int ID;
     string Subject;
    int Quiz;
    int Assignment;
    int Midterm;
    int Practical;
    int Final;
    int Total;
    double GPA;
};

#endif