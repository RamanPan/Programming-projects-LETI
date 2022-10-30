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
    printf("Первая строка = %s, Вторая строка = %s\n", firstString, secondString);
}

void showHelloMessage() {
    printf("Приветствую!\n");
}

int strLength(const unsigned char string[]) {
    int i = 0;
    while (string[i] != END_STRING) ++i;
    return i;
}

void strCopy(unsigned char firstString[], unsigned char secondString[], bool whichString) {
    if (whichString) {
        for (int i = 0; i < strLength(secondString); ++i)
            firstString[i] = secondString[i];
    } else {
        for (int i = 0; i < strLength(firstString); ++i)
            secondString[i] = firstString[i];
    }
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
    strCopy(string, tempString, true);
    string[MAX_LENGTH_STRING - 1] = END_STRING;
    fflush(stdin);
}

void consoleInterface() {
    SetConsoleOutputCP(CP_UTF8);
    bool exitFlag = false, permissionFlag;
    unsigned char firstString[MAX_LENGTH_STRING] = "", secondString[MAX_LENGTH_STRING] = "";
    short symbol;
    short position = 0;
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

                }
                break;
            case 2:
                if (permissionFlag) {

                }
                break;
            case 3:
                if (permissionFlag) {

                }
                break;
            case 4:
                if (permissionFlag) {

                }
                break;
            case 5:
                if (permissionFlag) {

                }
                break;
            case 6:
                if (permissionFlag) {

                }
                break;
            case 7:
                if (permissionFlag) {

                }
                break;
            case 8:
                if (permissionFlag) {

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
