#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "functionality.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    bool exitFlag = false;
    while (!exitFlag) {
        srand(time(NULL));
        showHelloMessage();
        bool startAgain = false;
        printf("Введите размерность поля\n");
        const long n = validationGameArea() + 2;
        int gameArea[n][n], positionSnakes[4], endTailFirstSnake[2], endTailSecondSnake[2], allTailFirstSnake[20], allTailSecondSnake[20];
        //0 - кол-во свободных клеток, 1 - кол-во еды, 2 - длина первой змейки, 3 - длина второй змейки
        int gameData[4] = {(n - 2) * (n - 2) - 2, 0, 1, 1};
        int pointsForWin[8] = {4, 5, 6, 7, 8, 9, 10, 11};
        int symbol;
        short orientationFirstSnake, orientationSecondSnake;
        char YN;
        bool winFirst = false, winSecond = false;
        fillingArea(n, gameArea);
        generatePositionSnakes(n, gameArea, positionSnakes,gameData);
        generateFood(n, gameData, gameArea);
        showMenu(n, gameData, gameArea);
        while (!startAgain) {
            symbol = getch();
            if (symbol == 224) symbol = getch();
            switch (symbol) {
                //верхняя стрелочка
                case 72:
                    if(gameData[2] > 1 && orientationFirstSnake == 1) break;
                    orientationFirstSnake = 0;
                    winSecond = snakeMotion(n, gameArea, gameData, positionSnakes, endTailFirstSnake,
                                            endTailSecondSnake, allTailFirstSnake, allTailSecondSnake, orientationFirstSnake, false);
                    break;
                    //нижняя стрелочка
                case 80:
                    if(gameData[2] > 1 && orientationFirstSnake == 0) break;
                    orientationFirstSnake = 1;
                    winSecond = snakeMotion(n, gameArea, gameData, positionSnakes, endTailFirstSnake,
                                            endTailSecondSnake, allTailFirstSnake, allTailSecondSnake, orientationFirstSnake, false);
                    break;
                    //левая стрелочка
                case 75:
                    if(gameData[2] > 1 && orientationFirstSnake == 3) break;
                    orientationFirstSnake = 2;
                    winSecond = snakeMotion(n, gameArea, gameData, positionSnakes, endTailFirstSnake,
                                            endTailSecondSnake, allTailFirstSnake, allTailSecondSnake, orientationFirstSnake, false);
                    break;
                    // правая стрелочка
                case 77:
                    if(gameData[2] > 1 && orientationFirstSnake == 2) break;
                    orientationFirstSnake = 3;
                    winSecond = snakeMotion(n, gameArea, gameData, positionSnakes, endTailFirstSnake,
                                            endTailSecondSnake, allTailFirstSnake, allTailSecondSnake, orientationFirstSnake, false);
                    break;
                    //W
                case 119:
                    if(gameData[3] > 1 && orientationSecondSnake == 1) break;
                    orientationSecondSnake = 0;
                    winFirst = snakeMotion(n, gameArea, gameData, positionSnakes, endTailFirstSnake, endTailSecondSnake,
                                           allTailFirstSnake, allTailSecondSnake, orientationSecondSnake, true);
                    break;
                    //S
                case 115:
                    if(gameData[3] > 1 && orientationSecondSnake == 0) break;
                    orientationSecondSnake = 1;
                    winFirst = snakeMotion(n, gameArea, gameData, positionSnakes, endTailFirstSnake, endTailSecondSnake,
                                           allTailFirstSnake, allTailSecondSnake, orientationSecondSnake, true);
                    break;
                    //A
                case 97:
                    if(gameData[3] > 1 && orientationSecondSnake == 3) break;
                    orientationSecondSnake = 2;
                    winFirst = snakeMotion(n, gameArea, gameData, positionSnakes, endTailFirstSnake, endTailSecondSnake,
                                           allTailFirstSnake, allTailSecondSnake, orientationSecondSnake, true);
                    break;
                    //D
                case 100:
                    if(gameData[3] > 1 && orientationSecondSnake == 2) break;
                    orientationSecondSnake = 3;
                    winFirst = snakeMotion(n, gameArea, gameData, positionSnakes, endTailFirstSnake, endTailSecondSnake,
                                           allTailFirstSnake, allTailSecondSnake, orientationSecondSnake, true);
                    break;
                case 27:
                    printf("Вы уверены что хотите выйти?(Y/N)\n");
                    scanf("%s", &YN);
                    if (YN == 'Y') return 0;
                    break;
                default:;
            }
            showMenu(n, gameData, gameArea);
            if (winFirst || gameData[2] == pointsForWin[n - 5]) {
                winFirst = true;
                printf("Первая змейка победила!\n");
                printf("Поздравляем с победой!\n");
            }
            if (winSecond || gameData[3] == pointsForWin[n - 5]) {
                winSecond = true;
                printf("Вторая змейка победила!\n");
                printf("Поздравляем с победой!\n");
            }
            if (winFirst || winSecond) {
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