#include "Student.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <map>
#include <stack>
#include <queue>

using namespace std;

Student::Student(DataManager& dm) : dm(dm), studentID(0) {}

void Student::setUsername(const string& user) {
    username = user;
}

void Student::setStudentID(int id) {
    studentID = id;
}

int Student::getStudentID() const {
    return studentID;
}

string Student::getUsername() const {
    return username;
}

//Anas
void Student::displayMenu() {
    int choice;
    while (true) {
        system("cls");
        cout << "*\n\n";
        cout << "                      Welcome Yaaa Taleb                            \n\n";
        cout << "*******************        MENU        *******************************\n\n";
        cout << "1. Register for a course\n";
        cout << "2. Find a course\n";
        cout << "3. View Grades\n";
        cout << "4. View Registration course\n";
        cout << "5. The report\n";
        cout << "6. Filter Grades\n";
        cout << "7. Exit\n";

        cout << "\nEnter your choice: ";
        string inputStr;
        while (true) {
            getline(cin, inputStr);
            bool isNumber = true;
            for (char ch : inputStr) {
                if (!isdigit(ch)) {
                    isNumber = false;
                    break;
                }
            }
            if (isNumber && !inputStr.empty()) {
                choice = stoi(inputStr);
                break;
            }
            else {
                cout << "\nInvalid input. Please enter a valid number.\n";
            }
        }

        switch (choice) {
        case 1:
            registercourse();
            break;
        case 2: {
            string searchName;
            cout << "Enter the course name to find: ";
            getline(cin, searchName);
            Course course = findcourse(searchName);
            if (course.title.empty()) {
                cout << "Course not found.\n";
            }
            else {
                cout << "\n--- Course Details ---\n";
                cout << "Title: " << course.title << endl;
                cout << "Syllabus: " << course.syllabus << endl;
                cout << "Credit Hours: " << course.creditHours << endl;
                cout << "Instructor: " << course.instructor << endl;
                cout << "Prerequisites: " << (course.prerequisites.empty() ? "No Prerequisites" : course.prerequisites) << endl;
            }
            system("pause");
            break;
        }
        case 3:
            viewGrades();
            break;
        case 4:
            viewRegisteredCourses();
            break;
        case 5:
            generateReport(to_string(studentID));
            break;
        case 6:
            filterGrades();
            break;
        case 7:
            cout << "Slaaaam YA Taleb.\n";
			system("pause");
            return;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    }
}
void Student::viewRegisteredCourses() {
    system("cls");
    cout << "******** Your Registered Courses ********\n";

    auto it = dm.registrations.find(studentID);
    stack<string> registeredCourses;
    bool found = false;

    if (it != dm.registrations.end()) {
        found = true;
        for (const auto& course : it->second) {
            if (!course.empty()) {
                registeredCourses.push(course);
            }
        }
    }

    if (found && !registeredCourses.empty()) {
        cout << "Courses : \n";
        while (!registeredCourses.empty()) {
            cout << "- " << registeredCourses.top() << "\n";
            registeredCourses.pop();
        }
    }
    else {
        cout << "No registration data found for user with ID: " << studentID << "\n";
    }

    system("pause");
}


//Kinzy
bool Student::alreadyRegistered(const string& courseName) {
    auto it = dm.registrations.find(studentID);
    if (it != dm.registrations.end()) {
        for (const auto& course : it->second) {
            if (course == courseName) {
                return true;
            }
        }
    }
    return false;
}
bool Student::prerequisitesMet(const string& prereq) {
    if (prereq.empty()) return true;

    auto it = dm.registrations.find(studentID);
    if (it != dm.registrations.end()) {
        stringstream ss(prereq);
        string singlePrereq;
        while (getline(ss, singlePrereq, ',')) {
            singlePrereq.erase(remove_if(singlePrereq.begin(), singlePrereq.end(), ::isspace), singlePrereq.end());
            bool met = false;
            for (const auto& course : it->second) {
                if (course == singlePrereq) {
                    met = true;
                    break;
                }
            }
            if (!met) return false;
        }
        return true;
    }
    return false;
}
bool Student::isCourseValid(const string& courseName) {
    string inputLower = courseName;
    transform(inputLower.begin(), inputLower.end(), inputLower.begin(), ::tolower);
    for (const auto& course : dm.courses) {
        string titleLower = course.title;
        transform(titleLower.begin(), titleLower.end(), titleLower.begin(), ::tolower);
        if (inputLower == titleLower) {
            return true;
        }
    }
    return false;
}///////////
Course Student::findcourse(const string& searchName) {
    string searchLower = searchName;
    transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
    for (const auto& course : dm.courses) {
        string titleLower = course.title;
        transform(titleLower.begin(), titleLower.end(), titleLower.begin(), ::tolower);
        if (searchLower == titleLower) {
            return course;
        }
    }
    return Course();
}///////
void Student::registercourse() {
    string courseName;
    cout << "Enter course name to register: ";
    getline(cin, courseName);

    if (!isCourseValid(courseName)) {
        cout << "Course not found or name is incorrect.\n";
        system("pause");
        return;
    }

    Course course = findcourse(courseName);
    if (course.title.empty()) {
        cout << "Course not found.\n";
        system("pause");
        return;
    }

    if (alreadyRegistered(courseName)) {
        cout << "You are already registered in this course.\n";
        system("pause");
        return;
    }

    if (!prerequisitesMet(course.prerequisites)) {
        cout << "Prerequisites not met for this course.\n";
        system("pause");
        return;
    }

    dm.registrations[studentID].push_back(courseName);
    cout << "Registered successfully.\n";
    system("pause");
}


//mohamed
void Student::viewGrades() {
    cout << "\nGrades for Student ID: " << studentID << "\n";
    cout << "--------------------------------------------------\n";
    cout << "Subject\tQuiz\tAssign\tMidterm\tPractical\tFinal\tTotal\tGPA\n";
    cout << "--------------------------------------------------\n";

    bool found = false;
    for (const auto& grade : dm.grades) {
        if (grade.ID == studentID) {
            found = true;
            cout << grade.Subject << "\t" << grade.Quiz << "\t" << grade.Assignment << "\t" << grade.Midterm
                << "\t" << grade.Practical << "\t" << grade.Final << "\t" << grade.Total << "\t" << grade.GPA << "\n";
        }
    }

    if (!found) {
        cout << "No grades found for this student!\n";
    }
    cout << "--------------------------------------------------\n";
    system("pause");
}
void Student::filterGrades() {
    double minGPA;
    cout << "\nEnter minimum GPA to filter grades: ";
    cin >> minGPA;
    cout << "Filtering grades for Student ID: " << studentID << " (GPA >= " << minGPA << ")\n";

    queue<Grade> filteredGrades;
    for (const auto& grade : dm.grades) {
        if (grade.ID == studentID && grade.GPA >= minGPA) {
            filteredGrades.push(grade);
        }
    }

    if (!filteredGrades.empty()) {
        cout << "\nFiltered Grades for Student ID: " << studentID << " (GPA >= " << minGPA << ")\n";
        cout << "--------------------------------------------------\n";
        cout << "Subject\tQuiz\tAssign\tMidterm\t的好Practical\tFinal\tTotal\tGPA\n";
        cout << "--------------------------------------------------\n";

        while (!filteredGrades.empty()) {
            const Grade& grade = filteredGrades.front();
            cout << grade.Subject << "\t" << grade.Quiz << "\t" << grade.Assignment << "\t"
                << grade.Midterm << "\t" << grade.Practical << "\t" << grade.Final << "\t"
                << grade.Total << "\t" << grade.GPA << "\n";
            filteredGrades.pop();
        }
    }
    else {
        cout << "No grades found with GPA >= " << minGPA << "!\n";
    }
    cout << "--------------------------------------------------\n";
    system("pause");
}




//Frah
void Student::generateReport(const string& id) {
    system("cls");
    cout << "******** Student Grade Report ********\n";

    cout << "Name: " << username << endl;
    cout << "ID: " << id << endl;

    string reportFilename = "Student_Report_" + id + ".txt";
    ofstream reportFile(reportFilename);
    if (!reportFile.is_open()) {
        cout << "Error: Could not create report file.\n";
        system("pause");
        return;
    }

    reportFile << "******** Student Grade Report ********\n";
    reportFile << "Name: " << username << "\n";
    reportFile << "ID: " << id << "\n";

    auto regIt = dm.registrations.find(stoi(id));
    vector<string> registeredCourses;
    if (regIt != dm.registrations.end()) {
        registeredCourses = regIt->second;
    }

    if (registeredCourses.empty()) {
        cout << "No registration data found for user with ID: " << id << "\n";
        reportFile << "No registration data found for user with ID: " << id << "\n";
        reportFile.close();
        system("pause");
        return;
    }

    map<string, Grade> courseGrades;
    for (const auto& grade : dm.grades) {
        if (grade.ID == stoi(id)) {
            courseGrades[grade.Subject] = grade;
        }
    }

    unordered_map<string, int> courseCreditHours;
    for (const auto& course : dm.courses) {
        try {
            courseCreditHours[course.title] = course.creditHours.empty() ? 0 : stoi(course.creditHours);
        }
        catch (const exception& e) {
            cout << "Warning: Invalid credit hours for course: " << course.title << "\n";
            courseCreditHours[course.title] = 0;
        }
    }

    vector<vector<string>> semesters;
    vector<string> currentSemester;
    int currentSemesterHours = 0;

    for (const string& course : registeredCourses) {
        if (courseCreditHours.find(course) != courseCreditHours.end()) {
            int courseHours = courseCreditHours[course];
            if (currentSemesterHours + courseHours > 15) {
                semesters.push_back(currentSemester);
                currentSemester.clear();
                currentSemesterHours = 0;
            }
            currentSemester.push_back(course);
            currentSemesterHours += courseHours;
        }
    }

    if (!currentSemester.empty()) {
        semesters.push_back(currentSemester);
    }

    cout << "\n******** Registered Courses by Semester ********\n";
    reportFile << "\n******** Registered Courses by Semester ********\n";
    double totalGPA = 0;
    int courseCount = 0;

    for (size_t i = 0; i < semesters.size(); ++i) {
        cout << "Semester " << (i + 1) << ":\n";
        reportFile << "Semester " << (i + 1) << ":\n";
        for (const string& course : semesters[i]) {
            cout << "- " << course << " (" << courseCreditHours[course] << " credit hours)";
            reportFile << "- " << course << " (" << courseCreditHours[course] << " credit hours)";
            if (courseGrades.find(course) != courseGrades.end()) {
                const Grade& grade = courseGrades[course];
                cout << " | Quiz: " << grade.Quiz
                    << " | Assignment: " << grade.Assignment
                    << " | Midterm: " << grade.Midterm
                    << " | Practical: " << grade.Practical
                    << " | Final: " << grade.Final
                    << " | Total: " << grade.Total
                    << " | GPA: " << grade.GPA;
                reportFile << " | Quiz: " << grade.Quiz
                    << " | Assignment: " << grade.Assignment
                    << " | Midterm: " << grade.Midterm
                    << " | Practical: " << grade.Practical
                    << " | Final: " << grade.Final
                    << " | Total: " << grade.Total
                    << " | GPA: " << grade.GPA;
                totalGPA += grade.GPA;
                courseCount++;
            }
            else {
                cout << " | Grade: N/A";
                reportFile << " | Grade: N/A";
            }
            cout << "\n";
            reportFile << "\n";
        }
        cout << "-------------------------------\n";
        reportFile << "-------------------------------\n";
    }

    if (courseCount > 0) {
        double overallGPA = totalGPA / courseCount;
        cout << "\nOverall GPA: " << overallGPA << endl;
        reportFile << "\nOverall GPA: " << overallGPA << "\n";
    }
    else {
        cout << "\nNo grades found for your registered courses.\n";
        reportFile << "\nNo grades found for your registered courses.\n";
    }

    cout << "*********************************************\n";
    reportFile << "*********************************************\n";

    reportFile.close();
    cout << "Report saved to " << reportFilename << endl;
    system("pause");
}