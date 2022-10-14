#include <stdio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include "functionality.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    bool exitFlag = false;
    while (!exitFlag) {
        srand(time(NULL));
        showHelloMessage();
        bool startAgain = false;
        printf("Введите размерность поля\n");
        const short n = validationGameArea() + 2;
        const short m = validationGameArea() + 2;
        printf("Введите условие победы для игрока, играющего крестиками\n");
        const short pointsForWinX = validationGameArea();
        printf("Введите условие победы для игрока, играющего ноликами\n");
        const short pointsForWinO = validationGameArea();
        int gameArea[n][m];
        //0 - кол-во свободных клеток, 1 - кол-во еды, 2 - длина первой змейки, 3 - длина второй змейки
        int gameData[4] = {(n - 2) * (n - 2) - 2, 0, 1, 1};
        int symbol;
        char YN;
        bool winFirst = false, winSecond = false, draw = false;
        fillingArea(n, gameArea);
        cleanArea(n, gameArea);
//        showMenu(n, gameData, gameArea);
        while (!startAgain) {
            symbol = getch();
            if (symbol == 224) symbol = getch();
            switch (symbol) {
                //верхняя стрелочка
                case 72:
                    break;
                    //нижняя стрелочка
                case 80:
                    break;
                    //левая стрелочка
                case 75:
                    break;
                    // правая стрелочка
                case 77:
                    break;
                    //W
                case 119:
                    break;
                    //S
                case 115:
                    break;
                    //A
                case 97:
                    break;
                    //D
                case 100:
                    break;
                case 27:
                    printf("Вы уверены что хотите выйти?(Y/N)\n");
                    scanf("%s", &YN);
                    if (YN == 'Y') return 0;
                    break;
                default:;
            }
//            showMenu(n, gameData, gameArea);
//            if (winFirst || gameData[2] == pointsForWin[n - 5]) {
//                winFirst = true;
//                printf("Первая змейка победила!\n");
//                printf("Поздравляем с победой!\n");
//            }
//            if (winSecond || gameData[3] == pointsForWin[n - 5]) {
//                winSecond = true;
//                printf("Вторая змейка победила!\n");
//                printf("Поздравляем с победой!\n");
//            }
//            if (winFirst || winSecond) {
//                printf("Хотите сыграть ещё раз?(Y/N)\n");
//                scanf("%s", &YN);
//                startAgain = true;
//                if (YN == 'Y') {}
//                else exitFlag = true;
//            }
        }
    }
    printf("Не забывайте иногда играть снова!");
    return 0;
}
