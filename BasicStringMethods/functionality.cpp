#include <cstdio>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include "functionality.h"
#include "constants.h"

void showMenu(short position, unsigned char firstString[], unsigned char secondString[]) {
    system("cls");
    printf("Выберите действие:\n");
    printf("1) Узнать длину строк%s\n", position == 1 ? " <--" : " ");
    printf("2) Внедрить одну строку в другую%s\n", position == 2 ? " <--" : " ");
    printf("3) Скопировать одну строку в другую%s\n", position == 3 ? " <--" : " ");
    printf("4) Перевернуть строки%s\n", position == 4 ? " <--" : " ");
    printf("5) Перевести строки в строчный вид%s\n", position == 5 ? " <--" : " ");
    printf("6) Перевести строки в заглавный вид%s\n", position == 6 ? " <--" : " ");
    printf("7) Изменить первую строку%s\n", position == 7 ? " <--" : " ");
    printf("8) Изменить вторую строку%s\n", position == 8 ? " <--" : " ");
    printf("9) Выход%s\n", position == 9 ? " <--" : " ");
    printf("Первая строка = %s\n", firstString);
    printf("Вторая строка = %s\n", secondString);
}

inline void showHelloMessage() {
    printf("Приветствую!\n");
}
void strLowerCase(unsigned char string[]) {
    int i = 0;
    unsigned char symbol;
    while (string[i] != END_STRING) {
        symbol = string[i];
        if(65 <= symbol && symbol <= 90) string[i] = symbol + 32;
        ++i;
    }
}

void strUpperCase(unsigned char string[]) {
    int i = 0;
    unsigned char symbol;
    while (string[i] != END_STRING) {
        symbol = string[i];
        if(97 <= symbol && symbol <= 122) string[i] = symbol - 32;
        ++i;
    }
}

int strLength(const unsigned char string[]) {
    int i = 0;
    while (string[i] != END_STRING) ++i;
    return i;
}

void initStringHollow(unsigned char string[]) {
    for (int i = 0; i < strLength(string); ++i) string[i] = ' ';
}

bool strCat(unsigned char firstString[], const unsigned char secondString[], short start) {
    unsigned char tempString[MAX_LENGTH_STRING + 1];
    int i, j = 0;
    for (i = 0; i < start; ++i)
        tempString[i] = firstString[i];
    for (; i < strLength(secondString) + start; ++i, ++j)
        tempString[i] = secondString[j];
    j = 0;
    for (; i < MAX_LENGTH_STRING; ++i, ++j) {
        tempString[i] = firstString[start + j];
    }
    tempString[MAX_LENGTH_STRING] = END_STRING;
    if (strLength(tempString) >= MAX_LENGTH_STRING) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("Невозможно внедрить строку, так как при внедрении её длина превышает максимальную!\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        return false;
    }
    strCopy(firstString, tempString);
    return true;
}

void strReverse(unsigned char string[]) {
    short length = strLength(string);
    for (int i = 0, j = length - 1; i < length / 2; i++, j--) {
        unsigned char temp = string[i];
        string[i] = string[j];
        string[j] = temp;
    }
}

void strCopy(unsigned char firstString[], const unsigned char secondString[]) {
    for (int i = 0; i < MAX_LENGTH_STRING; ++i)
        firstString[i] = secondString[i];
}

bool checkLatin(const unsigned char string[]) {
    int i = 0;
    while (string[i] != END_STRING) {
        if (string[i] > 127) return false;
        ++i;
    }
    return true;
}

