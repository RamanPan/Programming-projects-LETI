#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "functionality.h"

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

void showMenu(int n, int gameData[], int area[][n], int pointsForWin) {
    system("cls");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            printSymbol((short) area[i][j]);
            if (j == n - 1) printf("\n");
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
    printf("Кол-во очков для победы: %d\n", pointsForWin);
    printf("Кол-во свободных клеток: %d\n", gameData[0]);
    printf("Кол-во еды на поле: %d\n", gameData[1]);
}

void fillingArea(int n, int area[][n]) {
    for (int i = 0; i < n; ++i) {
        area[i][0] = '#';
        area[i][n - 1] = '#';
    }
    for (int j = 0; j < n; ++j) {
        area[0][j] = '#';
        area[n - 1][j] = '#';
    }
}

bool
snakeMotion(int n, int area[][n], int gameData[], int positionSnakes[], int endTailFirstSnake[],
            int endTailSecondSnake[], int allTailFirstSnake[], int allTailSecondSnake[], int pointFood[],
            short orientation, bool whichSnake) {
    bool isItFood = false;
    int xEndTail, yEndTail;
    if (!whichSnake) {
        switch (orientation) {
            case 3:
                positionSnakes[1] = positionSnakes[1] + 1;
                if (checkLose(n, area, positionSnakes[1], positionSnakes[0])) return true;
                if (area[positionSnakes[0]][positionSnakes[1]] == 101) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[0], positionSnakes[1]);
                }
                area[positionSnakes[0]][positionSnakes[1]] = 49;
                if (area[positionSnakes[0]][positionSnakes[1] - 1] == 49)
                    area[positionSnakes[0]][positionSnakes[1] - 1] = 0;
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
                        if (checkLose(n, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, area, endTailFirstSnake, endTailSecondSnake, orientation,
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
                    area[yEndTail][xEndTail] = 36;
                    gameData[2] = gameData[2] + 1;
                }
                if (gameData[2] >= 3 || gameData[2] == 2 && !isItFood)
                    tailMotion(n, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake, pointFood,
                               orientation, whichSnake);
//                if (gameData[2] > 1 && area[positionSnakes[0]][positionSnakes[1] - 1] == 0)
//                    area[positionSnakes[0]][positionSnakes[1] - 1] = 36;
                break;
            case 2:
                positionSnakes[1] = positionSnakes[1] - 1;
                if (checkLose(n, area, positionSnakes[1], positionSnakes[0])) return true;
                if (area[positionSnakes[0]][positionSnakes[1]] == 101) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[0], positionSnakes[1]);
                }
                area[positionSnakes[0]][positionSnakes[1]] = 49;
                if (area[positionSnakes[0]][positionSnakes[1] + 1] == 49)
                    area[positionSnakes[0]][positionSnakes[1] + 1] = 0;
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
                        if (checkLose(n, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, area, endTailFirstSnake, endTailSecondSnake, orientation,
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
                    area[yEndTail][xEndTail] = 36;
                    gameData[2] = gameData[2] + 1;
                }
                if (gameData[2] >= 3 || gameData[2] == 2 && !isItFood)
                    tailMotion(n, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake,
                               pointFood, orientation, whichSnake);
//                if (gameData[2] > 1 && area[positionSnakes[0]][positionSnakes[1] + 1] == 0)
//                    area[positionSnakes[0]][positionSnakes[1] + 1] = 36;
                break;
            case 0:
                positionSnakes[0] = positionSnakes[0] - 1;
                if (checkLose(n, area, positionSnakes[1], positionSnakes[0])) return true;
                if (area[positionSnakes[0]][positionSnakes[1]] == 101) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[0], positionSnakes[1]);
                }
                area[positionSnakes[0]][positionSnakes[1]] = 49;
                if (area[positionSnakes[0] + 1][positionSnakes[1]] == 49)
                    area[positionSnakes[0] + 1][positionSnakes[1]] = 0;
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
                        if (checkLose(n, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, area, endTailFirstSnake, endTailSecondSnake, orientation,
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
                    area[yEndTail][xEndTail] = 36;
                    gameData[2] = gameData[2] + 1;
                }
                if (gameData[2] >= 3 || gameData[2] == 2 && !isItFood)
                    tailMotion(n, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake, pointFood,
                               orientation, whichSnake);
//                if (gameData[2] > 1 && area[positionSnakes[0] + 1][positionSnakes[1]] == 0)
//                    area[positionSnakes[0] + 1][positionSnakes[1]] = 36;
                break;
            case 1:
                positionSnakes[0] = positionSnakes[0] + 1;
                if (checkLose(n, area, positionSnakes[1], positionSnakes[0])) return true;
                if (area[positionSnakes[0]][positionSnakes[1]] == 101) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[0], positionSnakes[1]);
                }
                area[positionSnakes[0]][positionSnakes[1]] = 49;
                if (area[positionSnakes[0] - 1][positionSnakes[1]] == 49)
                    area[positionSnakes[0] - 1][positionSnakes[1]] = 0;
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
                        if (checkLose(n, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, area, endTailFirstSnake, endTailSecondSnake, orientation,
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
                    area[yEndTail][xEndTail] = 36;
                    gameData[2] = gameData[2] + 1;
                }
                if (gameData[2] >= 3 || gameData[2] == 2 && !isItFood)
                    tailMotion(n, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake, pointFood,
                               orientation, whichSnake);
//                if (gameData[2] > 1 && area[positionSnakes[0] - 1][positionSnakes[1]] == 0)
//                    area[positionSnakes[0] - 1][positionSnakes[1]] = 36;
                break;
            default:;
        }
    } else {
        switch (orientation) {
            case 3:
                positionSnakes[3] = positionSnakes[3] + 1;
                if (checkLose(n, area, positionSnakes[3], positionSnakes[2])) return true;
                if (area[positionSnakes[2]][positionSnakes[3]] == 101) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[2], positionSnakes[3]);
                }
                area[positionSnakes[2]][positionSnakes[3]] = 50;
                if (area[positionSnakes[2]][positionSnakes[3] - 1] == 50)
                    area[positionSnakes[2]][positionSnakes[3] - 1] = 0;
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
                        if (checkLose(n, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, area, endTailFirstSnake, endTailSecondSnake, orientation,
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
                    area[yEndTail][xEndTail] = 38;
                    gameData[3] = gameData[3] + 1;
                }
                if (gameData[3] >= 3 || gameData[3] == 2 && !isItFood)
                    tailMotion(n, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake, pointFood,
                               orientation, whichSnake);
//                if (gameData[3] > 1 && area[positionSnakes[2]][positionSnakes[3] - 1] == 0)
//                    area[positionSnakes[2]][positionSnakes[3] - 1] = 38;
                break;
            case 2:
                positionSnakes[3] = positionSnakes[3] - 1;
                if (checkLose(n, area, positionSnakes[3], positionSnakes[2])) return true;
                if (area[positionSnakes[2]][positionSnakes[3]] == 101) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[2], positionSnakes[3]);
                }
                area[positionSnakes[2]][positionSnakes[3]] = 50;
                if (area[positionSnakes[2]][positionSnakes[3] + 1] == 50)
                    area[positionSnakes[2]][positionSnakes[3] + 1] = 0;
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
                        if (checkLose(n, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, area, endTailFirstSnake, endTailSecondSnake, orientation,
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
                    area[yEndTail][xEndTail] = 38;
                    gameData[3] = gameData[3] + 1;
                }
                if (gameData[3] >= 3 || gameData[3] == 2 && !isItFood)
                    tailMotion(n, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake, pointFood,
                               orientation, whichSnake);
//                if (gameData[3] > 1 && area[positionSnakes[2]][positionSnakes[3] + 1] == 0)
//                    area[positionSnakes[2]][positionSnakes[3] + 1] = 38;
                break;
            case 0:
                positionSnakes[2] = positionSnakes[2] - 1;
                if (checkLose(n, area, positionSnakes[3], positionSnakes[2])) return true;
                if (area[positionSnakes[2]][positionSnakes[3]] == 101) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[2], positionSnakes[3]);
                }
                area[positionSnakes[2]][positionSnakes[3]] = 50;
                if (area[positionSnakes[2] + 1][positionSnakes[3]] == 50)
                    area[positionSnakes[2] + 1][positionSnakes[3]] = 0;
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
                        if (checkLose(n, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, area, endTailFirstSnake, endTailSecondSnake, orientation,
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
                    area[yEndTail][xEndTail] = 38;
                    gameData[3] = gameData[3] + 1;
                }
                if (gameData[3] >= 3 || gameData[3] == 2 && !isItFood)
                    tailMotion(n, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake, pointFood,
                               orientation, whichSnake);
//                if (gameData[3] > 1 && area[positionSnakes[2] + 1][positionSnakes[3]] == 0)
//                    area[positionSnakes[2] + 1][positionSnakes[3]] = 38;
                break;
            case 1:
                positionSnakes[2] = positionSnakes[2] + 1;
                if (checkLose(n, area, positionSnakes[3], positionSnakes[2])) return true;
                if (area[positionSnakes[2]][positionSnakes[3]] == 101) {
                    isItFood = true;
                    findPointFood(gameData, pointFood, positionSnakes[2], positionSnakes[3]);
                }
                area[positionSnakes[2]][positionSnakes[3]] = 50;
                if (area[positionSnakes[2] - 1][positionSnakes[3]] == 50)
                    area[positionSnakes[2] - 1][positionSnakes[3]] = 0;
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
                        if (checkLose(n, area, xEndTail, yEndTail)) {
                            choosePointForNewPieceOfTail(n, area, endTailFirstSnake, endTailSecondSnake, orientation,
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
                    area[yEndTail][xEndTail] = 38;
                    gameData[3] = gameData[3] + 1;
                }
                if (gameData[3] >= 3 || gameData[3] == 2 && !isItFood)
                    tailMotion(n, area, gameData, positionSnakes, allTailFirstSnake, allTailSecondSnake, pointFood,
                               orientation, whichSnake);
//                if (gameData[3] > 1 && area[positionSnakes[2] - 1][positionSnakes[3]] == 0)
//                    area[positionSnakes[2] - 1][positionSnakes[3]] = 38;
                break;
            default:;
        }
    }
    if (isItFood) generateFood(n, gameData, area, pointFood);
    checkPointFood(n, area, gameData, pointFood);
    return false;
}

