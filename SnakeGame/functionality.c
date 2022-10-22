#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "functionality.h"
#include "constants.h"


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

void showMenu(int n, int m, int gameData[], int area[][m], int positionSnakes[]) {
    system("cls");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            printSymbol((short) area[i][j]);
            if (j == m - 1) printf("\n");
        }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    printf("Счёт: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
    printf("%d", gameData[2]);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    printf(":");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    printf("%d\n", gameData[3]);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    printf("Кол-во свободных клеток: %d\n", gameData[0]);
    printf("Кол-во еды: %d\n", gameData[1]);
    printf("Кол-во стенок: %d\n", gameData[4]);
}

void fillingArea(int n, int m, int area[][m]) {
    for (int i = 0; i < n; ++i) {
        area[i][0] = WALL;
        area[i][m - 1] = WALL;
    }
    for (int j = 0; j < m; ++j) {
        area[0][j] = WALL;
        area[n - 1][j] = WALL;
    }
}

bool
snakeMotion(int n, int m, int area[][m], int gameData[], int positionSnakes[], int endTailFirstSnake[],
            int endTailSecondSnake[], int allTailFirstSnake[], int allTailSecondSnake[], int pointFood[],
            short orientation, bool whichSnake) {
    bool isItFood = false;
    int xEndTail, yEndTail;
    if (!whichSnake) {
        switch (orientation) {
            case 3:
                positionSnakes[1] = positionSnakes[1] + 1;
                if (checkLose(n, m, area, positionSnakes[1], positionSnakes[0])) return true;
                if (area[positionSnakes[0]][positionSnakes[1]] == FOOD) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[0], positionSnakes[1]);
                }
                area[positionSnakes[0]][positionSnakes[1]] = HEAD_ONE;
                if (area[positionSnakes[0]][positionSnakes[1] - 1] == HEAD_ONE)
                    area[positionSnakes[0]][positionSnakes[1] - 1] = HOLLOW;
                if (isItFood) {
                    gameData[1]--;
                    if (gameData[2] == 1) {
                        yEndTail = positionSnakes[0];
                        xEndTail = positionSnakes[1] - 1;
                        endTailFirstSnake[0] = yEndTail;
                        endTailFirstSnake[1] = xEndTail;
                    } else {
                        yEndTail = endTailFirstSnake[0];
                        xEndTail = endTailFirstSnake[1] - 1;
                        if (checkLose(n, m, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, m, area, endTailFirstSnake, endTailSecondSnake, orientation,
                                                         whichSnake);
                            yEndTail = endTailFirstSnake[0];
                            xEndTail = endTailFirstSnake[1];
                        } else {
                            endTailFirstSnake[0] = yEndTail;
                            endTailFirstSnake[1] = xEndTail;
                        }
                    }
                    determineThePosition(gameData, endTailFirstSnake, endTailSecondSnake, allTailFirstSnake,
                                         allTailSecondSnake, whichSnake);
                    area[yEndTail][xEndTail] = TAIL_FIRST_SNAKE;
                    gameData[2] = gameData[2] + 1;
                }
                if (gameData[2] >= 3 || gameData[2] == 2 && !isItFood)
                    tailMotion(n, m, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake, pointFood,
                               orientation, whichSnake);
                break;
            case 2:
                positionSnakes[1] = positionSnakes[1] - 1;
                if (checkLose(n, m, area, positionSnakes[1], positionSnakes[0])) return true;
                if (area[positionSnakes[0]][positionSnakes[1]] == FOOD) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[0], positionSnakes[1]);
                }
                area[positionSnakes[0]][positionSnakes[1]] = HEAD_ONE;
                if (area[positionSnakes[0]][positionSnakes[1] + 1] == HEAD_ONE)
                    area[positionSnakes[0]][positionSnakes[1] + 1] = HOLLOW;
                if (isItFood) {
                    gameData[1]--;
                    if (gameData[2] == 1) {
                        yEndTail = positionSnakes[0];
                        xEndTail = positionSnakes[1] + 1;
                        endTailFirstSnake[0] = yEndTail;
                        endTailFirstSnake[1] = xEndTail;
                    } else {
                        yEndTail = endTailFirstSnake[0];
                        xEndTail = endTailFirstSnake[1] + 1;
                        if (checkLose(n, m, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, m, area, endTailFirstSnake, endTailSecondSnake, orientation,
                                                         whichSnake);
                            yEndTail = endTailFirstSnake[0];
                            xEndTail = endTailFirstSnake[1];
                        } else {
                            endTailFirstSnake[0] = yEndTail;
                            endTailFirstSnake[1] = xEndTail;
                        }
                    }
                    determineThePosition(gameData, endTailFirstSnake, endTailSecondSnake, allTailFirstSnake,
                                         allTailSecondSnake, whichSnake);
                    area[yEndTail][xEndTail] = TAIL_FIRST_SNAKE;
                    gameData[2] = gameData[2] + 1;
                }
                if (gameData[2] >= 3 || gameData[2] == 2 && !isItFood)
                    tailMotion(n, m, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake,
                               pointFood, orientation, whichSnake);
                break;
            case 0:
                positionSnakes[0] = positionSnakes[0] - 1;
                if (checkLose(n, m, area, positionSnakes[1], positionSnakes[0])) return true;
                if (area[positionSnakes[0]][positionSnakes[1]] == FOOD) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[0], positionSnakes[1]);
                }
                area[positionSnakes[0]][positionSnakes[1]] = HEAD_ONE;
                if (area[positionSnakes[0] + 1][positionSnakes[1]] == HEAD_ONE)
                    area[positionSnakes[0] + 1][positionSnakes[1]] = HOLLOW;
                if (isItFood) {
                    gameData[1]--;
                    if (gameData[2] == 1) {
                        yEndTail = positionSnakes[0] + 1;
                        xEndTail = positionSnakes[1];
                        endTailFirstSnake[0] = yEndTail;
                        endTailFirstSnake[1] = xEndTail;
                    } else {
                        yEndTail = endTailFirstSnake[0] + 1;
                        xEndTail = endTailFirstSnake[1];
                        if (checkLose(n, m, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, m, area, endTailFirstSnake, endTailSecondSnake, orientation,
                                                         whichSnake);
                            yEndTail = endTailFirstSnake[0];
                            xEndTail = endTailFirstSnake[1];
                        } else {
                            endTailFirstSnake[0] = yEndTail;
                            endTailFirstSnake[1] = xEndTail;
                        }
                    }
                    determineThePosition(gameData, endTailFirstSnake, endTailSecondSnake, allTailFirstSnake,
                                         allTailSecondSnake, whichSnake);
                    area[yEndTail][xEndTail] = TAIL_FIRST_SNAKE;
                    gameData[2] = gameData[2] + 1;
                }
                if (gameData[2] >= 3 || gameData[2] == 2 && !isItFood)
                    tailMotion(n, m, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake, pointFood,
                               orientation, whichSnake);
                break;
            case 1:
                positionSnakes[0] = positionSnakes[0] + 1;
                if (checkLose(n, m, area, positionSnakes[1], positionSnakes[0])) return true;
                if (area[positionSnakes[0]][positionSnakes[1]] == FOOD) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[0], positionSnakes[1]);
                }
                area[positionSnakes[0]][positionSnakes[1]] = HEAD_ONE;
                if (area[positionSnakes[0] - 1][positionSnakes[1]] == HEAD_ONE)
                    area[positionSnakes[0] - 1][positionSnakes[1]] = HOLLOW;
                if (isItFood) {
                    gameData[1]--;
                    if (gameData[2] == 1) {
                        yEndTail = positionSnakes[0] - 1;
                        xEndTail = positionSnakes[1];
                        endTailFirstSnake[0] = yEndTail;
                        endTailFirstSnake[1] = xEndTail;
                    } else {
                        yEndTail = endTailFirstSnake[0] - 1;
                        xEndTail = endTailFirstSnake[1];
                        if (checkLose(n, m, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, m, area, endTailFirstSnake, endTailSecondSnake, orientation,
                                                         whichSnake);
                            yEndTail = endTailFirstSnake[0];
                            xEndTail = endTailFirstSnake[1];
                        } else {
                            endTailFirstSnake[0] = yEndTail;
                            endTailFirstSnake[1] = xEndTail;
                        }
                    }
                    determineThePosition(gameData, endTailFirstSnake, endTailSecondSnake, allTailFirstSnake,
                                         allTailSecondSnake, whichSnake);
                    area[yEndTail][xEndTail] = TAIL_FIRST_SNAKE;
                    gameData[2] = gameData[2] + 1;
                }
                if (gameData[2] >= 3 || gameData[2] == 2 && !isItFood)
                    tailMotion(n, m, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake, pointFood,
                               orientation, whichSnake);
                break;
            default:;
        }
    } else {
        switch (orientation) {
            case 3:
                positionSnakes[3] = positionSnakes[3] + 1;
                if (checkLose(n, m, area, positionSnakes[3], positionSnakes[2])) return true;
                if (area[positionSnakes[2]][positionSnakes[3]] == FOOD) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[2], positionSnakes[3]);
                }
                area[positionSnakes[2]][positionSnakes[3]] = HEAD_TWO;
                if (area[positionSnakes[2]][positionSnakes[3] - 1] == HEAD_TWO)
                    area[positionSnakes[2]][positionSnakes[3] - 1] = HOLLOW;
                if (isItFood) {
                    gameData[1]--;
                    if (gameData[3] == 1) {
                        yEndTail = positionSnakes[2];
                        xEndTail = positionSnakes[3] - 1;
                        endTailSecondSnake[0] = yEndTail;
                        endTailSecondSnake[1] = xEndTail;
                    } else {
                        yEndTail = endTailSecondSnake[0];
                        xEndTail = endTailSecondSnake[1] - 1;
                        if (checkLose(n, m, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, m, area, endTailFirstSnake, endTailSecondSnake, orientation,
                                                         whichSnake);
                            yEndTail = endTailSecondSnake[0];
                            xEndTail = endTailSecondSnake[1];
                        } else {
                            endTailSecondSnake[0] = yEndTail;
                            endTailSecondSnake[1] = xEndTail;
                        }
                    }
                    determineThePosition(gameData, endTailFirstSnake, endTailSecondSnake, allTailFirstSnake,
                                         allTailSecondSnake, whichSnake);
                    area[yEndTail][xEndTail] = TAIL_SECOND_SNAKE;
                    gameData[3] = gameData[3] + 1;
                }
                if (gameData[3] >= 3 || gameData[3] == 2 && !isItFood)
                    tailMotion(n, m, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake, pointFood,
                               orientation, whichSnake);
                break;
            case 2:
                positionSnakes[3] = positionSnakes[3] - 1;
                if (checkLose(n, m, area, positionSnakes[3], positionSnakes[2])) return true;
                if (area[positionSnakes[2]][positionSnakes[3]] == FOOD) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[2], positionSnakes[3]);
                }
                area[positionSnakes[2]][positionSnakes[3]] = HEAD_TWO;
                if (area[positionSnakes[2]][positionSnakes[3] + 1] == HEAD_TWO)
                    area[positionSnakes[2]][positionSnakes[3] + 1] = HOLLOW;
                if (isItFood) {
                    gameData[1]--;
                    if (gameData[3] == 1) {
                        yEndTail = positionSnakes[2];
                        xEndTail = positionSnakes[3] + 1;
                        endTailSecondSnake[0] = yEndTail;
                        endTailSecondSnake[1] = xEndTail;
                    } else {
                        yEndTail = endTailSecondSnake[0];
                        xEndTail = endTailSecondSnake[1] + 1;
                        if (checkLose(n, m, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, m, area, endTailFirstSnake, endTailSecondSnake, orientation,
                                                         whichSnake);
                            yEndTail = endTailSecondSnake[0];
                            xEndTail = endTailSecondSnake[1];
                        } else {
                            endTailSecondSnake[0] = yEndTail;
                            endTailSecondSnake[1] = xEndTail;
                        }
                    }
                    determineThePosition(gameData, endTailFirstSnake, endTailSecondSnake, allTailFirstSnake,
                                         allTailSecondSnake, whichSnake);
                    area[yEndTail][xEndTail] = TAIL_SECOND_SNAKE;
                    gameData[3] = gameData[3] + 1;
                }
                if (gameData[3] >= 3 || gameData[3] == 2 && !isItFood)
                    tailMotion(n, m, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake, pointFood,
                               orientation, whichSnake);
                break;
            case 0:
                positionSnakes[2] = positionSnakes[2] - 1;
                if (checkLose(n, m, area, positionSnakes[3], positionSnakes[2])) return true;
                if (area[positionSnakes[2]][positionSnakes[3]] == FOOD) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[2], positionSnakes[3]);
                }
                area[positionSnakes[2]][positionSnakes[3]] = HEAD_TWO;
                if (area[positionSnakes[2] + 1][positionSnakes[3]] == HEAD_TWO)
                    area[positionSnakes[2] + 1][positionSnakes[3]] = HOLLOW;
                if (isItFood) {
                    gameData[1]--;
                    if (gameData[3] == 1) {
                        yEndTail = positionSnakes[2] + 1;
                        xEndTail = positionSnakes[3];
                        endTailSecondSnake[0] = yEndTail;
                        endTailSecondSnake[1] = xEndTail;
                    } else {
                        yEndTail = endTailSecondSnake[0] + 1;
                        xEndTail = endTailSecondSnake[1];
                        if (checkLose(n, m, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, m, area, endTailFirstSnake, endTailSecondSnake, orientation,
                                                         whichSnake);
                            yEndTail = endTailSecondSnake[0];
                            xEndTail = endTailSecondSnake[1];
                        } else {
                            endTailSecondSnake[0] = yEndTail;
                            endTailSecondSnake[1] = xEndTail;
                        }
                    }
                    determineThePosition(gameData, endTailFirstSnake, endTailSecondSnake, allTailFirstSnake,
                                         allTailSecondSnake, whichSnake);
                    area[yEndTail][xEndTail] = TAIL_SECOND_SNAKE;
                    gameData[3] = gameData[3] + 1;
                }
                if (gameData[3] >= 3 || gameData[3] == 2 && !isItFood)
                    tailMotion(n, m, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake, pointFood,
                               orientation, whichSnake);
                break;
            case 1:
                positionSnakes[2] = positionSnakes[2] + 1;
                if (checkLose(n, m, area, positionSnakes[3], positionSnakes[2])) return true;
                if (area[positionSnakes[2]][positionSnakes[3]] == FOOD) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[2], positionSnakes[3]);
                }
                area[positionSnakes[2]][positionSnakes[3]] = HEAD_TWO;
                if (area[positionSnakes[2] - 1][positionSnakes[3]] == HEAD_TWO)
                    area[positionSnakes[2] - 1][positionSnakes[3]] = HOLLOW;
                if (isItFood) {
                    gameData[1]--;
                    if (gameData[3] == 1) {
                        yEndTail = positionSnakes[2] - 1;
                        xEndTail = positionSnakes[3];
                        endTailSecondSnake[0] = yEndTail;
                        endTailSecondSnake[1] = xEndTail;
                    } else {
                        yEndTail = endTailSecondSnake[0] - 1;
                        xEndTail = endTailSecondSnake[1];
                        if (checkLose(n, m, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, m, area, endTailFirstSnake, endTailSecondSnake, orientation,
                                                         whichSnake);
                            yEndTail = endTailSecondSnake[0];
                            xEndTail = endTailSecondSnake[1];
                        } else {
                            endTailSecondSnake[0] = yEndTail;
                            endTailSecondSnake[1] = xEndTail;
                        }
                    }
                    determineThePosition(gameData, endTailFirstSnake, endTailSecondSnake, allTailFirstSnake,
                                         allTailSecondSnake, whichSnake);
                    area[yEndTail][xEndTail] = TAIL_SECOND_SNAKE;
                    gameData[3] = gameData[3] + 1;
                }
                if (gameData[3] >= 3 || gameData[3] == 2 && !isItFood)
                    tailMotion(n, m, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake, pointFood,
                               orientation, whichSnake);
                break;
            default:;
        }
    }
    if (isItFood) generateFood(n, m, gameData, area, pointFood);
    checkPointFood(n, m, area, gameData, pointFood);
    return false;
}

