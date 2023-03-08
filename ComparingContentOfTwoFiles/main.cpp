#include <conio.h>
#include "functionality.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    ifstream firstFile = getFileWithCheckExists(), secondFile = getFileWithCheckExists();
    vector<string> allLinesFirstFile = readAllLinesFromFile(firstFile), allLinesSecondFile = readAllLinesFromFile(
            secondFile);
    bool exit = false;
    short symbol;
    while (!exit) {
        system("cls");
        showMenu(allLinesFirstFile, allLinesSecondFile);
        symbol = getch();
        if (symbol == ESC) exit = true;
    }
    firstFile.close();
    secondFile.close();
}
