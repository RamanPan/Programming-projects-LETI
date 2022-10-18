#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "functionality.h"
#include "windows.h"

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

long validationGameArea() {
    long result;
    short minArea = 2, maxArea = 14;
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

long validationWithArgument(short max) {
    long result;
    short minArea = 2, maxArea = max;
    do {
        result = validation();
        if (result > maxArea || result < minArea) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Неверный ввод размера поля! Очки для победы могут принимать значения от %hd до %hd\n", minArea,
                   maxArea);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
    } while (result > maxArea || result < minArea);
    return result;
}

void showHelloMessage() {
    system("cls");
    printf("Приветствую!\n");
    printf("Это игра 'Крестики и нолики'\n");
    printf("Перед игрой вам нужно ввести высоту и ширину игрового поля\n");
    printf("Затем выбрать кол-во очков для победы крестиков и для победы ноликов\n");
    printf("Очки для победы не могут быть больше чем высота и ширина поля\n");
    printf("Выигрышная лииня выделяется ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    printf("зелёным\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    printf("Если на поле не осталось места - игра завершается ничьей\n");
}

bool checkWin(int m, int area[][m], int positionCursor[], int statementForWin, bool XorO) {
    short symbol = XorO ? 79 : 88;
    int i = positionCursor[0], j = positionCursor[1];
    if (area[i][j] == 791) if (symbol != 79) return false;
    if (area[i][j] == 881) if (symbol != 88) return false;
    short shift = 1;
    short quantityElements = (short) ((statementForWin - 1) * 2);
    int diagWin[quantityElements], reverseDiagWin[quantityElements], horizontalWin[quantityElements], verticalWin[quantityElements];
    bool win = false, exitFlag = false;
    int counterDiagonal = 1, counterReverseDiagonal = 1, counterHorizontal = 1, counterVertical = 1;
    bool diagonalUp = true, diagonalDown = true, reverseDiagonalUp = true, reverseDiagonalDown = true,
            horizontalUp = true, horizontalDown = true, verticalUp = true, verticalDown = true;
    while (!exitFlag) {
        if (diagonalUp && area[i - shift][j - shift] == symbol) {
            diagWin[(counterDiagonal - 1) + (counterDiagonal - 1)] = i - shift;
            diagWin[(counterDiagonal - 1) + (counterDiagonal - 1) + 1] = j - shift;
            counterDiagonal++;
        } else diagonalUp = false;
        if (diagonalDown && area[i + shift][j + shift] == symbol) {
            diagWin[(counterDiagonal - 1) + (counterDiagonal - 1)] = i + shift;
            diagWin[(counterDiagonal - 1) + (counterDiagonal - 1) + 1] = j + shift;
            counterDiagonal++;
        } else diagonalDown = false;
        if (reverseDiagonalUp && area[i - shift][j + shift] == symbol) {
            reverseDiagWin[(counterReverseDiagonal - 1) + (counterReverseDiagonal - 1)] = i - shift;
            reverseDiagWin[(counterReverseDiagonal - 1) + (counterReverseDiagonal - 1) + 1] = j + shift;
            counterReverseDiagonal++;
        } else reverseDiagonalUp = false;
        if (reverseDiagonalDown && area[i + shift][j - shift] == symbol) {
            reverseDiagWin[(counterReverseDiagonal - 1) + (counterReverseDiagonal - 1)] = i + shift;
            reverseDiagWin[(counterReverseDiagonal - 1) + (counterReverseDiagonal - 1) + 1] = j - shift;
            counterReverseDiagonal++;
        } else reverseDiagonalDown = false;
        if (horizontalUp && area[i][j - shift] == symbol) {
            horizontalWin[(counterHorizontal - 1) + (counterHorizontal - 1)] = i;
            horizontalWin[(counterHorizontal - 1) + (counterHorizontal - 1) + 1] = j - shift;
            counterHorizontal++;
        } else horizontalUp = false;
        if (horizontalDown && area[i][j + shift] == symbol) {
            horizontalWin[(counterHorizontal - 1) + (counterHorizontal - 1)] = i;
            horizontalWin[(counterHorizontal - 1) + (counterHorizontal - 1) + 1] = j + shift;
            counterHorizontal++;
        } else horizontalDown = false;
        if (verticalUp && area[i - shift][j] == symbol) {
            verticalWin[(counterVertical - 1) + (counterVertical - 1)] = i - shift;
            verticalWin[(counterVertical - 1) + (counterVertical - 1) + 1] = j;
            counterVertical++;
        } else verticalUp = false;
        if (verticalDown && area[i + shift][j] == symbol) {
            verticalWin[(counterVertical - 1) + (counterVertical - 1)] = i + shift;
            verticalWin[(counterVertical - 1) + (counterVertical - 1) + 1] = j;
            counterVertical++;
        } else verticalDown = false;
        if (!diagonalUp && !diagonalDown && !reverseDiagonalUp && !reverseDiagonalDown
            && !horizontalUp && !horizontalDown && !verticalUp && !verticalDown)
            exitFlag = true;
        if (counterDiagonal == statementForWin) {
            exitFlag = true;
            win = true;
            drawWinLine(m, area, quantityElements, diagWin, symbol);
        } else if (counterReverseDiagonal == statementForWin) {
            exitFlag = true;
            win = true;
            drawWinLine(m, area, quantityElements, reverseDiagWin, symbol);
        } else if (counterHorizontal == statementForWin) {
            exitFlag = true;
            win = true;
            drawWinLine(m, area, quantityElements, horizontalWin, symbol);
        } else if (counterVertical == statementForWin) {
            exitFlag = true;
            win = true;
            drawWinLine(m, area, quantityElements, verticalWin, symbol);
        }
        ++shift;
    }
    return win;
}

void drawWinLine(int m, int area[][m], int size, int positionWinPoints[], short symbol) {
    short s = (symbol == 79) ? 791 : 881;
    for (int i = 0; i < size; i += 2)
        area[positionWinPoints[i]][positionWinPoints[i + 1]] = s;

}

void printSymbol(short numberSymbol) {
    switch (numberSymbol) {
        case 35:
            printf("#");
            break;
        case 88:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
            printf("X");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case 881:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("X");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case 79:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
            printf("O");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case 791:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("O");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        case 149:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("•");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            break;
        default:
            printf(" ");
    }
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

bool setXorO(int m, int area[][m], int gameData[], int positionCursor[], bool whoseStep) {
    if (!checkForMove(m, area, positionCursor[1], positionCursor[0])) {
        if (!whoseStep) {
            area[positionCursor[0]][positionCursor[1]] = 881;
            gameData[1]++;
            gameData[0]--;
        } else {
            area[positionCursor[0]][positionCursor[1]] = 791;
            gameData[2]++;
            gameData[0]--;
        }
        return !whoseStep;
    }
    return whoseStep;
}

void showMenu(int n, int m, int gameData[], int area[][m], int pointsForWinX, int pointsForWinO, bool XorO) {
    system("cls");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            printSymbol((short) area[i][j]);
            if (j == m - 1) printf("\n");
        }
    if (XorO) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        printf("ХОД НОЛИКОВ\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        printf("ХОД КРЕСТИКОВ\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    }
    printf("Размер поля: %dx%d\n", n - 2, m - 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("Кол-во очков для победы X: %d\n", pointsForWinX);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    printf("Кол-во очков для победы 0: %d\n", pointsForWinO);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    printf("Кол-во свободных клеток: %d\n", gameData[0]);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
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

bool checkForMove(int m, int area[][m], int x, int y) {
    int value = area[y][x];
    return value == 35 || value == 88 || value == 79 || value == 881 || value == 791;
}

bool checkOverflow(double d) {
    return d >= -2147483648 && d <= 2147483647;
}