#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "functionality.h"
#include "functionality.h"

long validation() {
    bool validationFlag = false;
    double result;
    while (!validationFlag) {
        if (scanf("%lf", &result)) {
            if (!checkOverflow(result)) {
                printf("Неправильный ввод! Число вышло за границу дозволенного! Попробуйте снова!\n");
            } else validationFlag = true;
        } else printf("Неправильный ввод! Попробуйте снова!\n");
        fflush(stdin);
    }
    return (long) result;
}

long validationGameArea() {
    long result;
    short minArea = 2, maxArea = 14;
    do {
        result = validation();
        if (result > maxArea || result < minArea)
            printf("Неверный ввод размера поля! Размер поля может принимать значения от %hd до %hd\n", minArea,
                   maxArea);
    } while (result > maxArea || result < minArea);
    return result;
}

long validationWithArgument(short max) {
    long result;
    short minArea = 2, maxArea = max;
    do {
        result = validation();
        if (result > maxArea || result < minArea)
            printf("Неверный ввод размера поля! Размер поля может принимать значения от %hd до %hd\n", minArea,
                   maxArea);
    } while (result > maxArea || result < minArea);
    return result;
}

void moveCursor(int m, int area[][m], int positionCursor[], short orientation) {
    bool checkForMoves = checkForMove(m, area, positionCursor[1], positionCursor[0]);
    switch (orientation) {
        case 0:
            if (area[positionCursor[0] - 1][positionCursor[1]] == 35) break;
            if (!checkForMoves) area[positionCursor[0]][positionCursor[1]] = 0;
            else if (area[positionCursor[0]][positionCursor[1]] == 881) area[positionCursor[0]][positionCursor[1]] = 88;
            else if (area[positionCursor[0]][positionCursor[1]] == 791) area[positionCursor[0]][positionCursor[1]] = 79;
            if (!checkForMove(m, area, positionCursor[1], positionCursor[0] - 1)) {
                positionCursor[0]--;
                area[positionCursor[0]][positionCursor[1]] = 149;
            } else if (area[positionCursor[0] - 1][positionCursor[1]] == 88) {
                positionCursor[0]--;
                area[positionCursor[0]][positionCursor[1]] = 881;
            } else if (area[positionCursor[0] - 1][positionCursor[1]] == 79) {
                positionCursor[0]--;
                area[positionCursor[0]][positionCursor[1]] = 791;
            } else if (checkForMoves) area[positionCursor[0]][positionCursor[1]] = 149;
            break;
        case 1:
            if (area[positionCursor[0] + 1][positionCursor[1]] == 35) break;
            if (!checkForMoves) area[positionCursor[0]][positionCursor[1]] = 0;
            else if (area[positionCursor[0]][positionCursor[1]] == 881) area[positionCursor[0]][positionCursor[1]] = 88;
            else if (area[positionCursor[0]][positionCursor[1]] == 791) area[positionCursor[0]][positionCursor[1]] = 79;
            if (!checkForMove(m, area, positionCursor[1], positionCursor[0] + 1)) {
                positionCursor[0]++;
                area[positionCursor[0]][positionCursor[1]] = 149;
            } else if (area[positionCursor[0] + 1][positionCursor[1]] == 88) {
                positionCursor[0]++;
                area[positionCursor[0]][positionCursor[1]] = 881;
            } else if (area[positionCursor[0] + 1][positionCursor[1]] == 79) {
                positionCursor[0]++;
                area[positionCursor[0]][positionCursor[1]] = 791;
            } else if (checkForMoves) area[positionCursor[0]][positionCursor[1]] = 149;
            break;
        case 2:
            if (area[positionCursor[0]][positionCursor[1] - 1] == 35) break;
            if (!checkForMoves) area[positionCursor[0]][positionCursor[1]] = 0;
            else if (area[positionCursor[0]][positionCursor[1]] == 881) area[positionCursor[0]][positionCursor[1]] = 88;
            else if (area[positionCursor[0]][positionCursor[1]] == 791) area[positionCursor[0]][positionCursor[1]] = 79;
            if (!checkForMove(m, area, positionCursor[1] - 1, positionCursor[0])) {
                positionCursor[1]--;
                area[positionCursor[0]][positionCursor[1]] = 149;
            } else if (area[positionCursor[0]][positionCursor[1] - 1] == 88) {
                positionCursor[1]--;
                area[positionCursor[0]][positionCursor[1]] = 881;
            } else if (area[positionCursor[0]][positionCursor[1] - 1] == 79) {
                positionCursor[1]--;
                area[positionCursor[0]][positionCursor[1]] = 791;
            } else if (checkForMoves) area[positionCursor[0]][positionCursor[1]] = 149;
            break;
        case 3:
            if (area[positionCursor[0]][positionCursor[1] + 1] == 35) break;
            if (!checkForMoves) area[positionCursor[0]][positionCursor[1]] = 0;
            else if (area[positionCursor[0]][positionCursor[1]] == 881) area[positionCursor[0]][positionCursor[1]] = 88;
            else if (area[positionCursor[0]][positionCursor[1]] == 791) area[positionCursor[0]][positionCursor[1]] = 79;
            if (!checkForMove(m, area, positionCursor[1] + 1, positionCursor[0])) {
                positionCursor[1]++;
                area[positionCursor[0]][positionCursor[1]] = 149;
            } else if (area[positionCursor[0]][positionCursor[1] + 1] == 88) {
                positionCursor[1]++;
                area[positionCursor[0]][positionCursor[1]] = 881;
            } else if (area[positionCursor[0]][positionCursor[1] + 1] == 79) {
                positionCursor[1]++;
                area[positionCursor[0]][positionCursor[1]] = 791;
            } else if (checkForMoves) area[positionCursor[0]][positionCursor[1]] = 149;
            break;
        default:;
    }
}

