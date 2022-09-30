#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functionality.h"

long validation() {
    bool validationFlag = false;
    double result;
    while (!validationFlag) {
        if (scanf("%lf", &result)) {
            if (!checkOverflow(result)) {
                printf("Неправильный ввод! Число вышло за границу дозволенного! Попробуйте снова!\n");
                fflush(stdin);
            } else validationFlag = true;
        } else {
            printf("Неправильный ввод! Попробуйте снова!\n");
            fflush(stdin);
        }
    }
    return (long) result;
}

void showMenu(int n, int gameData[], int area[][n]) {
    system("cls");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            printSymbol((short) area[i][j]);
            if (j == n - 1) printf("\n");
        }
    printf("Счёт: %d:%d\n", gameData[2], gameData[3]);
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

bool snakeMotion(int n, int area[][n], int gameData[], int positionSnakes[], short orientation, bool whichSnake) {
    bool isItFood = false;
    if (!whichSnake) {
        switch (orientation) {
            case 3:
                positionSnakes[1] = positionSnakes[1] + 1;
                if (checkLose(n, area, positionSnakes[1], positionSnakes[0])) return true;
                if (area[positionSnakes[0]][positionSnakes[1]] == 101) isItFood = true;
                area[positionSnakes[0]][positionSnakes[1]] = 49;
                area[positionSnakes[0]][positionSnakes[1] - 1] = 0;
                if (isItFood) {
                    gameData[1]--;
                    generateFood(n,gameData,area);
                    if (gameData[2] == 1) area[positionSnakes[0]][positionSnakes[1] - 1] = 36;
                    //else
                    gameData[2] = gameData[2] + 1;
                }
                break;
            case 2:
                positionSnakes[1] = positionSnakes[1] - 1;
                if (checkLose(n, area, positionSnakes[1], positionSnakes[0])) return true;
                if (area[positionSnakes[0]][positionSnakes[1]] == 101) isItFood = true;
                area[positionSnakes[0]][positionSnakes[1]] = 49;
                area[positionSnakes[0]][positionSnakes[1] + 1] = 0;
                if (isItFood) {
                    gameData[1]--;
                    generateFood(n,gameData,area);
                    if (gameData[2] == 1) area[positionSnakes[0]][positionSnakes[1] + 1] = 36;
                    //else
                    gameData[2] = gameData[2] + 1;
                }
                break;
            case 0:
                positionSnakes[0] = positionSnakes[0] - 1;
                if (checkLose(n, area, positionSnakes[1], positionSnakes[0])) return true;
                if (area[positionSnakes[0]][positionSnakes[1]] == 101) isItFood = true;
                area[positionSnakes[0]][positionSnakes[1]] = 49;
                area[positionSnakes[0] + 1][positionSnakes[1]] = 0;
                if (isItFood) {
                    gameData[1]--;
                    generateFood(n,gameData,area);
                    if (gameData[2] == 1) area[positionSnakes[0] + 1][positionSnakes[1]] = 36;
                    //else
                    gameData[2] = gameData[2] + 1;
                }
                break;
            case 1:
                positionSnakes[0] = positionSnakes[0] + 1;
                if (checkLose(n, area, positionSnakes[1], positionSnakes[0])) return true;
                if (area[positionSnakes[0]][positionSnakes[1]] == 101) isItFood = true;
                area[positionSnakes[0]][positionSnakes[1]] = 49;
                area[positionSnakes[0] - 1][positionSnakes[1]] = 0;
                if (isItFood) {
                    gameData[1]--;
                    generateFood(n,gameData,area);
                    if (gameData[2] == 1) area[positionSnakes[0] - 1][positionSnakes[1]] = 36;
                    //else
                    gameData[2] = gameData[2] + 1;
                }
                break;
        }
    } else {
        switch (orientation) {
            case 3:
                positionSnakes[3] = positionSnakes[3] + 1;
                if (checkLose(n, area, positionSnakes[3], positionSnakes[2])) return true;
                if (area[positionSnakes[2]][positionSnakes[3]] == 101) isItFood = true;
                area[positionSnakes[2]][positionSnakes[3]] = 50;
                area[positionSnakes[2]][positionSnakes[3] - 1] = 0;
                if (isItFood) {
                    gameData[1]--;
                    generateFood(n,gameData,area);
                    if (gameData[3] == 1) area[positionSnakes[2]][positionSnakes[3] - 1] = 38;
                    //else
                    gameData[3] = gameData[3] + 1;
                }
                break;
            case 2:
                positionSnakes[3] = positionSnakes[3] - 1;
                if (checkLose(n, area, positionSnakes[3], positionSnakes[2])) return true;
                if (area[positionSnakes[2]][positionSnakes[3]] == 101) isItFood = true;
                area[positionSnakes[2]][positionSnakes[3]] = 50;
                area[positionSnakes[2]][positionSnakes[3] + 1] = 0;
                if (isItFood) {
                    gameData[1]--;
                    generateFood(n,gameData,area);
                    if (gameData[3] == 1) area[positionSnakes[2]][positionSnakes[3] + 1] = 38;
                    //else
                    gameData[3] = gameData[3] + 1;
                }
                break;
            case 0:
                positionSnakes[2] = positionSnakes[2] - 1;
                if (checkLose(n, area, positionSnakes[3], positionSnakes[2])) return true;
                if (area[positionSnakes[2]][positionSnakes[3]] == 101) isItFood = true;
                area[positionSnakes[2]][positionSnakes[3]] = 50;
                area[positionSnakes[2] + 1][positionSnakes[3]] = 0;
                if (isItFood) {
                    gameData[1]--;
                    generateFood(n,gameData,area);
                    if (gameData[3] == 1) area[positionSnakes[2] + 1][positionSnakes[3]] = 38;
                    //else
                    gameData[3] = gameData[3] + 1;
                }
                break;
            case 1:
                positionSnakes[2] = positionSnakes[2] + 1;
                if (checkLose(n, area, positionSnakes[3], positionSnakes[2])) return true;
                if (area[positionSnakes[2]][positionSnakes[3]] == 101) isItFood = true;
                area[positionSnakes[2]][positionSnakes[3]] = 50;
                area[positionSnakes[2] - 1][positionSnakes[3]] = 0;
                if (isItFood) {
                    gameData[1]--;
                    generateFood(n,gameData,area);
                    if (gameData[3] == 1) area[positionSnakes[2] - 1][positionSnakes[3]] = 38;
                    //else
                    gameData[3] = gameData[3] + 1;
                }
                break;
        }
    }
    return false;
}

