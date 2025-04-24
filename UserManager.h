#ifndef USERMANAGER_H
#define USERMANAGER_H
#include <string> 
class UserManager {
public:
    std::string UN; 
public:
    UserManager() { UN = ""; };
    void login();
    void registerUser();
    void forgot();
};

#endif