void tailMotion(int n, int area[][n], int gameData[], const int positionSnakes[], int tailFirstSnake[],
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
                area[tempI][tempJ] = 36;
                if (!checkForMove(n, area, tailFirstSnake[N - 1], tailFirstSnake[N - 2]))
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
                checkTail(n, N, area, tailFirstSnake, whichSnake);
                break;
            case 1:
                tempI = positionSnakes[0] - 1;
                tempJ = positionSnakes[1];
                area[tempI][tempJ] = 36;
                if (!checkForMove(n, area, tailFirstSnake[N - 1], tailFirstSnake[N - 2]))
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
                checkTail(n, N, area, tailFirstSnake, whichSnake);
                break;
            case 2:
                tempI = positionSnakes[0];
                tempJ = positionSnakes[1] + 1;
                area[tempI][tempJ] = 36;
                if (!checkForMove(n, area, tailFirstSnake[N - 1], tailFirstSnake[N - 2]))
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
                checkTail(n, N, area, tailFirstSnake, whichSnake);
                break;
            case 3:
                tempI = positionSnakes[0];
                tempJ = positionSnakes[1] - 1;
                area[tempI][tempJ] = 36;
                if (!checkForMove(n, area, tailFirstSnake[N - 1], tailFirstSnake[N - 2]))
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
                checkTail(n, N, area, tailFirstSnake, whichSnake);
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
                area[tempI][tempJ] = 38;
                if (!checkForMove(n, area, tailSecondSnake[N - 1], tailSecondSnake[N - 2]))
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
                checkTail(n, N, area, tailSecondSnake, whichSnake);
                break;
            case 1:
                tempI = positionSnakes[2] - 1;
                tempJ = positionSnakes[3];
                area[tempI][tempJ] = 38;
                if (!checkForMove(n, area, tailSecondSnake[N - 1], tailSecondSnake[N - 2]))
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
                checkTail(n, N, area, tailSecondSnake, whichSnake);
                break;
            case 2:
                tempI = positionSnakes[2];
                tempJ = positionSnakes[3] + 1;
                area[tempI][tempJ] = 38;
                if (!checkForMove(n, area, tailSecondSnake[N - 1], tailSecondSnake[N - 2]))
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
                checkTail(n, N, area, tailSecondSnake, whichSnake);
                break;
            case 3:
                tempI = positionSnakes[2];
                tempJ = positionSnakes[3] - 1;
                area[tempI][tempJ] = 38;
                if (!checkForMove(n, area, tailSecondSnake[N - 1], tailSecondSnake[N - 2]))
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
                checkTail(n, N, area, tailSecondSnake, whichSnake);
                break;
            default:;
        }
    }
    if (gameData[1] == 0) generateFood(n, gameData, area, pointFood);
    fillingArea(n, area);
}

