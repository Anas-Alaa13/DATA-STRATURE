//Files Management

#include <map>
#include <vector>
#include <string>
#include "Structures.h"
#include<set>

#ifndef DATAMANAGER_H
#define DATAMANAGER_H
using namespace std;

class DataManager {
public:
     vector<User> users;
     vector<Course> courses;
     set< string> courseTitles;
     map<int,  vector< string>> registrations;
     vector<Grade> grades;

    DataManager();
    void readUsers(const  string& filename);
    void readCourses(const  string& filename);
    void readRegistrations(const  string& filename);
    void readGrades(const  string& filename);
    void writeUsers(const  string& filename);
    void writeCourses(const  string& filename);
    void writeRegistrations(const  string& filename);
    void writeGrades(const  string& filename);
    void saveAllData();
};

#endif