bool checkLose(int n, int area[][n], int x, int y) {
    int value = area[y][x];
    return value == 36 || value == 38 || value == 35 || value == 49 || value == 50;
}

void generateFood(int n, int gameData[], int area[][n]) {
    bool opportunityToGenerate = true;
    if (gameData[0] < 4) {
        opportunityToGenerate = false;
        return;
    }
    while (gameData[1] != 4) {
        srand(time(NULL));
        int i = 1 + rand() % (n - 2);
        int j = 1 + rand() % (n - 2);
        if (area[i][j] != 36 && area[i][j] != 38 && area[i][j] != 49 && area[i][j] != 50 && area[i][j] != 101) {
            area[i][j] = 101;
            gameData[1] = gameData[1] + 1;
            gameData[0] = gameData[0] - 1;
        }
    }
}

void generatePositionSnakes(int n, int area[][n], int positionSnakes[]) {
    int i1 = 1 + rand() % (n - 2), j1 = 1 + rand() % (n - 2);
    int i2 = 1 + rand() % (n - 2), j2 = 1 + rand() % (n - 2);
    area[i1][j2] = 49;
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
}


void showHelloMessage() {
    system("cls");
    printf("Добро пожаловать в Змейку!!!\n");
    printf("Краткий гайд:\n");
    printf("Размер поля может быть от 3x3 до 10x10\n");
    printf("Голова первой змейки обозначается 1, второй 2\n");
    printf("Хвост первой змейки обозначается $, второй &\n");
    printf("Первая змейка ходит на стрелочки, вторая на WASD\n");
    printf("Еда выглядит - e\n");
    printf("Стенки - #\n");
}

void printSymbol(short numberSymbol) {
    switch (numberSymbol) {
        case 36:
            printf("$");
            break;
        case 38:
            printf("&");
            break;
        case 35:
            printf("#");
            break;
        case 49:
            printf("1");
            break;
        case 50:
            printf("2");
            break;
        case 101:
            printf("e");
            break;
        default:
            printf(" ");
    }
}


long validationGameArea() {
    long result;
    short minArea = 3, maxArea = 10;
    do {
        result = validation();
        if (result > maxArea || result < minArea)
            printf("Неверный ввод размера поля! Размер поля может принимать значения от %hd до %hd\n", minArea,
                   maxArea);
    } while (result > maxArea || result < minArea);
    return result;
}

bool checkOverflow(double d) {
    return d >= -2147483648 && d <= 2147483647;
}
