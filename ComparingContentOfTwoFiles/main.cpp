#include <conio.h>
#include "functionality.h"

int main(int argc, char *argv[]) {
    system("mode con cols=200 lines=50");
    SetConsoleOutputCP(CP_UTF8);
    cout << *argv;
    ifstream firstFile = getFileWithCheckExists(argv[1]), secondFile = getFileWithCheckExists(argv[2]);
    vector<string> allLinesFirstFile = readAllLinesFromFile(firstFile), allLinesSecondFile = readAllLinesFromFile(
            secondFile);
    firstFile.close();
    secondFile.close();
    vector<Word> wordsFromFirstFile, wordsFromSecondFile;
    getAllWordsFromLines(allLinesFirstFile, wordsFromFirstFile);
    getAllWordsFromLines(allLinesSecondFile, wordsFromSecondFile);
    bool exit = false;
    short symbol;
    findDiff(wordsFromFirstFile, wordsFromSecondFile);
    while (!exit) {
        system("cls");
        showMenu(wordsFromFirstFile, wordsFromSecondFile);
        symbol = getch();
        if (symbol == ESC) exit = true;
    }
}
