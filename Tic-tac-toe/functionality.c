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

bool checkWin(int m, int area[][m], int positionCursor[], int statementForWin, bool XorO) {
    short symbol = XorO ? 79 : 88;
    int i = positionCursor[0], j = positionCursor[1];
    if (area[i][j] == 791) if (symbol != 79) return false;
    if (area[i][j] == 881) if (symbol != 88) return false;
    short shift = 1;
    bool win = false, exitFlag = false;
    int counterDiagonal = 1, counterReverseDiagonal = 1, counterHorizontal = 1, counterVertical = 1;
    bool diagonalUp = true, diagonalDown = true, reverseDiagonalUp = true, reverseDiagonalDown = true,
            horizontalUp = true, horizontalDown = true, verticalUp = true, verticalDown = true;
    while (!exitFlag) {
        if (diagonalUp && area[i - shift][j - shift] == symbol) {
            counterDiagonal++;
        } else diagonalUp = false;
        if (diagonalDown && area[i + shift][j + shift] == symbol) {
            counterDiagonal++;
        } else diagonalDown = false;
        if (reverseDiagonalUp && area[i - shift][j + shift] == symbol) {
            counterReverseDiagonal++;
        } else reverseDiagonalUp = false;
        if (reverseDiagonalDown && area[i + shift][j - shift] == symbol) {
            counterReverseDiagonal++;
        } else reverseDiagonalDown = false;
        if (horizontalUp && area[i][j - shift] == symbol) {
            counterHorizontal++;
        } else horizontalUp = false;
        if (horizontalDown && area[i][j + shift] == symbol) {
            counterHorizontal++;
        } else horizontalDown = false;
        if (verticalUp && area[i - shift][j] == symbol) {
            counterVertical++;
        } else verticalUp = false;
        if (verticalDown && area[i + shift][j] == symbol) {
            counterVertical++;
        } else verticalDown = false;
        if (!diagonalUp && !diagonalDown && !reverseDiagonalUp && !reverseDiagonalDown
            && !horizontalUp && !horizontalDown && !verticalUp && !verticalDown)
            exitFlag = true;
        if (counterDiagonal == statementForWin || counterReverseDiagonal == statementForWin ||
            counterHorizontal == statementForWin || counterVertical == statementForWin) {
            exitFlag = true;
            win = true;
        }
        ++shift;
    }
    return win;
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
void printSymbol(short numberSymbol) {
    switch (numberSymbol) {
        case 35:
            printf("#");
            break;
        case 88:
            printf("X");
            break;
        case 881:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("X");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
            break;
        case 79:
            printf("O");
            break;
        case 791:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("O");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
            break;
        case 149:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("•");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
            break;
        default:
            printf(" ");
    }
}

void showMenu(int n, int m, int gameData[], int area[][m], int pointsForWinX, int pointsForWinO, bool XorO) {
    system("cls");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            printSymbol((short) area[i][j]);
            if (j == m - 1) printf("\n");
        }
    if (XorO) printf("ХОД НОЛИКОВ\n");
    else printf("ХОД КРЕСТИКОВ\n");
    printf("Размер поля: %dx%d\n", n - 2, m - 2);
    printf("Кол-во очков для победы X: %d\n", pointsForWinX);
    printf("Кол-во очков для победы 0: %d\n", pointsForWinO);
    printf("Кол-во свободных клеток: %d\n", gameData[0]);
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

bool checkForMove(int m, int area[][m], int x, int y) {
    int value = area[y][x];
    return value == 35 || value == 88 || value == 79 || value == 881 || value == 791;
}