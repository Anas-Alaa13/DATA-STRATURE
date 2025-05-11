                                                                    //Anas

#ifndef LOGINSYSTEM_H
#define LOGINSYSTEM_H

#include "DataManager.h"

class LoginSystem {
private:
    DataManager& dm;

public:
    LoginSystem(DataManager& data);
    void displayMenu();
};

#endif