void tailMotion(int n, int m, int area[][m], int gameData[], const int positionSnakes[], int tailFirstSnake[],
                int tailSecondSnake[], int pointFood[],
                short orientation, bool whichSnake) {
    int actualOrientation;
    int tempI, tempJ, tempI1, tempJ1;
    if (!whichSnake) {
        int N = (gameData[2] - 1) * 2;
        actualOrientation = orientation;
        switch (actualOrientation) {
            case 0:
                tempI = positionSnakes[0] + 1;
                tempJ = positionSnakes[1];
                area[tempI][tempJ] = TAIL_FIRST_SNAKE;
                if (!checkForMove(n, m, area, tailFirstSnake[N - 1], tailFirstSnake[N - 2]))
                    area[tailFirstSnake[N - 2]][tailFirstSnake[N - 1]] = 0;
                for (int i = 0; i < N; i = i + 2) {
                    if (i != N - 1) {
                        tempI1 = tailFirstSnake[i];
                        tempJ1 = tailFirstSnake[i + 1];
                        tailFirstSnake[i] = tempI;
                        tailFirstSnake[i + 1] = tempJ;
                        tempI = tempI1;
                        tempJ = tempJ1;
                    }
                }
                checkTail(n, m, N, area, tailFirstSnake, whichSnake);
                break;
            case 1:
                tempI = positionSnakes[0] - 1;
                tempJ = positionSnakes[1];
                area[tempI][tempJ] = TAIL_FIRST_SNAKE;
                if (!checkForMove(n, m, area, tailFirstSnake[N - 1], tailFirstSnake[N - 2]))
                    area[tailFirstSnake[N - 2]][tailFirstSnake[N - 1]] = 0;
                for (int i = 0; i < N; i = i + 2) {
                    if (i != N - 1) {
                        tempI1 = tailFirstSnake[i];
                        tempJ1 = tailFirstSnake[i + 1];
                        tailFirstSnake[i] = tempI;
                        tailFirstSnake[i + 1] = tempJ;
                        tempI = tempI1;
                        tempJ = tempJ1;
                    }
                }
                checkTail(n, m, N, area, tailFirstSnake, whichSnake);
                break;
            case 2:
                tempI = positionSnakes[0];
                tempJ = positionSnakes[1] + 1;
                area[tempI][tempJ] = TAIL_FIRST_SNAKE;
                if (!checkForMove(n, m, area, tailFirstSnake[N - 1], tailFirstSnake[N - 2]))
                    area[tailFirstSnake[N - 2]][tailFirstSnake[N - 1]] = 0;
                for (int i = 0; i < N; i = i + 2) {
                    if (i != N - 1) {
                        tempI1 = tailFirstSnake[i];
                        tempJ1 = tailFirstSnake[i + 1];
                        tailFirstSnake[i] = tempI;
                        tailFirstSnake[i + 1] = tempJ;
                        tempI = tempI1;
                        tempJ = tempJ1;
                    }
                }
                checkTail(n, m, N, area, tailFirstSnake, whichSnake);
                break;
            case 3:
                tempI = positionSnakes[0];
                tempJ = positionSnakes[1] - 1;
                area[tempI][tempJ] = TAIL_FIRST_SNAKE;
                if (!checkForMove(n, m, area, tailFirstSnake[N - 1], tailFirstSnake[N - 2]))
                    area[tailFirstSnake[N - 2]][tailFirstSnake[N - 1]] = 0;
                for (int i = 0; i < N; i = i + 2) {
                    if (i != N - 1) {
                        tempI1 = tailFirstSnake[i];
                        tempJ1 = tailFirstSnake[i + 1];
                        tailFirstSnake[i] = tempI;
                        tailFirstSnake[i + 1] = tempJ;
                        tempI = tempI1;
                        tempJ = tempJ1;
                    }
                }
                checkTail(n, m, N, area, tailFirstSnake, whichSnake);
                break;
            default:;
        }
    } else {
        int N = (gameData[3] - 1) * 2;
        actualOrientation = orientation;
        switch (actualOrientation) {
            case 0:
                tempI = positionSnakes[2] + 1;
                tempJ = positionSnakes[3];
                area[tempI][tempJ] = TAIL_SECOND_SNAKE;
                if (!checkForMove(n, m, area, tailSecondSnake[N - 1], tailSecondSnake[N - 2]))
                    area[tailSecondSnake[N - 2]][tailSecondSnake[N - 1]] = 0;
                for (int i = 0; i < N; i = i + 2) {
                    if (i != N - 1) {
                        tempI1 = tailSecondSnake[i];
                        tempJ1 = tailSecondSnake[i + 1];
                        tailSecondSnake[i] = tempI;
                        tailSecondSnake[i + 1] = tempJ;
                        tempI = tempI1;
                        tempJ = tempJ1;
                    }
                }
                checkTail(n, m, N, area, tailSecondSnake, whichSnake);
                break;
            case 1:
                tempI = positionSnakes[2] - 1;
                tempJ = positionSnakes[3];
                area[tempI][tempJ] = TAIL_SECOND_SNAKE;
                if (!checkForMove(n, m, area, tailSecondSnake[N - 1], tailSecondSnake[N - 2]))
                    area[tailSecondSnake[N - 2]][tailSecondSnake[N - 1]] = 0;
                for (int i = 0; i < N; i = i + 2) {
                    if (i != N - 1) {
                        tempI1 = tailSecondSnake[i];
                        tempJ1 = tailSecondSnake[i + 1];
                        tailSecondSnake[i] = tempI;
                        tailSecondSnake[i + 1] = tempJ;
                        tempI = tempI1;
                        tempJ = tempJ1;
                    }
                }
                checkTail(n, m, N, area, tailSecondSnake, whichSnake);
                break;
            case 2:
                tempI = positionSnakes[2];
                tempJ = positionSnakes[3] + 1;
                area[tempI][tempJ] = TAIL_SECOND_SNAKE;
                if (!checkForMove(n, m, area, tailSecondSnake[N - 1], tailSecondSnake[N - 2]))
                    area[tailSecondSnake[N - 2]][tailSecondSnake[N - 1]] = 0;
                for (int i = 0; i < N; i = i + 2) {
                    if (i != N - 1) {
                        tempI1 = tailSecondSnake[i];
                        tempJ1 = tailSecondSnake[i + 1];
                        tailSecondSnake[i] = tempI;
                        tailSecondSnake[i + 1] = tempJ;
                        tempI = tempI1;
                        tempJ = tempJ1;
                    }
                }
                checkTail(n, m, N, area, tailSecondSnake, whichSnake);
                break;
            case 3:
                tempI = positionSnakes[2];
                tempJ = positionSnakes[3] - 1;
                area[tempI][tempJ] = TAIL_SECOND_SNAKE;
                if (!checkForMove(n, m, area, tailSecondSnake[N - 1], tailSecondSnake[N - 2]))
                    area[tailSecondSnake[N - 2]][tailSecondSnake[N - 1]] = 0;
                for (int i = 0; i < N; i = i + 2) {
                    if (i != N - 1) {
                        tempI1 = tailSecondSnake[i];
                        tempJ1 = tailSecondSnake[i + 1];
                        tailSecondSnake[i] = tempI;
                        tailSecondSnake[i + 1] = tempJ;
                        tempI = tempI1;
                        tempJ = tempJ1;
                    }
                }
                checkTail(n, m, N, area, tailSecondSnake, whichSnake);
                break;
            default:;
        }
    }
    if (gameData[1] == 0) generateFood(n, m, gameData, area, pointFood);
    fillingArea(n, m, area);
}

