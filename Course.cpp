#include <iostream>
#include <string>
#include <vector>
#include<unordered_map>
using namespace std;

class Course {
private:
    string courseTitle;
    string courseCode;
    string syllabus;
    int creditHours;
    unordered_map<string, vector<string>> grades;

public:
    
    Course();
    Course(string courseTitle,string courseCode,string syllabus,int creditHours, unordered_map<string, vector<string>> grades);

    
  
   
};
