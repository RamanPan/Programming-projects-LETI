#include <stdbool.h>

#ifndef SNAKEGAME_FUNCTIONALITY_H
#define SNAKEGAME_FUNCTIONALITY_H

long validation();

long validationGameArea();

void showMenu(int n,int m, int gameData[], int area[][m]);

void fillingArea(int n, int m, int area[][m]);

void generateFood(int n, int m, int gameData[], int area[][m], int pointFood[]);

void preparationForGenerateWalls(int n, int m, int area[][m], int gameData[]);

void generateWalls(int n, int m, int area[][m], int gameData[]);

void generatePositionSnakes(int n, int m, int area[][m], int positionSnakes[], int gameData[]);

void showHelloMessage();

void cleanArea(int n, int m, int area[][m]);

void determineThePosition(const int gameData[], const int endTailFirstSnake[], const int endTailSecondSnake[],
                          int allTailFirstSnake[], int allTailSecondSnake[], bool whichSnake);

bool
snakeMotion(int n, int m, int area[][m], int gameData[], int positionSnakes[], int endTailFirstSnake[],
            int endTailSecondSnake[], int allTailFirstSnake[], int allTailSecondSnake[], int pointFood[],
            short orientation, bool whichSnake);

void tailMotion(int n, int m, int area[][m], int gameData[], const int positionSnakes[], int tailFirstSnake[],
                int tailSecondSnake[], int pointFood[],
                short orientation, bool whichSnake);

void printSymbol(short numberSymbol);

void choosePointForNewPieceOfTail(int n, int m, int area[][m], int endTailFirstSnake[],
                                  int endTailSecondSnake[], short orientation, bool whichSnake);

void checkTail(int n, int m, int N, int area[][m], const int tailSnake[], bool whichSnake);

void checkPointFood(int n, int m, int area[][m], int gameData[], int pointFood[]);

void findPointFood(int gameData[], int pointFood[], int y, int x);

bool checkForMove(int n, int m, int area[][m], int x, int y);

bool checkOverflow(double d);

bool checkLose(int n, int m, int area[][m], int x, int y);

#endif //SNAKEGAME_FUNCTIONALITY_H
