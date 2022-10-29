#include <cstdio>
#include <conio.h>
#include <windows.h>
#include "functionality.h"
#include "constants.h"

void showMenu(short position, char firstString[], char secondString[]) {
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



void consoleInterface() {
    SetConsoleOutputCP(CP_UTF8);
    bool exitFlag = false, permissionFlag;
    char firstString[MAX_LENGTH_STRING], secondString[MAX_LENGTH_STRING];
    short symbol;
    short position = 0;
    char YN;
    showHelloMessage();
    printf("Введите первую строку!(не более 20 символов)\n");
    validationString(firstString, MAX_LENGTH_STRING);
    printf("Введите вторую строку!(не более 20 символов)\n");
    validationString(secondString, MAX_LENGTH_STRING);
    showMenu(position,firstString,secondString);
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
