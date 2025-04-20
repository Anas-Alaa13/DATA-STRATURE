#include "Course.h"
#include <fstream>
#include <iostream>
using namespace std;


Course::Course(string t, string s, int ch, string i) {
    title = t;
    syllabus = s;
    creditHours = ch;
    instructor = i;
}
void Course::saveToFile(const string& filename) {
    bool isEmpty = false;
    ifstream checkFile(filename);
    isEmpty = checkFile.peek() == ifstream::traits_type::eof();
    checkFile.close();

    ofstream file(filename, ios::app);
    if (file.is_open()) {
        if (isEmpty) {
            file << "Course_title,syllabus,creditHours,instructor\n";
        }
        file << title << "," << syllabus << "," << creditHours << "," << instructor << "\n";
        file.close();
        cout << "Course saved successfully!\n";
    }
    else {
        cout << "Failed to open file.\n";
    }
}

void Course::printCourse() {
    cout << courseTitle << "(" << semester << " ,Grade: " << grade << " ,Credit Hours: " << creditHours << ")" << endl;
}
