#include "Student.h"
#include "Course.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <map>

using namespace std;

Student::Student() {}
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
            for (int i = 0; i < inputStr.size(); i++) {
                if (!isdigit(inputStr[i])) {
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

                if (course.prerequisites.empty()) {
                    cout << "No Prerequisites" << endl;
                }
                else {
                    cout << "Prerequisites: " << course.prerequisites << endl;
                }
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
            cout << "Goodbye.\n";
            return;

        default:
            cout << "Invalid choice, please try again.\n";
        }
    }
}
void Student::viewRegisteredCourses() {
    system("cls");

    cout << "******** Your Registered Courses ********\n";

    ifstream regFile("registrations.csv");
    if (!regFile.is_open()) {
        cout << "Error: Could not open registrations.csv\n";
        return;
    }

    string line;
    getline(regFile, line); // Skip the header line

    bool found = false;

    while (getline(regFile, line)) {
        stringstream ss(line);
        string userID;
        getline(ss, userID, ',');

        if (userID == to_string(studentID)) {
            
            found = true;
            string course;
            int count = 0;
            while (getline(ss, course, ',')) {
                cout << "- " << course << "\n";
                count++;
            }
            if (count == 0) {
                cout << "You are not registered in any courses.\n";
            }
            break;
        }
    }

    if (!found) {
        cout << "No registration data found for user with ID: " << studentID << "\n";
    }

    regFile.close();
    system("pause");
}





//Kenzy
void Student::setUsername(const string& user) {
    username = user;
}
int Student::getStudentID() const {
    return this->studentID;
}
unordered_map<int, vector<string>> Student::readRegistrationsFile(const string& filename) {
    unordered_map<int, vector<string>> registrations;
    ifstream regFile(filename);
    string line;
    getline(regFile, line);

    while (getline(regFile, line)) {
        stringstream ss(line);
        string idStr;
        getline(ss, idStr, ',');
        int studentID = stoi(idStr);

        string course;
        while (getline(ss, course, ',')) {
            registrations[studentID].push_back(course);
        }
    }

    return registrations;
}
bool Student::alreadyRegistered(const string& courseName) {
    unordered_map<int, vector<string>> registrations = readRegistrationsFile("registrations.csv");
    int studentID = getStudentID();
    vector<string> studentCourses = registrations[studentID];

    for (int i = 0; i < studentCourses.size(); i++) {
        if (studentCourses[i] == courseName) {
            return true;
        }
    }

    return false;
}
bool Student::prerequisitesMet(const string& prereq) {
    if (prereq.empty()) return true;

    unordered_map<int, vector<string>> registrations = readRegistrationsFile("registrations.csv");
    int studentID = getStudentID();
    vector<string> studentCourses = registrations[studentID];

    for (int i = 0; i < studentCourses.size(); i++) {
        if (studentCourses[i] == prereq) {
            return true;
        }
    }

    return false;
}
bool Student::isCourseValid(const string& courseName) {
    ifstream file("courses.csv");
    if (!file.is_open()) {
        cerr << "Error opening courses.csv\n";
        return false;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string title;
        getline(ss, title, ',');

        // تحويل الاسم إلى حروف صغيرة للمقارنة
        string inputLower = courseName;
        string titleLower = title;
        transform(inputLower.begin(), inputLower.end(), inputLower.begin(), ::tolower);
        transform(titleLower.begin(), titleLower.end(), titleLower.begin(), ::tolower);

        if (inputLower == titleLower) {
            return true; // الكورس موجود والاسم صحيح
        }
    }

    return false; // الكورس غير موجود
}
Course Student::findcourse(const string& searchName) {
    ifstream file("courses.csv");
    if (!file.is_open()) {
        cerr << "Error opening courses.csv\n";
        return Course();
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string title, syllabus, creditHoursStr, instructor, prereq;

        getline(ss, title, ',');
        getline(ss, syllabus, ',');
        getline(ss, creditHoursStr, ',');
        getline(ss, instructor, ',');
        getline(ss, prereq);

        string searchLower = searchName;
        string titleLower = title;
        transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
        transform(titleLower.begin(), titleLower.end(), titleLower.begin(), ::tolower);

        if (searchLower == titleLower) {
            Course course(title, syllabus, creditHoursStr, instructor);
            course.prerequisites = prereq;
            return course;
        }
    }

    return Course();
}
void Student::registercourse() {
    string courseName;
    cout << "Enter course name to register: ";
    getline(cin, courseName);

    Course course = findcourse(courseName);
    if (course.title.empty()) {
        cout << "Course not found.\n";
        return;
    }

    if (alreadyRegistered(courseName)) {
        cout << "You are already registered in this course.\n";
        system("pause");

        return;
    }

    // EDIT 
    if (!isCourseValid(courseName)) {
        cout << "Course not found or name is incorrect.\n";
        return;
    }
   // END

    if (!prerequisitesMet(course.prerequisites)) {
        cout << "Prerequisites not met for this course.\n";
        system("pause");

        return;
    }

    unordered_map<int, vector<string>> registrations = readRegistrationsFile("registrations.csv");
    registrations[getStudentID()].push_back(courseName);

    ofstream outFile("registrations.csv");



    //START EDIT
	// هنا بنجيب عدد الكورسات المسجلة لكل طالب
    int maxCourses = 0;
    for (const auto& entry : registrations) {
        if (entry.second.size() > maxCourses) {
            maxCourses = entry.second.size();
        }
    }
    // Write dynamic header
    outFile << "UserID";
    for (int i = 1; i <= maxCourses; i++) {
        outFile << ",Subject" << i;
    }
    outFile << "\n";
    //END EDIT



    unordered_map<int, vector<string>>::iterator it = registrations.begin();
    while (it != registrations.end()) {
        outFile << it->first;
        vector<string> courseList = it->second;
        for (int i = 0; i < courseList.size(); i++) {
            outFile << "," << courseList[i];
        }
        outFile << "\n";
        it++;
    }

    outFile.close();
    cout << "Registered successfully.\n";
    system("pause");

}







 //Mohamed
