//
// Created by vpana on 28.10.2022.
//

#ifndef BASICSTRINGMETHODS_FUNCTIONALITY_H
#define BASICSTRINGMETHODS_FUNCTIONALITY_H
void showMenu(int position, char firstString[], char secondString[]);

void validationString(char string[], short maxLength);

void consoleInterface();

int strLength(char string[]);

void strCat(char firstString[], char secondString[], short start, bool whichString);

void strCopy(char firstString[], char secondString[], bool whichString);

void strReverse(char string[]);

void strLowerCase(char string[]);

void strUpperCase(char string[]);

#endif //BASICSTRINGMETHODS_FUNCTIONALITY_H
