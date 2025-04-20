#ifndef COURSE_H
#define COURSE_H


#include <string>
using namespace std;

class Course {
public:
    string title;
    string syllabus;
    int creditHours;
    string instructor;

    Course();
    Course(string t, string s, int ch, string i);
    void saveToFile(const string& filename);
};

#endif
