#include <iostream>
#include "Messages.h"
#include "windows.h"

void showErrorMessage(const std::string &message) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    std::cout << message << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void showInfoMessage(const std::string &message) {
    std::cout << message << std::endl;
}
