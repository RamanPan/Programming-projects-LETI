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
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
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
        int gameData[3] = {(n - 2) * (m - 2), 0, 0}, positionCursor[2] = {1, 1}, positionX[192], positionO[192];
        int symbol;
        char YN;
        bool winFirst = false, winSecond = false, draw = false, XorO = false;
        if (rand() % 2 == 0) XorO = true;
        else XorO = false;
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
                    printf("Вы уверены что хотите выйти?(Y/N)\n");
                    scanf("%s", &YN);
                    if (YN == 'Y') return 0;
                    break;
                case 13:
                    setXorO(m, gameArea, gameData, positionCursor, positionX, positionO, XorO);
                    if (!XorO) winFirst = checkWin(m, gameArea, pointsForWinX, false);
                    else winSecond = checkWin(m, gameArea, pointsForWinX, true);
                    XorO = !XorO;
                    break;
                default:;
            }
            showMenu(n, m, gameData, gameArea, pointsForWinX, pointsForWinO, XorO);
            if (winFirst) {
                printf("Крестики победили!\n");
                printf("Поздравляем с победой!\n");
            } else if (winSecond) {
                printf("Нолики победили!\n");
                printf("Поздравляем с победой!\n");
            } else if (gameData[0] == 0) {
                draw = true;
                printf("Ничья!\n");
            }
            if (winFirst || winSecond || draw) {
                printf("Хотите сыграть ещё раз?(Y/N)\n");
                scanf("%s", &YN);
                startAgain = true;
                if (YN == 'Y') {}
                else exitFlag = true;
            }
        }
    }
    printf("Не забывайте иногда играть снова!");
    return 0;
}