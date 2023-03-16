#ifndef COMPARINGCONTENTOFTWOFILES_FUNCTIONALITY_H
#define COMPARINGCONTENTOFTWOFILES_FUNCTIONALITY_H

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <utility>
#include <vector>
#include <cstdio>
#include <conio.h>

#define ESC 27
using namespace std;
enum Status {
    RED, GREEN, NORMAL
};

class Word {
    int position;
    int numberLine;
    string statement;
    Status status;

public:
    Word(int position, int numberLine, string statement) {
        this->position = position;
        this->numberLine = numberLine;
        this->statement = std::move(statement);
        status = NORMAL;
    }


    int getPosition() const {
        return position;
    }

    void setPosition(int pos) {
        Word::position = pos;
    }

    int getNumberLine() const {
        return numberLine;
    }

    void setNumberLine(int number) {
        Word::numberLine = number;
    }

    const string &getStatement() const {
        return statement;
    }

    void setStatus(Status rightNow) {
        status = rightNow;
    }

    void setStatement(const string &state) {
        Word::statement = state;
    }

    Status getStatus() const {
        return status;
    }
};

ifstream getFileWithCheckExists();

ifstream getFileWithCheckExists(char* path);

void findDiff(vector<Word> &wordsFromFirstFile, vector<Word> &wordsFromSecondFile);


void getAllWordsFromLines(vector<string> &lines, vector<Word> &words);

void showMenu(vector<Word> &first, vector<Word> &second);

vector<string> readAllLinesFromFile(ifstream &file);

#endif //COMPARINGCONTENTOFTWOFILES_FUNCTIONALITY_H