void checkTail(int n, int m, int N, int area[][m], const int tailSnake[], bool whichSnake) {
    int valuePoint = whichSnake ? TAIL_SECOND_SNAKE : TAIL_FIRST_SNAKE;
    for (int i = 0; i < N; i = i + 2)
        if (area[tailSnake[i]][tailSnake[i + 1]] == 0) area[tailSnake[i]][tailSnake[i + 1]] = valuePoint;
}

void checkPointFood(int n, int m, int area[][m], int gameData[], int pointFood[]) {
    int valuePoint = FOOD;
    for (int i = 0; i < 8; i = i + 2)
        if (pointFood[i] != 0 && pointFood[i + 1] != 0) {
            if (area[pointFood[i]][pointFood[i + 1]] != valuePoint)
                area[pointFood[i]][pointFood[i + 1]] = valuePoint;
        }
}

void findPointFood(int gameData[], int pointFood[], int y, int x) {
    for (int i = 0; i < 8; i = i + 2)
        if (pointFood[i] == y && pointFood[i + 1] == x) {
            pointFood[i] = 0;
            pointFood[i + 1] = 0;
        }
}

bool checkLose(int n, int m, int area[][m], int x, int y) {
    int value = area[y][x];
    return value == TAIL_FIRST_SNAKE || value == TAIL_SECOND_SNAKE || value == WALL || value == HEAD_ONE || value == HEAD_TWO;
}

