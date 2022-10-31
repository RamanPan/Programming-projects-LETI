#ifndef BASICSTRINGMETHODS_FUNCTIONALITY_H
#define BASICSTRINGMETHODS_FUNCTIONALITY_H

void showMenu(int position, unsigned char firstString[], unsigned char secondString[]);

void validationString(unsigned char string[], short maxLength);

bool checkOverflow(double d);

long validation();

long validationWithArgument(short max);

void consoleInterface();

void showHelloMessage();

int strLength(const unsigned char string[]);

bool checkLatin(const unsigned char string[]);

void initStringHollow(unsigned char string[]);

bool strCat(unsigned char firstString[], const unsigned char secondString[], short start);

void strCopy(unsigned char firstString[], const unsigned char secondString[]);

void strReverse(unsigned char string[]);

void strLowerCase(unsigned char string[]);

void strUpperCase(unsigned char string[]);

#endif //BASICSTRINGMETHODS_FUNCTIONALITY_H
