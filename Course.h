#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

class Course {
public:
    string title;
    string syllabus;
    string creditHours;
    string instructor;
    string prerequisites;
    float grade;
    string semster;

    Course();
    Course(string t, string s, string ch, string i, float g, string sem, string p = "");
    void printCourse();
    void saveToFile(const string& filename);
};

#endif
