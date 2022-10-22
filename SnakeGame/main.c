#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "functionality.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    bool exitFlag = false;
    while (!exitFlag) {
        srand(time(NULL));
        showHelloMessage();
        bool startAgain = false, randomOrOwnWalls = false;
        printf("Введите высоту поля\n");
        const long n = validationGameArea() + 2;
        printf("Введите ширину поля\n");
        const long m = validationGameArea() + 2;
        int gameArea[n][m], positionSnakes[4], positionCursor[2] = {1, 1}, endTailFirstSnake[2],
                pointFood[8] = {0, 0, 0, 0, 0, 0, 0, 0},
                endTailSecondSnake[2], allTailFirstSnake[50], allTailSecondSnake[50];
        //0 - кол-во свободных клеток, 1 - кол-во еды, 2 - длина первой змейки, 3 - длина второй змейки
        int gameData[5] = {(n - 2) * (m - 2), 0, 1, 1, 2 * ((n - 2) + m - 2) + 4};
//        int pointsForWin[8] = {4, 6, 8, 10, 12, 14, 16, 20};
        int symbol;
        short orientationFirstSnake, orientationSecondSnake;
        char YN;
        bool winFirst = false, winSecond = false, draw = false;
        printf("Хотите поставить стенки вручную или пусть генерируются?(Y - сами, любой другой символ - рандоманя генерация\n");
        YN = getSymbol();
        if (YN == 'Y') randomOrOwnWalls = true;
        fillingArea(n, m, gameArea);
        cleanArea(n, m, gameArea, randomOrOwnWalls);
        if (randomOrOwnWalls) createWalls(n, m, gameArea, gameData, positionCursor);
        gameData[0] -= 2;
        generatePositionSnakes(n, m, gameArea, positionSnakes, gameData, randomOrOwnWalls);
        generateFood(n, m, gameData, gameArea, pointFood);
        showMenu(n, m, gameData, gameArea,positionSnakes);
        while (!startAgain) {
            if (gameData[0] == 0 && gameData[1] == 0) {
                if (gameData[2] == gameData[3]) {
                    draw = true;
                    printf("Ничья!\n");
                } else if (gameData[2] > gameData[3]) winFirst = true;
                else winSecond = true;
            }
            if (winFirst) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
                printf("Первая змейка победила!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                printf("Поздравляем с победой!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            }
            if (winSecond) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                printf("Вторая змейка победила!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                printf("Поздравляем с победой!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            }

            if (winFirst || winSecond || draw) {
                printf("Хотите сыграть ещё раз?(Y - да, любой другой символ - нет)\n");
                YN = getSymbol();
                startAgain = true;
                if (YN == 'Y') {}
                else exitFlag = true;
            }
            if (!startAgain) {
                symbol = getch();
                if (symbol == 224) symbol = getch();
                switch (symbol) {
                    //верхняя стрелочка
                    case 72:
                        if (gameData[2] > 1 && orientationFirstSnake == 1) break;
                        orientationFirstSnake = 0;
                        winSecond = snakeMotion(n, m, gameArea, gameData, positionSnakes, endTailFirstSnake,
                                                endTailSecondSnake, allTailFirstSnake, allTailSecondSnake, pointFood,
                                                orientationFirstSnake, false);
                        break;
                        //нижняя стрелочка
                    case 80:
                        if (gameData[2] > 1 && orientationFirstSnake == 0) break;
                        orientationFirstSnake = 1;
                        winSecond = snakeMotion(n, m, gameArea, gameData, positionSnakes, endTailFirstSnake,
                                                endTailSecondSnake, allTailFirstSnake, allTailSecondSnake, pointFood,
                                                orientationFirstSnake, false);
                        break;
                        //левая стрелочка
                    case 75:
                        if (gameData[2] > 1 && orientationFirstSnake == 3) break;
                        orientationFirstSnake = 2;
                        winSecond = snakeMotion(n, m, gameArea, gameData, positionSnakes, endTailFirstSnake,
                                                endTailSecondSnake, allTailFirstSnake, allTailSecondSnake, pointFood,
                                                orientationFirstSnake, false);
                        break;
                        // правая стрелочка
                    case 77:
                        if (gameData[2] > 1 && orientationFirstSnake == 2) break;
                        orientationFirstSnake = 3;
                        winSecond = snakeMotion(n, m, gameArea, gameData, positionSnakes, endTailFirstSnake,
                                                endTailSecondSnake, allTailFirstSnake, allTailSecondSnake, pointFood,
                                                orientationFirstSnake, false);
                        break;
                        //W
                    case 119:
                        if (gameData[3] > 1 && orientationSecondSnake == 1) break;
                        orientationSecondSnake = 0;
                        winFirst = snakeMotion(n, m, gameArea, gameData, positionSnakes, endTailFirstSnake,
                                               endTailSecondSnake,
                                               allTailFirstSnake, allTailSecondSnake, pointFood, orientationSecondSnake,
                                               true);
                        break;
                        //S
                    case 115:
                        if (gameData[3] > 1 && orientationSecondSnake == 0) break;
                        orientationSecondSnake = 1;
                        winFirst = snakeMotion(n, m, gameArea, gameData, positionSnakes, endTailFirstSnake,
                                               endTailSecondSnake,
                                               allTailFirstSnake, allTailSecondSnake, pointFood, orientationSecondSnake,
                                               true);
                        break;
                        //A
                    case 97:
                        if (gameData[3] > 1 && orientationSecondSnake == 3) break;
                        orientationSecondSnake = 2;
                        winFirst = snakeMotion(n, m, gameArea, gameData, positionSnakes, endTailFirstSnake,
                                               endTailSecondSnake,
                                               allTailFirstSnake, allTailSecondSnake, pointFood, orientationSecondSnake,
                                               true);
                        break;
                        //D
                    case 100:
                        if (gameData[3] > 1 && orientationSecondSnake == 2) break;
                        orientationSecondSnake = 3;
                        winFirst = snakeMotion(n, m, gameArea, gameData, positionSnakes, endTailFirstSnake,
                                               endTailSecondSnake,
                                               allTailFirstSnake, allTailSecondSnake, pointFood, orientationSecondSnake,
                                               true);
                        break;
                    case 27:
                        printf("Вы уверены что хотите выйти?(Y - да, любой другой символ - нет)\n");
                        YN = getSymbol();
                        if (YN == 'Y') return 0;
                        break;
                    default:;
                }
                showMenu(n, m, gameData, gameArea,positionSnakes);
            }
        }
    }
    printf("Не забывайте иногда играть снова!");
    return 0;
}
