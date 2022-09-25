#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "functionality.h"
int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    showHelloMessage();
    printf("Введите размерность поля\n");
    const long n = validationGameArea() + 1;
    int gameArea[n][n],positionSnakes[3];
    //0 - кол-во свободных клеток, 1 - кол-во еды, 2 - длина первой змейки, 3 - длина второй змейки
    int gameData[4] = {n*n-2,0,1,1};
    bool gameOver = false, winFirst = false, winSecond = false;
    fillingArea(n,gameArea);
    generatePositionSnakes(n,gameArea,positionSnakes);
//    while(!gameOver)
    showMenu(n,gameArea);
    return 0;
}
