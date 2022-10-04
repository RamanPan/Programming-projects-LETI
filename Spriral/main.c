#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include "functionality.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    bool exitFlag = false;
    short I, J;
    short symbol;
    short minPosition = 1, maxPosition = 7;
    short position = 0;
    char YN;
    showHelloMessage();
    printf("Введите длину\n");
    I = (short) validation();
    printf("Введите ширину\n");
    J = (short) validation();
    showMenu(position, I, J);
    while (!exitFlag) {
        symbol = (short) getch();
        if (symbol == 224) symbol = (short) getch();
        int area[I][J];
        switch (symbol) {
            case 72:
                if (0 != position - 1)
                    position--;
                else position = maxPosition;
                break;
            case 80:
                if (position < maxPosition) position++;
                else
                    position = minPosition;
                break;
            case 27:
                printf("Вы уверены что хотите выйти?(Y/N)\n");
                scanf("%s", &YN);
                if (YN == 'Y') exitFlag = true;
                break;
            case 49:
                position = 1;
                break;
            case 50:
                position = 2;
                break;
            case 51:
                position = 3;
                break;
            case 52:
                position = 4;
                break;
            case 53:
                position = 5;
                break;
            case 54:
                position = 6;
                break;
            case 55:
                position = 7;
                break;
            default:;
        }
        showMenu(position, I, J);
        switch (position) {
            case 1:
                printf("Введите длину\n");
                I = (short) validation();
                showMenu(position, I, J);
                printf("Длина успешно изменена!\n");
                break;
            case 2:
                printf("Введите ширину\n");
                J = (short) validation();
                showMenu(position, I, J);
                printf("Ширина успешно изменена!\n");
                break;
            case 3:
                generateSpiral(I, J, area, 0);
                break;
            case 4:
                generateSpiral(I, J, area, 1);
                break;
            case 5:
                generateSpiral(I, J, area, 2);
                break;
            case 6:
                generateSpiral(I, J, area, 3);
                break;
            case 7:
                printf("Вы уверены что хотите выйти?(Y/N)\n");
                scanf("%s", &YN);
                if (YN == 'Y') exitFlag = true;
                break;
            default:;
        }
    }
    return 0;
}
