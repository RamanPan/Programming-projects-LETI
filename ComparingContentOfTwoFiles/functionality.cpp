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

void showMenu(ifstream& first, ifstream& second) {
    cout.width(30),cout << "first",cout.width(30), cout << "|",cout.width(30),cout << "second";
    string lineFirstFile,lineSecondFile;
    while(!first.eof() && !second.eof()) {
        if(!first.eof()) getline(first,lineFirstFile);
        else lineFirstFile = "";
        if(!second.eof()) getline(second,lineSecondFile);
        else lineSecondFile = "";
        cout.width(30);
        cout << lineFirstFile;
        cout.width(30);
        cout << "|";
        cout.width(30);
        cout << lineSecondFile;
    }
}