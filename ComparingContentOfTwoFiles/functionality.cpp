#include <iomanip>
#include "functionality.h"

ifstream getFileWithCheckExists() {
    ifstream file;
    string path;
    bool isOpen = false;
    while (!isOpen) {
        cout << "Введите путь к файлу" << endl;
        cin >> path;
        file.open(path);
        if (file.is_open()) {
            if (path.substr(path.find_last_of('.') + 1) == "txt") isOpen = true;
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("Расширение файла не txt! Попробуйте снова!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            }
        } else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Неправильный путь к файлу! Попробуйте снова!\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    printf("Файл успешно открыт!\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    return file;
}
vector<string> readAllLinesFromFile(ifstream& file) {
    string line;
    vector<string> allLines;
    while(getline(file,line)) {
        allLines.push_back(line);
    }
    return allLines;
}
void showMenu(vector<string> first, vector<string> second) {
    cout.width(30),cout << "first",cout.width(30), cout << "|",cout.width(30),cout << "second" << endl;
    int i = 0;
    string lineFirstFile, lineSecondFile;
    cout.fill(' ');
    while(i < max(first.size(),second.size())) {
        if(i < first.size()) lineFirstFile = first.at(i);
        if(i < second.size()) lineSecondFile = second.at(i);
        cout << lineFirstFile << setw(60 - lineFirstFile.size());
        cout << "|";
        cout << lineSecondFile;
        cout << endl;
        i++;
    }
}