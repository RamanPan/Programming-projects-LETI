#ifndef TIC_TAC_TOE_FUNCTIONALITY_H
#define TIC_TAC_TOE_FUNCTIONALITY_H

void showHelloMessage();

long validation();

long validationGameArea();

long validationWithArgument(short max);

bool checkOverflow(double d);

void cleanArea(int n, int m, int area[][m]);

void moveCursor(int m, int area[][m], int positionCursor[], short orientation);

bool setXorO(int m, int area[][m], int gameData[], int positionCursor[], int positionX[], int positionO[],
             bool whoseStep);

void fillingArea(int n, int m, int area[n][m]);

void printSymbol(short numberSymbol);

void showMenu(int n, int m, int gameData[], int area[][m], int pointsForWinX, int pointsForWin0, bool XorO);

bool checkWin(int m, int area[][m], int statementForWin, bool XorO);

bool checkForMove(int n, int area[][n], int x, int y);

#endif //TIC_TAC_TOE_FUNCTIONALITY_H