bool checkForMove(int n, int m, int area[][m], int x, int y) {
    int value = area[y][x];
    return value == WALL || value == FOOD || value == HEAD_ONE || value == HEAD_TWO;
}

void generateFood(int n, int m, int gameData[], int area[][m], int pointFood[]) {
    short conditionToStop = 4;
    if (gameData[0] < 4) {
        if (gameData[0] == 0) return;
        else if (gameData[0] == 1 && gameData[1] == 0) conditionToStop = 1;
        else if (gameData[0] == 2 && gameData[1] == 0) conditionToStop = 2;
        else if (gameData[0] == 3 && gameData[1] == 0) conditionToStop = 3;
    }
    while (gameData[1] < conditionToStop) {
        int i = 1 + rand() % (n - 2);
        int j = 1 + rand() % (m - 2);
        if (area[i][j] != TAIL_FIRST_SNAKE && area[i][j] != WALL && area[i][j] != TAIL_SECOND_SNAKE && area[i][j] != HEAD_ONE && area[i][j] != HEAD_TWO &&
            area[i][j] != FOOD) {
            area[i][j] = FOOD;
            gameData[1] = gameData[1] + 1;
            switch (gameData[1]) {
                case 1:
                    pointFood[0] = i;
                    pointFood[1] = j;
                    break;
                case 2:
                    pointFood[2] = i;
                    pointFood[3] = j;
                    break;
                case 3:
                    pointFood[4] = i;
                    pointFood[5] = j;
                    break;
                case 4:
                    if (pointFood[0] == 0 && pointFood[1] == 0) {
                        pointFood[0] = i;
                        pointFood[1] = j;
                    } else if (pointFood[2] == 0 && pointFood[3] == 0) {
                        pointFood[2] = i;
                        pointFood[3] = j;
                    } else if (pointFood[4] == 0 && pointFood[5] == 0) {
                        pointFood[4] = i;
                        pointFood[5] = j;
                    } else {
                        pointFood[6] = i;
                        pointFood[7] = j;
                    }
                    break;
            }
            gameData[0] = gameData[0] - 1;
        }
    }
}

