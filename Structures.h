//Helper To File

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>

struct User {
    int ID;
    std::string FirstName;
    std::string LastName;
    std::string PhoneNumber;
    std::string Username;
    std::string Password;
    std::string Email;
};

struct Course {
    std::string title;
    std::string syllabus;
    std::string creditHours;
    std::string instructor;
    std::string prerequisites;
};

struct Grade {
    int ID;
    std::string Subject;
    int Quiz;
    int Assignment;
    int Midterm;
    int Practical;
    int Final;
    int Total;
    double GPA;
};

#endif