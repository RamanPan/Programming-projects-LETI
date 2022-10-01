#include <stdbool.h>

#ifndef SNAKEGAME_FUNCTIONALITY_H
#define SNAKEGAME_FUNCTIONALITY_H

long validation();

long validationGameArea();

void showMenu(int n, int gameData[], int area[][n]);

void fillingArea(int n, int area[][n]);

void generateFood(int n, int gameData[], int area[][n]);

void generatePositionSnakes(int n, int area[][n], int positionSnakes[]);

void showHelloMessage();

bool
snakeMotion(int n, int area[][n], int gameData[], int positionSnakes[], int endTailFirstSnake[], int endTailSecondSnake[],
            short orientation, bool whichSnake);

void tailMotion(int n, int area[][n], int gameData[], int positionSnakes[], int tailFirstSnake[], int tailSecondSnake[],
                short orientation, bool whichSnake);

void printSymbol(short numberSymbol);

bool checkOverflow(double d);

bool checkLose(int n, int area[][n], int x, int y);

#endif //SNAKEGAME_FUNCTIONALITY_H