void cleanArea(int n, int m, int area[][m], bool createWalls) {
    for (int i = 1; i < n - 1; i++)
        for (int j = 1; j < m - 1; j++)
            area[i][j] = HOLLOW;
    if (createWalls) area[1][1] = POINT;
}

void choosePointForNewPieceOfTail(int n, int m, int area[][m], int endTailFirstSnake[],
                                  int endTailSecondSnake[], short orientation, bool whichSnake) {
    int i, j;
    if (!whichSnake) {
        i = endTailFirstSnake[0];
        j = endTailFirstSnake[1];
        if (orientation == 0 || orientation == 1) {
            j++;
            if (!checkLose(n, m, area, j, i)) {
                endTailFirstSnake[0] = i;
                endTailFirstSnake[1] = j;
                return;
            }
            j -= 2;
            if (!checkLose(n, m, area, j, i)) {
                endTailFirstSnake[0] = i;
                endTailFirstSnake[1] = j;
                return;
            }
        } else {
            i++;
            if (!checkLose(n, m, area, j, i)) {
                endTailFirstSnake[0] = i;
                endTailFirstSnake[1] = j;
                return;
            }
            i -= 2;
            if (!checkLose(n, m, area, j, i)) {
                endTailFirstSnake[0] = i;
                endTailFirstSnake[1] = j;
                return;
            }
        }
    } else {
        i = endTailSecondSnake[0];
        j = endTailSecondSnake[1];
        if (orientation == 0 || orientation == 1) {
            j++;
            if (!checkLose(n, m, area, j, i)) {
                endTailSecondSnake[0] = i;
                endTailSecondSnake[1] = j;
                return;
            }
            j -= 2;
            if (!checkLose(n, m, area, j, i)) {
                endTailSecondSnake[0] = i;
                endTailSecondSnake[1] = j;
                return;
            }
        } else {
            i++;
            if (!checkLose(n, m, area, j, i)) {
                endTailSecondSnake[0] = i;
                endTailSecondSnake[1] = j;
                return;
            }
            i -= 2;
            if (!checkLose(n, m, area, j, i)) {
                endTailSecondSnake[0] = i;
                endTailSecondSnake[1] = j;
                return;
            }
        }
    }
}

