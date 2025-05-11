                                    //Anas


#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "DataManager.h"

class UserManager {
public:
    void login(DataManager& dm);
    void registerUser(DataManager& dm);
    void forgot(DataManager& dm);
};

#endif