struct Grade {
    std::string subject;
    int quiz;
    int assignment;
    int midterm;
    int practical;
    int final;
    int total;
    double gpa;
};
void Student::viewGrades() {
    std::ifstream file("grades.csv");
    if (!file.is_open()) {
        std::cout << "Error: Unable to open grades.csv" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header

    // Print table header
    std::cout << std::left
        << std::setw(15) << "Subject"
        << std::setw(10) << "Quiz"
        << std::setw(10) << "Assignment"
        << std::setw(10) << "Midterm"
        << std::setw(10) << "Practical"
        << std::setw(10) << "Final"
        << std::setw(10) << "Total"
        << std::setw(10) << "GPA" << std::endl;
    std::cout << std::string(85, '-') << std::endl;
    system("pause");
    bool found = false;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, subject, quiz, assignment, midterm, practical, final, total, gpa;
        std::getline(ss, id, ',');
        std::getline(ss, subject, ',');
        std::getline(ss, quiz, ',');
        std::getline(ss, assignment, ',');
        std::getline(ss, midterm, ',');
        std::getline(ss, practical, ',');
        std::getline(ss, final, ',');
        std::getline(ss, total, ',');
        std::getline(ss, gpa);

        if (id == username) {
            found = true;
            std::cout << std::left
                << std::setw(15) << subject
                << std::setw(10) << quiz
                << std::setw(10) << assignment
                << std::setw(10) << midterm
                << std::setw(10) << practical
                << std::setw(10) << final
                << std::setw(10) << total
                << std::setw(10) << gpa << std::endl;
        }
    }

    if (!found) {
        std::cout << "No grades found for student ID: " << username << std::endl;
        system("pause");

    }

    file.close();
}
void Student::filterGrades() {
    std::ifstream file("grades.csv");
    if (!file.is_open()) {
        std::cout << "Error: Unable to open grades.csv" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header

    std::cout << "Filter Grades:" << std::endl;
    std::cout << "1. By Subject" << std::endl;
    std::cout << "2. By GPA" << std::endl;
    std::cout << "3. By Total" << std::endl;
    std::cout << "Enter choice (1-3, or 0 to exit): ";
    system("pause");

    int choice;
    std::cin >> choice;
    std::cin.ignore(); // Clear newline

    if (choice == 0) return;

    std::string filterSubject, filterGPA, filterTotal;
    if (choice == 1) {
        std::cout << "Enter Subject (e.g., Probability): ";
        std::getline(std::cin, filterSubject);
    }
    else if (choice == 2) {
        std::cout << "Enter GPA (e.g., 4): ";
        std::getline(std::cin, filterGPA);
    }
    else if (choice == 3) {
        std::cout << "Enter Total (e.g., 100): ";
        std::getline(std::cin, filterTotal);
    }
    else {
        std::cout << "Invalid choice!" << std::endl;
        file.close();
        return;
    }

    // Print table header
    std::cout << std::left
        << std::setw(15) << "Subject"
        << std::setw(10) << "Quiz"
        << std::setw(10) << "Assignment"
        << std::setw(10) << "Midterm"
        << std::setw(10) << "Practical"
        << std::setw(10) << "Final"
        << std::setw(10) << "Total"
        << std::setw(10) << "GPA" << std::endl;
    std::cout << std::string(85, '-') << std::endl;
    system("pause");

    bool found = false;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, subject, quiz, assignment, midterm, practical, final, total, gpa;
        std::getline(ss, id, ',');
        std::getline(ss, subject, ',');
        std::getline(ss, quiz, ',');
        std::getline(ss, assignment, ',');
        std::getline(ss, midterm, ',');
        std::getline(ss, practical, ',');
        std::getline(ss, final, ',');
        std::getline(ss, total, ',');
        std::getline(ss, gpa);

        if (id == username &&
            (filterSubject.empty() || subject == filterSubject) &&
            (filterGPA.empty() || gpa == filterGPA) &&
            (filterTotal.empty() || total == filterTotal)) {
            found = true;
            std::cout << std::left
                << std::setw(15) << subject
                << std::setw(10) << quiz
                << std::setw(10) << assignment
                << std::setw(10) << midterm
                << std::setw(10) << practical
                << std::setw(10) << final
                << std::setw(10) << total
                << std::setw(10) << gpa << std::endl;
        }
    }

    if (!found) {
        std::cout << "No grades found for student ID: " << username;
        if (!filterSubject.empty()) std::cout << " with subject: " << filterSubject;
        if (!filterGPA.empty()) std::cout << " with GPA: " << filterGPA;
        if (!filterTotal.empty()) std::cout << " with Total: " << filterTotal;
        std::cout << std::endl;
    }
    system("pause");

    file.close();
}
void Student::exportGradesToCSV() {
    std::ifstream file("grades.csv");
    if (!file.is_open()) {
        std::cout << "Error: Unable to open grades.csv" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header

    std::vector<Grade> grades;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, subject, quiz, assignment, midterm, practical, final, total, gpa;
        std::getline(ss, id, ',');
        std::getline(ss, subject, ',');
        std::getline(ss, quiz, ',');
        std::getline(ss, assignment, ',');
        std::getline(ss, midterm, ',');
        std::getline(ss, practical, ',');
        std::getline(ss, final, ',');
        std::getline(ss, total, ',');
        std::getline(ss, gpa);

        if (id == username) {
            Grade grade;
            grade.subject = subject;
            grade.quiz = std::stoi(quiz);
            grade.assignment = std::stoi(assignment);
            grade.midterm = std::stoi(midterm);
            grade.practical = std::stoi(practical);
            grade.final = std::stoi(final);
            grade.total = std::stoi(total);
            grade.gpa = std::stod(gpa);
            grades.push_back(grade);
        }
    }
    file.close();

    if (grades.empty()) {
        std::cout << "No grades found to export for student ID: " << username << std::endl;
        return;
    }

    std::string filename = "Grades_" + username + ".csv";
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "Error: Unable to create " << filename << std::endl;
        return;
    }

    outFile << "Subject,Quiz,Assignment,Midterm,Practical,Final,Total,GPA\n";
    for (const auto& grade : grades) {
        outFile << grade.subject << ","
            << grade.quiz << ","
            << grade.assignment << ","
            << grade.midterm << ","
            << grade.practical << ","
            << grade.final << ","
            << grade.total << ","
            << grade.gpa << "\n";
    }

    outFile.close();
    std::cout << "Grades exported successfully to " << filename << std::endl;
}