void generatePositionSnakes(int n, int m, int area[][m], int positionSnakes[], int gameData[], bool wallsAreDone) {
    int i1, j1;
    int i2, j2;
    bool firstDone = false, secondDone = false;
    short heads = 0;
    do {
        if (!firstDone) {
            i1 = 1 + rand() % (n - 2);
            j1 = 1 + rand() % (m - 2);
        }
        if (!secondDone) {
            i2 = 1 + rand() % (n - 2);
            j2 = 1 + rand() % (m - 2);
        }
        if (area[i1][j1] == 0) {
            firstDone = true;
            area[i1][j1] = HEAD_ONE;
            heads++;
        }
        if (area[i2][j2] == 0) {
            secondDone = true;
            area[i2][j2] = HEAD_TWO;
            heads++;
        }
    } while (heads != 2);
    positionSnakes[0] = i1;
    positionSnakes[1] = j1;
    positionSnakes[2] = i2;
    positionSnakes[3] = j2;
    if (!wallsAreDone) preparationForGenerateWalls(n, m, area, gameData);
}

void preparationForGenerateWalls(int n, int m, int area[][m], int gameData[]) {
    int N = (n - 2) * (m - 2);
    if (N < 25) return;
    else if (N < 50) generateWalls(n, m, area, gameData);
    else {
        generateWalls(n, m, area, gameData);
        generateWalls(n, m, area, gameData);
    }
}

