#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>
#include "functionality.h"

#define MAX(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    bool exitFlag = false;
    while (!exitFlag) {
        srand(time(NULL));
        showHelloMessage();
        bool startAgain = false;
        printf("Введите высоту поля(N)\n");
        const short n = (short) (validationGameArea() + 2);
        printf("Введите ширину поля(M)\n");
        const short m = (short) (validationGameArea() + 2);
        printf("Введите условие победы для игрока, играющего крестиками\n");
        const short pointsForWinX = (short) validationWithArgument(MAX(n - 2, m - 2));
        printf("Введите условие победы для игрока, играющего ноликами\n");
        const short pointsForWinO = (short) validationWithArgument(MAX(n - 2, m - 2));
        int gameArea[n][m];
        //0 - кол-во свободных клеток, 1 - кол-во крестиков, 2 - кол-во ноликов
        int gameData[3] = {(n - 2) * (m - 2), 0, 0}, positionCursor[2] = {1, 1};
        int symbol;
        char YN;
        bool winX = false, win0 = false, draw = false, XorO = false;
        if (rand() % 2 == 0) XorO = true;
        else XorO = false;
        bool checkChanges;
        fillingArea(n, m, gameArea);
        cleanArea(n, m, gameArea);
        showMenu(n, m, gameData, gameArea, pointsForWinX, pointsForWinO, XorO);
        while (!startAgain) {
            symbol = getch();
            if (symbol == 224) symbol = getch();
            switch (symbol) {
                //верхняя стрелочка
                case 72:
                    moveCursor(m, gameArea, positionCursor, 0);
                    break;
                    //нижняя стрелочка
                case 80:
                    moveCursor(m, gameArea, positionCursor, 1);
                    break;
                    //левая стрелочка
                case 75:
                    moveCursor(m, gameArea, positionCursor, 2);
                    break;
                    // правая стрелочка
                case 77:
                    moveCursor(m, gameArea, positionCursor, 3);
                    break;
                    //W
                case 119:
                    moveCursor(m, gameArea, positionCursor, 0);
                    break;
                    //S
                case 115:
                    moveCursor(m, gameArea, positionCursor, 1);
                    break;
                    //A
                case 97:
                    moveCursor(m, gameArea, positionCursor, 2);
                    break;
                    //D
                case 100:
                    moveCursor(m, gameArea, positionCursor, 3);
                    break;
                case 27:
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("Вы уверены что хотите выйти?(Y/N)\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                    YN = getch();
                    if (YN == 'Y') return 0;
                    break;
                case 13:
                    checkChanges = setXorO(m, gameArea, gameData, positionCursor, XorO);
                    if (!XorO) winX = checkWin(m, gameArea, positionCursor, pointsForWinX, XorO);
                    else win0 = checkWin(m, gameArea, positionCursor, pointsForWinO, XorO);
                    if (checkChanges != XorO) XorO = !XorO;
                    break;
                default:;
            }
            showMenu(n, m, gameData, gameArea, pointsForWinX, pointsForWinO, XorO);
            if (winX) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                printf("Крестики победили!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                printf("Поздравляем с победой!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            } else if (win0) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                printf("Нолики победили!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                printf("Поздравляем с победой!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            } else if (gameData[0] == 0) {
                draw = true;
                printf("Ничья!\n");
            }
            if (winX || win0 || draw) {
                printf("Хотите сыграть ещё раз?(Y/N)\n");
                YN = getch();
                startAgain = true;
                if (YN == 'Y') {}
                else exitFlag = true;
            }
        }
    }
    printf("Не забывайте иногда играть снова!");
    return 0;
}