bool setXorO(int m, int area[][m], int gameData[], int positionCursor[], int positionX[], int positionO[],
             bool whoseStep) {
    if (!checkForMove(m, area, positionCursor[1], positionCursor[0])) {
        if (!whoseStep) {
            area[positionCursor[0]][positionCursor[1]] = 881;
            positionX[gameData[1] + gameData[1]] = positionCursor[0];
            positionX[gameData[1] + gameData[1] + 1] = positionCursor[1];
            gameData[1]++;
            gameData[0]--;
        } else {
            area[positionCursor[0]][positionCursor[1]] = 791;
            positionO[gameData[2] + gameData[2]] = positionCursor[0];
            positionO[gameData[2] + gameData[2] + 1] = positionCursor[1];
            gameData[2]++;
            gameData[0]--;
        }
        return !whoseStep;
    }
    return whoseStep;
}

void showHelloMessage() {
    printf("Приветствую!\n");
    printf("Это игра 'Крестики и нолики'\n");
    printf("Перед игрой вам нужно ввести высоту и ширину игрового поля\n");
    printf("Затем выбрать кол-во очков для победы крестиков и для победы ноликов\n");
    printf("Очки для победы не могут быть больше чем высота и ширина поля\n");
    printf("Если на поле не осталось места - игра завершается ничьей\n");
}

void fillingArea(int n, int m, int area[][m]) {
    for (int i = 0; i < n; ++i) {
        area[i][0] = '#';
        area[i][m - 1] = '#';
    }
    for (int j = 0; j < m; ++j) {
        area[0][j] = '#';
        area[n - 1][j] = '#';
    }
}

void cleanArea(int n, int m, int area[][m]) {
    for (int i = 1; i < n - 1; i++)
        for (int j = 1; j < m - 1; j++)
            area[i][j] = 0;
    area[1][1] = 149;
}

bool checkOverflow(double d) {
    return d >= -2147483648 && d <= 2147483647;
}