void generateWalls(int n, int m, int area[][m], int gameData[]) {
    int orientation;
    int sizeWall = 1 + rand() % 3;
    int i = 1 + rand() % (n - 2), j = 1 + rand() % (m - 2);
    if (area[i][j] != HEAD_ONE && area[i][j] != HEAD_TWO) {
        area[i][j] = '#';
        --gameData[0];
        ++gameData[4];
    }
    for (int k = 0; k < sizeWall - 1; ++k) {
        orientation = rand() % 3;
        switch (orientation) {
            case 0:
                i++;
                if (area[i][j] != HEAD_ONE && area[i][j] != HEAD_TWO) {
                    area[i][j] = '#';
                    --gameData[0];
                    ++gameData[4];
                }
                break;
            case 1:
                i--;
                if (area[i][j] != HEAD_ONE && area[i][j] != HEAD_TWO) {
                    area[i][j] = '#';
                    --gameData[0];
                    ++gameData[4];
                }
                break;
            case 2:
                j++;
                if (area[i][j] != HEAD_ONE && area[i][j] != HEAD_TWO) {
                    area[i][j] = '#';
                    --gameData[0];
                    ++gameData[4];
                }
                break;
            case 3:
                j--;
                if (area[i][j] != HEAD_ONE && area[i][j] != HEAD_TWO) {
                    area[i][j] = '#';
                    --gameData[0];
                    ++gameData[4];
                }
                break;
            default:;
        }
    }
}


void showHelloMessage() {
    system("cls");
    printf("Добро пожаловать в Змейку!!!\n");
    printf("Краткий гайд:\n");
    printf("Размер поля может быть от 3x3 до 10x10\n");
    printf("Голова первой змейки обозначается ");
    printSymbol('1');
    printf(", второй ");
    printSymbol('2');
    printf("\n");
    printf("Хвост первой змейки обозначается ");
    printSymbol('$');
    printf(" ,второй ");
    printSymbol('&');
    printf("\n");
    printf("Первая змейка ходит на стрелочки, вторая на WASD\n");
    printf("Еда - ");
    printSymbol('e');
    printf("\n");
    printf("Стенки - ");
    printSymbol('#');
    printf("\n");
}

char getSymbol() {
    int YN;
    fflush(stdin);
    YN = getchar();
    fflush(stdin);
    return (char) YN;
}

void createWalls(int n, int m, int area[][m], int gameData[], int positionCursor[]) {
    bool exitFlag = false, possibleExit = true;
    char YN;
    int symbol;
    int countCreatedWalls = 0;
    showMenuForCreateWalls(n, m, gameData, countCreatedWalls, area);
    while (!exitFlag) {
        symbol = getch();
        if (symbol == FIRST_BYTE_ARROW) symbol = getch();
        switch (symbol) {
            case ARROW_UP:
                moveCursor(n, m, area, positionCursor, 0);
                break;
                //нижняя стрелочка
            case ARROW_DOWN:
                moveCursor(n, m, area, positionCursor, 1);
                break;
                //левая стрелочка
            case ARROW_LEFT:
                moveCursor(n, m, area, positionCursor, 2);
                break;
                // правая стрелочка
            case ARROW_RIGHT:
                moveCursor(n, m, area, positionCursor, 3);
                break;
                //W
            case W:
                moveCursor(n, m, area, positionCursor, 0);
                break;
                //S
            case S:
                moveCursor(n, m, area, positionCursor, 1);
                break;
                //A
            case A:
                moveCursor(n, m, area, positionCursor, 2);
                break;
                //D
            case D:
                moveCursor(n, m, area, positionCursor, 3);
                break;
            case ESC:
                if (possibleExit) {
                    printf("Вы уверены что хотите закончить строительство стен?(Y - да, любой другой символ - нет)\n");
                    YN = getSymbol();
                    if (YN == 'Y') {
                        if (area[positionCursor[0]][positionCursor[1]] == GREEN_WALL)
                            area[positionCursor[0]][positionCursor[1]] = WALL;
                        else area[positionCursor[0]][positionCursor[1]] = HOLLOW;
                        return;
                    }
                }
                break;
            case ENTER:
                if (area[positionCursor[0]][positionCursor[1]] == GREEN_WALL)
                    countCreatedWalls = setOrRemoveWall(m, area, gameData, positionCursor, countCreatedWalls, true);
                else countCreatedWalls = setOrRemoveWall(m, area, gameData, positionCursor, countCreatedWalls, false);
                break;
            default:;
        }
        showMenuForCreateWalls(n, m, gameData, countCreatedWalls, area);
        if (gameData[0] < 2) {
            possibleExit = false;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Минимум две клетки на поле должны быть свободны!\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        } else possibleExit = true;
    }
}

