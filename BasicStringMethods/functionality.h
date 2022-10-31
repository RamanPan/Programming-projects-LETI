#ifndef BASICSTRINGMETHODS_FUNCTIONALITY_H
#define BASICSTRINGMETHODS_FUNCTIONALITY_H

void showMenu(int position, unsigned char firstString[], unsigned char secondString[]);

void validationString(unsigned char string[], short maxLength);

void consoleInterface();

void showHelloMessage();

int strLength(const unsigned char string[]);

bool checkLatin(const unsigned char string[]);

void initStringHollow(unsigned char string[]);

void strCat(unsigned char firstString[], unsigned char secondString[], short start, bool whichString);

void strCopy(unsigned char firstString[], const unsigned char secondString[]);

void strReverse(unsigned char string[]);

void strLowerCase(unsigned char string[]);

void strUpperCase(unsigned char string[]);

#endif //BASICSTRINGMETHODS_FUNCTIONALITY_H
