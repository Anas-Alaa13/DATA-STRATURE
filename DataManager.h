//Files Management

#include <map>
#include <vector>
#include <string>
#include "Structures.h"
#ifndef DATAMANAGER_H
#define DATAMANAGER_H


class DataManager {
public:
    std::vector<User> users;
    std::vector<Course> courses;
    std::map<int, std::vector<std::string>> registrations;
    std::vector<Grade> grades;

    DataManager();
    void readUsers(const std::string& filename);
    void readCourses(const std::string& filename);
    void readRegistrations(const std::string& filename);
    void readGrades(const std::string& filename);
    void writeUsers(const std::string& filename);
    void writeCourses(const std::string& filename);
    void writeRegistrations(const std::string& filename);
    void writeGrades(const std::string& filename);
    void saveAllData();
};

#endif