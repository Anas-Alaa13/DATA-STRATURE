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

    Course();
    Course(string t, string s, string ch, string i, string p = "");
    void saveToFile(const string& filename);
};

#endif