//Farah
void Student::generateReport(const string& id) {
	void Student::generateReport(const string& id) {
    system("cls");

    cout << "******** Student Grade Report ********\n";

    // Step 1: Display Student Name and ID
    cout << "Name: " << Student::username << endl;
    cout << "ID: " << id << endl;

    // Step 2: Read Registered Courses
    ifstream regFile("registrations.csv");
    if (!regFile.is_open()) {
        cout << "Error: Could not open registrations.csv\n";
        return;
    }

    string line;
    getline(regFile, line); // Skip the header line

    bool found = false;
    vector<string> registeredCourses;

    while (getline(regFile, line)) {
        stringstream ss(line);
        string userID;
        getline(ss, userID, ',');

        if (userID == id) { // Match using the provided ID
            found = true;
            string course;
            while (getline(ss, course, ',')) {
                registeredCourses.push_back(course);
            }
            break;
        }
    }

    regFile.close();

    if (!found) {
        cout << "No registration data found for user with ID: " << id << "\n";
        system("pause");
        return;
    }

    // Step 3: Read Grades
    ifstream gradesFile("grades.csv");
    if (!gradesFile.is_open()) {
        cout << "Error: Could not open grades.csv\n";
        return;
    }

    getline(gradesFile, line); // Skip the header line

    struct Grade {
        int quiz, assignment, midterm, practical, finalExam, total;
        double gpa;
    };

    map<string, Grade> courseGrades; // Map to store course title and its grades
    while (getline(gradesFile, line)) {
        stringstream ss(line);
        string gradeID, subject;
        Grade grade;

        getline(ss, gradeID, ',');
        getline(ss, subject, ',');
        ss >> grade.quiz;
        ss.ignore();
        ss >> grade.assignment;
        ss.ignore();
        ss >> grade.midterm;
        ss.ignore();
        ss >> grade.practical;
        ss.ignore();
        ss >> grade.finalExam;
        ss.ignore();
        ss >> grade.total;
        ss.ignore();
        ss >> grade.gpa;

        if (gradeID == id) { // Match grades by student ID
            courseGrades[subject] = grade;
        }
    }

    gradesFile.close();

    // Step 4: Divide Courses into Semesters
    ifstream coursesFile("courses.csv");
    if (!coursesFile.is_open()) {
        cout << "Error: Could not open courses.csv\n";
        return;
    }

    getline(coursesFile, line); // Skip the header line

    map<string, int> courseCreditHours; // Map to store course title and its credit hours
    while (getline(coursesFile, line)) {
        stringstream ss(line);
        string title, syllabus, creditHours, instructor, prerequisites;

        getline(ss, title, ',');
        getline(ss, syllabus, ',');
        getline(ss, creditHours, ',');
        getline(ss, instructor, ',');
        getline(ss, prerequisites);

        if (!creditHours.empty()) {
            courseCreditHours[title] = stoi(creditHours); // Store credit hours for each course
        }
        else {
            cout << "Warning: Missing credit hours for course: " << title << "\n";
            courseCreditHours[title] = 0; // Assign a default value or skip
        }
    }


    coursesFile.close();

    vector<vector<string>> semesters;
    vector<string> currentSemester;
    int currentSemesterHours = 0;

    for (const string& course : registeredCourses) {
        if (courseCreditHours.find(course) != courseCreditHours.end()) {
            int courseHours = courseCreditHours[course];
            if (currentSemesterHours + courseHours > 15) {
                // Start a new semester
                semesters.push_back(currentSemester);
                currentSemester.clear();
                currentSemesterHours = 0;
            }
            currentSemester.push_back(course);
            currentSemesterHours += courseHours;
        }
    }

    // Add the last semester if it has courses
    if (!currentSemester.empty()) {
        semesters.push_back(currentSemester);
    }

    // Step 5: Display Courses by Semester with Grades
    cout << "\n******** Registered Courses by Semester ********\n";
    double totalGPA = 0;
    int courseCount = 0;

    for (size_t i = 0; i < semesters.size(); ++i) {
        cout << "Semester " << (i + 1) << ":\n";
        for (const string& course : semesters[i]) {
            cout << "- " << course << " (" << courseCreditHours[course] << " credit hours)";
            if (courseGrades.find(course) != courseGrades.end()) {
                const Grade& grade = courseGrades[course];
                cout << " | Quiz: " << grade.quiz
                    << " | Assignment: " << grade.assignment
                    << " | Midterm: " << grade.midterm
                    << " | Practical: " << grade.practical
                    << " | Final: " << grade.finalExam
                    << " | Total: " << grade.total
                    << " | GPA: " << grade.gpa;
                totalGPA += grade.gpa;
                courseCount++;
            }
            else {
                cout << " | Grade: N/A";
            }
            cout << "\n";
        }
        cout << "-------------------------------\n";
    }

    // Step 6: Calculate and Display Overall GPA
    if (courseCount > 0) {
        double overallGPA = totalGPA / courseCount;
        cout << "\nOverall GPA: " << overallGPA << endl;
    }
    else {
        cout << "\nNo grades found for your registered courses.\n";
    }

    cout << "*\n";
    system("pause");
}
    
}
