#ifndef COMPARINGCONTENTOFTWOFILES_FUNCTIONALITY_H
#define COMPARINGCONTENTOFTWOFILES_FUNCTIONALITY_H
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
#define ESC 27
using namespace std;
ifstream getFileWithCheckExists();

void showMenu(ifstream& first, ifstream& second);

#endif //COMPARINGCONTENTOFTWOFILES_FUNCTIONALITY_H
