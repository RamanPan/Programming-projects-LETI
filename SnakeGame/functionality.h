#include <stdbool.h>

#ifndef SNAKEGAME_FUNCTIONALITY_H
#define SNAKEGAME_FUNCTIONALITY_H

long validation();

long validationGameArea();

void showMenu(int n, int gameData[], int area[][n], int pointsForWin);

void fillingArea(int n, int area[][n]);

void generateFood(int n, int gameData[], int area[][n], int pointFood[]);

void preparationForGenerateWalls(int n, int area[][n], int gameData[]);

void generateWalls(int n, int area[][n], int gameData[]);

void generatePositionSnakes(int n, int area[][n], int positionSnakes[], int gameData[]);

void showHelloMessage();

void cleanArea(int n, int area[][n]);

void determineThePosition(const int gameData[], const int endTailFirstSnake[], const int endTailSecondSnake[],
                          int allTailFirstSnake[], int allTailSecondSnake[], bool whichSnake);

bool
snakeMotion(int n, int area[][n], int gameData[], int positionSnakes[], int endTailFirstSnake[],
            int endTailSecondSnake[], int allTailFirstSnake[], int allTailSecondSnake[], int pointFood[],
            short orientation, bool whichSnake);

void tailMotion(int n, int area[][n], int gameData[], const int positionSnakes[], int tailFirstSnake[],
                int tailSecondSnake[], int pointFood[],
                short orientation, bool whichSnake);

void printSymbol(short numberSymbol);

void choosePointForNewPieceOfTail(int n, int area[][n], int endTailFirstSnake[],
                                  int endTailSecondSnake[], short orientation, bool whichSnake);

void checkTail(int n, int N, int area[][n], const int tailSnake[], bool whichSnake);

void checkPointFood(int n, int area[][n], int gameData[], int pointFood[]);

void findPointFood(int gameData[], int pointFood[], int y, int x);

bool checkForMove(int n, int area[][n], int x, int y);

bool checkOverflow(double d);

bool checkLose(int n, int area[][n], int x, int y);

#endif //SNAKEGAME_FUNCTIONALITY_H
