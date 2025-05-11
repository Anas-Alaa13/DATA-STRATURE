#include "LoginSystem.h"
#include "DataManager.h"

int main() {
    DataManager dm;
    LoginSystem ls(dm);
    ls.displayMenu();
    return 0;
}