void moveCursor(int n, int m, int area[][m], int positionCursor[], short orientation) {
    switch (orientation) {
        case ORIENTATION_UP:
            if (positionCursor[0] - 1 == 0) break;
            if (area[positionCursor[0]][positionCursor[1]] == GREEN_WALL)
                area[positionCursor[0]][positionCursor[1]] = WALL;
            else if (area[positionCursor[0]][positionCursor[1]] != WALL) area[positionCursor[0]][positionCursor[1]] = HOLLOW;
            positionCursor[0]--;
            if (area[positionCursor[0]][positionCursor[1]] == WALL) area[positionCursor[0]][positionCursor[1]] = GREEN_WALL;
            else area[positionCursor[0]][positionCursor[1]] = POINT;
            break;
        case ORIENTATION_DOWN:
            if (positionCursor[0] + 1 == n - 1) break;
            if (area[positionCursor[0]][positionCursor[1]] == GREEN_WALL)
                area[positionCursor[0]][positionCursor[1]] = WALL;
            else if (area[positionCursor[0]][positionCursor[1]] != WALL) area[positionCursor[0]][positionCursor[1]] = HOLLOW;
            positionCursor[0]++;
            if (area[positionCursor[0]][positionCursor[1]] == WALL) area[positionCursor[0]][positionCursor[1]] = GREEN_WALL;
            else area[positionCursor[0]][positionCursor[1]] = POINT;
            break;
        case ORIENTATION_LEFT:
            if (positionCursor[1] - 1 == 0) break;
            if (area[positionCursor[0]][positionCursor[1]] == GREEN_WALL)
                area[positionCursor[0]][positionCursor[1]] = WALL;
            else if (area[positionCursor[0]][positionCursor[1]] != WALL) area[positionCursor[0]][positionCursor[1]] = HOLLOW;
            positionCursor[1]--;
            if (area[positionCursor[0]][positionCursor[1]] == WALL) area[positionCursor[0]][positionCursor[1]] = GREEN_WALL;
            else area[positionCursor[0]][positionCursor[1]] = POINT;
            break;
        case ORIENTATION_RIGHT:
            if (positionCursor[1] + 1 == m - 1) break;
            if (area[positionCursor[0]][positionCursor[1]] == GREEN_WALL)
                area[positionCursor[0]][positionCursor[1]] = WALL;
            else if (area[positionCursor[0]][positionCursor[1]] != WALL) area[positionCursor[0]][positionCursor[1]] = HOLLOW;
            positionCursor[1]++;
            if (area[positionCursor[0]][positionCursor[1]] == WALL) area[positionCursor[0]][positionCursor[1]] = GREEN_WALL;
            else area[positionCursor[0]][positionCursor[1]] = POINT;
            break;
        default:;
    }
}

int
setOrRemoveWall(int m, int area[][m], int gameData[], int positionCursor[], int countCreatedWalls, bool setOrRemove) {
    if (!setOrRemove) {
        area[positionCursor[0]][positionCursor[1]] = GREEN_WALL;
        --gameData[0];
        ++gameData[4];
        ++countCreatedWalls;
    } else {
        area[positionCursor[0]][positionCursor[1]] = POINT;
        ++gameData[0];
        --gameData[4];
        --countCreatedWalls;
    }
    return countCreatedWalls;
}

void showMenuForCreateWalls(int n, int m, int gameData[], int countCreateWalls, int area[][m]) {
    system("cls");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            printSymbol((short) area[i][j]);
            if (j == m - 1) printf("\n");
        }
    printf("Кол-во свободных клеток: %d\n", gameData[0]);
    printf("Кол-во созданных стен: %d\n", countCreateWalls);
}

void printSymbol(short numberSymbol) {
    switch (numberSymbol) {
        case TAIL_FIRST_SNAKE:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            printf("|$|");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case TAIL_SECOND_SNAKE:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
            printf("|&|");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case WALL:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("|#|");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case GREEN_WALL:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("|#|");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case HEAD_ONE:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
            printf("|1|");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case HEAD_TWO:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
            printf("|2|");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case FOOD:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("|e|");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case POINT:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("|•|");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        default:
            printf("| |");
    }
}

long validationGameArea() {
    long result;
    short minArea = 3, maxArea = 10;
    do {
        result = validation();
        if (result > maxArea || result < minArea) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Неверный ввод размера поля! Размер поля может принимать значения от %hd до %hd\n", minArea,
                   maxArea);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
    } while (result > maxArea || result < minArea);
    return result;
}

bool checkOverflow(double d) {
    return d >= -2147483648 && d <= 2147483647;
}

void determineThePosition(const int gameData[], const int endTailFirstSnake[], const int endTailSecondSnake[],
                          int allTailFirstSnake[],
                          int allTailSecondSnake[], bool whichSnake) {
    if (!whichSnake) {
        allTailFirstSnake[(gameData[2] - 1) + (gameData[2] - 1)] = endTailFirstSnake[0];
        allTailFirstSnake[(gameData[2] - 1) + (gameData[2] - 1) + 1] = endTailFirstSnake[1];
    } else {
        allTailSecondSnake[(gameData[3] - 1) + (gameData[3] - 1)] = endTailSecondSnake[0];
        allTailSecondSnake[(gameData[3] - 1) + (gameData[3] - 1) + 1] = endTailSecondSnake[1];
    }
}