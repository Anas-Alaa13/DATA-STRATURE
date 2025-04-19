#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Structure to store a single grade entry
struct Grade {
    string courseName; // Name of the course
    string semester;   // Semester of the course
    double score;      // Score achieved
};

// Hash table to store grades for each student, keyed by StudentID
unordered_map<string, vector<Grade>> studentGrades;

// Initialize dummy data for testing
void initializeDummyData() {
    studentGrades["S123"] = {
        {"Data Structures", "Fall 2024", 85.5},
        {"Operations Research", "Fall 2024", 90.0},
        {"Linear Algebra", "Fall 2024", 88.0}
    };
    studentGrades["S456"] = {
        {"Computer Architecture", "Spring 2024", 78.0},
        {"AI", "Spring 2024", 92.5}
    };
    studentGrades["S789"] = {
        {"Data Structures", "Fall 2023", 80.0}
    };
}

// Display grades for a given StudentID in a formatted table
void viewGrades(const string& studentID) {
    if (studentGrades.find(studentID) == studentGrades.end()) {
        cout << "No grades found for student ID: " << studentID << endl;
        return;
    }
    cout << "Grades for Student ID: " << studentID << endl;
    cout << left << setw(25) << "Course" 
         << setw(15) << "Semester" 
         << setw(10) << "Score" << endl;
    cout << "--------------------------------------------" << endl;
    for (const auto& grade : studentGrades[studentID]) {
        cout << left << setw(25) << grade.courseName 
             << setw(15) << grade.semester 
             << setw(10) << grade.score << endl;
    }
    cout << "--------------------------------------------" << endl;
}

int main() {
    initializeDummyData(); // Load dummy data
    string studentID;
    while (true) {
        cout << "Enter Student ID (or 'exit' to quit): ";
        cin >> studentID;
        if (studentID == "exit") break;
        viewGrades(studentID); // Display grades for entered ID
    }
    return 0;
}