void checkTail(int n, int N, int area[][n], const int tailSnake[], bool whichSnake) {
    int valuePoint = whichSnake ? 38 : 36;
    for (int i = 0; i < N; i = i + 2)
        if (area[tailSnake[i]][tailSnake[i + 1]] == 0) area[tailSnake[i]][tailSnake[i + 1]] = valuePoint;
}

void checkPointFood(int n, int area[][n], int gameData[], int pointFood[]) {
    int valuePoint = 101;
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

bool checkLose(int n, int area[][n], int x, int y) {
    int value = area[y][x];
    return value == 36 || value == 38 || value == 35 || value == 49 || value == 50;
}

bool checkForMove(int n, int area[][n], int x, int y) {
    int value = area[y][x];
    return value == 35 || value == 101 || value == 49 || value == 50;
}

void generateFood(int n, int gameData[], int area[][n], int pointFood[]) {
    short conditionToStop = 4;
    if (gameData[0] < 4 && gameData[1] == 4 || gameData[0] == 0) {
        return;
    } else if (gameData[0] < 4) conditionToStop = 1;
    while (gameData[1] < conditionToStop) {
        int i = 1 + rand() % (n - 2);
        int j = 1 + rand() % (n - 2);
        if (area[i][j] != 36 && area[i][j] != 38 && area[i][j] != 49 && area[i][j] != 50 && area[i][j] != 101) {
            area[i][j] = 101;
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

void cleanArea(int n, int area[][n]) {
    for (int i = 1; i < n - 1; i++)
        for (int j = 1; j < n - 1; j++)
            area[i][j] = 0;
}

void choosePointForNewPieceOfTail(int n, int area[][n], int endTailFirstSnake[],
                                  int endTailSecondSnake[], short orientation, bool whichSnake) {
    int i, j;
    if (!whichSnake) {
        i = endTailFirstSnake[0];
        j = endTailFirstSnake[1];
        if (orientation == 0 || orientation == 1) {
            j++;
            if (!checkLose(n, area, j, i)) {
                endTailFirstSnake[0] = i;
                endTailFirstSnake[1] = j;
                return;
            }
            j -= 2;
            if (!checkLose(n, area, j, i)) {
                endTailFirstSnake[0] = i;
                endTailFirstSnake[1] = j;
                return;
            }
        } else {
            i++;
            if (!checkLose(n, area, j, i)) {
                endTailFirstSnake[0] = i;
                endTailFirstSnake[1] = j;
                return;
            }
            i -= 2;
            if (!checkLose(n, area, j, i)) {
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
            if (!checkLose(n, area, j, i)) {
                endTailSecondSnake[0] = i;
                endTailSecondSnake[1] = j;
                return;
            }
            j -= 2;
            if (!checkLose(n, area, j, i)) {
                endTailSecondSnake[0] = i;
                endTailSecondSnake[1] = j;
                return;
            }
        } else {
            i++;
            if (!checkLose(n, area, j, i)) {
                endTailSecondSnake[0] = i;
                endTailSecondSnake[1] = j;
                return;
            }
            i -= 2;
            if (!checkLose(n, area, j, i)) {
                endTailSecondSnake[0] = i;
                endTailSecondSnake[1] = j;
                return;
            }
        }
    }
}

void generatePositionSnakes(int n, int area[][n], int positionSnakes[], int gameData[]) {
    int i1 = 1 + rand() % (n - 2), j1 = 1 + rand() % (n - 2);
    int i2 = 1 + rand() % (n - 2), j2 = 1 + rand() % (n - 2);
    area[i1][j1] = 49;
    if (i1 != i2 || j1 != j2) area[i2][j2] = 50;
    else {
        i2 = 1 + rand() % (n - 2);
        j2 = 1 + rand() % (n - 2);
        area[i2][j2] = 50;
    }
    positionSnakes[0] = i1;
    positionSnakes[1] = j1;
    positionSnakes[2] = i2;
    positionSnakes[3] = j2;
    preparationForGenerateWalls(n, area, gameData);
}

void preparationForGenerateWalls(int n, int area[][n], int gameData[]) {
    int N = n - 2;
    if (N < 5) return;
    else if (N < 8) generateWalls(n, area, gameData);
    else {
        generateWalls(n, area, gameData);
        generateWalls(n, area, gameData);
    }
}

void generateWalls(int n, int area[][n], int gameData[]) {
    int orientation;
    int sizeWall = 1 + rand() % 3;
    int i = 1 + rand() % (n - 2), j = 1 + rand() % (n - 2);
    if (area[i][j] != 49 && area[i][j] != 50) {
        area[i][j] = '#';
        --gameData[0];
    }
    for (int k = 0; k < sizeWall - 1; ++k) {
        orientation = rand() % 3;
        switch (orientation) {
            case 0:
                i++;
                if (area[i][j] != 49 && area[i][j] != 50) {
                    area[i][j] = '#';
                    --gameData[0];
                }
                break;
            case 1:
                i--;
                if (area[i][j] != 49 && area[i][j] != 50) {
                    area[i][j] = '#';
                    --gameData[0];
                }
                break;
            case 2:
                j++;
                if (area[i][j] != 49 && area[i][j] != 50) {
                    area[i][j] = '#';
                    --gameData[0];
                }
                break;
            case 3:
                j--;
                if (area[i][j] != 49 && area[i][j] != 50) {
                    area[i][j] = '#';
                    --gameData[0];
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

void printSymbol(short numberSymbol) {
    switch (numberSymbol) {
        case 36:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            printf("|$|");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case 38:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
            printf("|&|");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case 35:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("|#|");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case 49:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
            printf("|1|");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case 50:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
            printf("|2|");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case 101:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("|e|");
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
        switch (gameData[2]) {
            case 1:
                allTailFirstSnake[0] = endTailFirstSnake[0];
                allTailFirstSnake[1] = endTailFirstSnake[1];
                break;
            case 2:
                allTailFirstSnake[2] = endTailFirstSnake[0];
                allTailFirstSnake[3] = endTailFirstSnake[1];
                break;
            case 3:
                allTailFirstSnake[4] = endTailFirstSnake[0];
                allTailFirstSnake[5] = endTailFirstSnake[1];
                break;
            case 4:
                allTailFirstSnake[6] = endTailFirstSnake[0];
                allTailFirstSnake[7] = endTailFirstSnake[1];
                break;
            case 5:
                allTailFirstSnake[8] = endTailFirstSnake[0];
                allTailFirstSnake[9] = endTailFirstSnake[1];
                break;
            case 6:
                allTailFirstSnake[10] = endTailFirstSnake[0];
                allTailFirstSnake[11] = endTailFirstSnake[1];
                break;
            case 7:
                allTailFirstSnake[12] = endTailFirstSnake[0];
                allTailFirstSnake[13] = endTailFirstSnake[1];
                break;
            case 8:
                allTailFirstSnake[14] = endTailFirstSnake[0];
                allTailFirstSnake[15] = endTailFirstSnake[1];
                break;
            case 9:
                allTailFirstSnake[16] = endTailFirstSnake[0];
                allTailFirstSnake[17] = endTailFirstSnake[1];
                break;
            case 10:
                allTailFirstSnake[18] = endTailFirstSnake[0];
                allTailFirstSnake[19] = endTailFirstSnake[1];
                break;
            case 11:
                allTailFirstSnake[20] = endTailFirstSnake[0];
                allTailFirstSnake[21] = endTailFirstSnake[1];
                break;
            case 12:
                allTailFirstSnake[22] = endTailFirstSnake[0];
                allTailFirstSnake[23] = endTailFirstSnake[1];
                break;
            case 13:
                allTailFirstSnake[24] = endTailFirstSnake[0];
                allTailFirstSnake[25] = endTailFirstSnake[1];
                break;
            case 14:
                allTailFirstSnake[26] = endTailFirstSnake[0];
                allTailFirstSnake[27] = endTailFirstSnake[1];
                break;
            case 15:
                allTailFirstSnake[28] = endTailFirstSnake[0];
                allTailFirstSnake[29] = endTailFirstSnake[1];
                break;
            case 16:
                allTailFirstSnake[30] = endTailFirstSnake[0];
                allTailFirstSnake[31] = endTailFirstSnake[1];
                break;
            case 17:
                allTailFirstSnake[32] = endTailFirstSnake[0];
                allTailFirstSnake[33] = endTailFirstSnake[1];
                break;
            case 18:
                allTailFirstSnake[34] = endTailFirstSnake[0];
                allTailFirstSnake[35] = endTailFirstSnake[1];
                break;
            case 19:
                allTailFirstSnake[36] = endTailFirstSnake[0];
                allTailFirstSnake[37] = endTailFirstSnake[1];
                break;
            case 20:
                allTailFirstSnake[38] = endTailFirstSnake[0];
                allTailFirstSnake[39] = endTailFirstSnake[1];
                break;
            case 21:
                allTailFirstSnake[40] = endTailFirstSnake[0];
                allTailFirstSnake[41] = endTailFirstSnake[1];
                break;
            case 22:
                allTailFirstSnake[42] = endTailFirstSnake[0];
                allTailFirstSnake[43] = endTailFirstSnake[1];
                break;
            case 23:
                allTailFirstSnake[44] = endTailFirstSnake[0];
                allTailFirstSnake[45] = endTailFirstSnake[1];
            case 24:
                allTailFirstSnake[46] = endTailFirstSnake[0];
                allTailFirstSnake[47] = endTailFirstSnake[1];
                break;
            case 25:
                allTailFirstSnake[48] = endTailFirstSnake[0];
                allTailFirstSnake[49] = endTailFirstSnake[1];
                break;
        }
    } else {
        switch (gameData[3]) {
            case 1:
                allTailSecondSnake[0] = endTailSecondSnake[0];
                allTailSecondSnake[1] = endTailSecondSnake[1];
                break;
            case 2:
                allTailSecondSnake[2] = endTailSecondSnake[0];
                allTailSecondSnake[3] = endTailSecondSnake[1];
                break;
            case 3:
                allTailSecondSnake[4] = endTailSecondSnake[0];
                allTailSecondSnake[5] = endTailSecondSnake[1];
                break;
            case 4:
                allTailSecondSnake[6] = endTailSecondSnake[0];
                allTailSecondSnake[7] = endTailSecondSnake[1];
                break;
            case 5:
                allTailSecondSnake[8] = endTailSecondSnake[0];
                allTailSecondSnake[9] = endTailSecondSnake[1];
                break;
            case 6:
                allTailSecondSnake[10] = endTailSecondSnake[0];
                allTailSecondSnake[11] = endTailSecondSnake[1];
                break;
            case 7:
                allTailSecondSnake[12] = endTailSecondSnake[0];
                allTailSecondSnake[13] = endTailSecondSnake[1];
                break;
            case 8:
                allTailSecondSnake[14] = endTailSecondSnake[0];
                allTailSecondSnake[15] = endTailSecondSnake[1];
                break;
            case 9:
                allTailSecondSnake[16] = endTailSecondSnake[0];
                allTailSecondSnake[17] = endTailSecondSnake[1];
                break;
            case 10:
                allTailSecondSnake[18] = endTailSecondSnake[0];
                allTailSecondSnake[19] = endTailSecondSnake[1];
                break;
            case 11:
                allTailSecondSnake[20] = endTailSecondSnake[0];
                allTailSecondSnake[21] = endTailSecondSnake[1];
                break;
            case 12:
                allTailSecondSnake[22] = endTailSecondSnake[0];
                allTailSecondSnake[23] = endTailSecondSnake[1];
                break;
            case 13:
                allTailSecondSnake[24] = endTailSecondSnake[0];
                allTailSecondSnake[25] = endTailSecondSnake[1];
                break;
            case 14:
                allTailSecondSnake[26] = endTailSecondSnake[0];
                allTailSecondSnake[27] = endTailSecondSnake[1];
                break;
            case 15:
                allTailSecondSnake[28] = endTailSecondSnake[0];
                allTailSecondSnake[29] = endTailSecondSnake[1];
                break;
            case 16:
                allTailSecondSnake[30] = endTailSecondSnake[0];
                allTailSecondSnake[31] = endTailSecondSnake[1];
                break;
            case 17:
                allTailSecondSnake[32] = endTailSecondSnake[0];
                allTailSecondSnake[33] = endTailSecondSnake[1];
                break;
            case 18:
                allTailSecondSnake[34] = endTailSecondSnake[0];
                allTailSecondSnake[35] = endTailSecondSnake[1];
                break;
            case 19:
                allTailSecondSnake[36] = endTailSecondSnake[0];
                allTailSecondSnake[37] = endTailSecondSnake[1];
                break;
            case 20:
                allTailSecondSnake[38] = endTailSecondSnake[0];
                allTailSecondSnake[39] = endTailSecondSnake[1];
                break;
            case 21:
                allTailSecondSnake[40] = endTailSecondSnake[0];
                allTailSecondSnake[41] = endTailSecondSnake[1];
                break;
            case 22:
                allTailSecondSnake[42] = endTailSecondSnake[0];
                allTailSecondSnake[43] = endTailSecondSnake[1];
                break;
            case 23:
                allTailSecondSnake[44] = endTailSecondSnake[0];
                allTailSecondSnake[45] = endTailSecondSnake[1];
                break;
            case 24:
                allTailSecondSnake[46] = endTailSecondSnake[0];
                allTailSecondSnake[47] = endTailSecondSnake[1];
                break;
            case 25:
                allTailSecondSnake[48] = endTailSecondSnake[0];
                allTailSecondSnake[49] = endTailSecondSnake[1];
                break;
        }
    }
}