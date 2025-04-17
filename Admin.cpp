#pragma once
#include <string>
#include<iostream>
#include "User.h"
using namespace std;

class Admin :public User {
private:
    string id;
    string name;
    string password;

public:
    Admin();
   Admin( string id,  string name,  string password);
   
};
