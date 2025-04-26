#include "Course.h"
#include"Student.h"
#include <fstream>
#include <iostream>
using namespace std;

#include "Course.h"

Course::Course()
    : title(""), syllabus(""), creditHours(0), instructor(""), prerequisites(""), semester(""), grade(0.0) {
}


Course::Course(string t, string s, string ch, string i, string p, float g, string sem) {
    title = t;
    syllabus = s;
    creditHours = ch;
    instructor = i;
    prerequisites = p;
    semester = sem;
	grade = g;
}
void Course::printCourse() {
	cout << name << "(" << semster << " ,Grade:" << grade << " ,Credit Hours:" << credithours <<")" <<endl;
    
}

void Course::saveToFile(const string& filename) {
    bool isEmpty = false;
    ifstream checkFile(filename);
    isEmpty = checkFile.peek() == ifstream::traits_type::eof();
    checkFile.close();

    ofstream file(filename, ios::app);
    if (file.is_open()) {
   
        file << title << "," << syllabus << "," << creditHours << "," << instructor << "," << prerequisites << "\n";
        file.close();
        cout << "Course saved successfully!\n";
    }
    else {
        cout << "Failed to open file.\n";
    }
}