void validationString(unsigned char string[]) {
    unsigned char tempString[MAX_LENGTH_STRING + 1];
    bool exitFlag = false;
    while (!exitFlag) {
        std::cin >> tempString;
        tempString[MAX_LENGTH_STRING] = END_STRING;
        if (strLength(tempString) < MAX_LENGTH_STRING) {
            if (checkLatin(tempString)) {
                exitFlag = true;
            } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("В строке содержится кириллица!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            }
        } else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Строка слишком длинная!\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
    }
    strCopy(string, tempString);
    string[MAX_LENGTH_STRING - 1] = END_STRING;
    fflush(stdin);
}

void consoleInterface() {
    SetConsoleOutputCP(CP_UTF8);
    bool exitFlag = false, permissionFlag;
    unsigned char firstString[MAX_LENGTH_STRING] = " ";
    unsigned char secondString[MAX_LENGTH_STRING] = " ";
    short symbol;
    short position = 0;
    short pointInsert;
    char YN;
    showHelloMessage();
    printf("Введите первую строку!(не более 20 символов)\n");
    validationString(firstString);
    printf("Введите вторую строку!(не более 20 символов)\n");
    validationString(secondString);
    showMenu(position, firstString, secondString);
    while (!exitFlag) {
        permissionFlag = false;
        symbol = (short) getch();
        if (symbol == FIRST_BYTE_ARROW) symbol = (short) getch();
        switch (symbol) {
            case ARROW_UP:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION;
                break;
            case ARROW_DOWN:
                if (position < MAX_ARROW_POSITION) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case W:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION;
                break;
            case S:
                if (position < MAX_ARROW_POSITION) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case ESC:
                printf("Вы уверены что хотите выйти?(Y/N)\n");
                scanf("%s", &YN);
                if (YN == 'Y') exitFlag = true;
                break;
            case ENTER:
                permissionFlag = true;
                break;
            case ONE:
                position = 1;
                break;
            case TWO:
                position = 2;
                break;
            case THREE:
                position = 3;
                break;
            case FOUR:
                position = 4;
                break;
            case FIVE:
                position = 5;
                break;
            case SIX:
                position = 6;
                break;
            case SEVEN:
                position = 7;
                break;
            case EIGHT:
                position = 8;
                break;
            case NINE:
                position = 9;
                break;
            default:;
        }
        showMenu(position, firstString, secondString);
        switch (position) {
            case 1:
                if (permissionFlag) {
                    printf("Длина первой строки: %d\n", strLength(firstString));
                    printf("Длина второй строки: %d\n", strLength(secondString));
                }
                break;
            case 2:
                if (permissionFlag) {
                    if (strLength(firstString) + strLength(secondString) >= MAX_LENGTH_STRING) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                        printf("Невозможно внедрить строку, так как при внедрении её длина превышает максимальную!\n");
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                        break;
                    }
                    printf("В какую строку вы хотите внедрить другую?(1/2)\n");
                    YN = (char) getchar();
                    printf("С какого символа начать внедрение?\n");
                    if (YN == '1') {
                        pointInsert = (short) validationWithArgument((short) strLength(secondString));
                        if (strCat(firstString, secondString, pointInsert))
                            showMenu(position, firstString, secondString);
                    } else if (YN == '2') {
                        pointInsert = (short) validationWithArgument((short) strLength(firstString));
                        if (strCat(secondString, secondString, pointInsert))
                            showMenu(position, firstString, secondString);
                    }
                }
                break;
            case 3:
                if (permissionFlag) {
                    printf("В какую строку вы хотите скопировать другую?(1/2)\n");
                    YN = (char) getchar();
                    if (YN == '1') {
                        strCopy(firstString, secondString);
                    } else if (YN == '2') {
                        strCopy(secondString, firstString);
                    }
                    showMenu(position, firstString, secondString);
                }
                break;
            case 4:
                if (permissionFlag) {
                    strReverse(firstString);
                    strReverse(secondString);
                    showMenu(position, firstString, secondString);
                }
                break;
            case 5:
                if (permissionFlag) {
                    strLowerCase(firstString);
                    strLowerCase(secondString);
                    showMenu(position, firstString, secondString);
                }
                break;
            case 6:
                if (permissionFlag) {
                    strUpperCase(firstString);
                    strUpperCase(secondString);
                    showMenu(position, firstString, secondString);
                }
                break;
            case 7:
                if (permissionFlag) {
                    printf("Введите строку\n");
                    validationString(firstString);
                    showMenu(position, firstString, secondString);
                }
                break;
            case 8:
                if (permissionFlag) {
                    printf("Введите строку\n");
                    validationString(secondString);
                    showMenu(position, firstString, secondString);
                }
                break;
            case 9:
                if (permissionFlag) {
                    printf("Вы уверены что хотите выйти?(Y/N)\n");
                    scanf("%s", &YN);
                    if (YN == 'Y') exitFlag = true;
                }
                break;
            default:;
        }
    }
}

long validation() {
    bool validationFlag = false;
    double result;
    while (!validationFlag) {
        if (scanf("%lf", &result)) {
            if (!checkOverflow(result)) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("Неправильный ввод! Число вышло за границу дозволенного! Попробуйте снова!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            } else validationFlag = true;
        } else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Неправильный ввод! Попробуйте снова!\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
        fflush(stdin);
    }
    return (long) result;
}

long validationWithArgument(short max) {
    long result;
    short minArea = 0, maxArea = max;
    do {
        result = validation();
        if (result > maxArea || result < minArea) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Неверный ввод! Значение должно быть от %hd до %hd\n", minArea,
                   maxArea);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
    } while (result > maxArea || result < minArea);
    return result;
}

bool checkOverflow(double d) {
    return d >= -2147483648 && d <= 2147483647;
}
