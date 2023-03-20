#include <iomanip>
#include <algorithm>
#include "functionality.h"
#include "helpFunc.h"

ifstream getFileWithCheckExists(char *path) {
    ifstream file;
    string pathToFile;
    if (path != nullptr) pathToFile = path;
    string prefix = "../";
    bool isOpen = false;
    if (!pathToFile.empty()) {
        if (pathToFile.find(':') == std::string::npos) pathToFile = prefix.append(pathToFile);
        file.open(pathToFile);
        if (file.is_open()) {
            if (pathToFile.substr(pathToFile.find_last_of('.') + 1) == "txt") isOpen = true;
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("Расширение файла не txt!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                exit(0);
            }
        } else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Неправильный путь к файлу!\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            exit(0);
        }
        isOpen = true;
    }
    while (!isOpen) {
        cout << "Введите путь к файлу" << endl;
        prefix = "../";
        cin >> pathToFile;
        if (pathToFile.find(':') == std::string::npos) pathToFile = prefix.append(pathToFile);
//        replace(pathToFile.begin(), pathToFile.end(), '/', '\\');
        file.open(pathToFile);
        if (file.is_open()) {
            if (pathToFile.substr(pathToFile.find_last_of('.') + 1) == "txt") isOpen = true;
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
        prefix = "../";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    printf("Файл успешно открыт!\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    return file;
}

vector<string> readAllLinesFromFile(ifstream &file) {
    string line;
    vector<string> allLines;
    while (getline(file, line)) {
        allLines.push_back(line);
    }
    return allLines;
}

void getAllWordsFromLines(vector<string> &lines, vector<Word> &words) {
    vector<string> splitLine;
    for (int i = 0; i < lines.size(); ++i) {
        splitLine = split(lines.at(i), ' ');
        for (int j = 0; j < splitLine.size(); ++j) {
            Word word(j, i, splitLine.at(j));
            words.push_back(word);
        }
    }
}

void showMenu(vector<Word> &first, vector<Word> &second) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout.width(45), cout << "first", cout.width(50), cout << "|", cout.width(45), cout << "second" << endl;
    int countFirst = 0, countSecond = 0, countLine = 0;
    cout.fill(' ');
    int sizeLine;
    Word *word;
    while (countFirst < first.size() || countSecond < second.size()) {
        sizeLine = 0;
        do {
            if (countFirst == first.size()) break;
            word = &(first.at(countFirst));
            if (countLine != word->getNumberLine()) break;
            word->getStatus() == RED ? SetConsoleTextAttribute(hConsole, 12) :
            word->getStatus() == GREEN ? SetConsoleTextAttribute(hConsole, 10) : SetConsoleTextAttribute(hConsole, 7);
            cout << (*word).getStatement() << " ";
            sizeLine += word->getStatement().size() + 1;
            countFirst++;
        } while (true);
        cout << setw(95 - sizeLine);
        SetConsoleTextAttribute(hConsole, 6);
        cout << "|";
        sizeLine = 0;
        do {
            if (countSecond == second.size()) break;
            word = &(second.at(countSecond));
            if (countLine != word->getNumberLine()) break;
            word->getStatus() == RED ? SetConsoleTextAttribute(hConsole, 12) :
            word->getStatus() == GREEN ? SetConsoleTextAttribute(hConsole, 10) : SetConsoleTextAttribute(hConsole, 7);
            cout << word->getStatement() << " ";
            sizeLine += word->getStatement().size();
            countSecond++;
        } while (true);
        cout << endl;
        countLine++;
    }
    SetConsoleTextAttribute(hConsole, 7);
}

void findDiff(vector<Word> &wordsFromFirstFile, vector<Word> &wordsFromSecondFile) {
    for (const Word &w: wordsFromFirstFile) {
        for (int i = 0; i < wordsFromSecondFile.size(); ++i) {
            if (w.getStatement() == wordsFromSecondFile.at(i).getStatement() &&
                wordsFromSecondFile.at(i).getStatus() != GREEN) {
                wordsFromSecondFile.at(i).setStatus(GREEN);
                i = wordsFromSecondFile.size();
            } else {
                if (wordsFromSecondFile.at(i).getStatus() != GREEN) { wordsFromSecondFile.at(i).setStatus(RED); }
            }
        }
    }
}