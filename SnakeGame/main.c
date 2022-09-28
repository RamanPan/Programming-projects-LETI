#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "functionality.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    showHelloMessage();
    printf("Введите размерность поля\n");
    const long n = validationGameArea() + 2;
    int gameArea[n][n], positionSnakes[3];
    //0 - кол-во свободных клеток, 1 - кол-во еды, 2 - длина первой змейки, 3 - длина второй змейки
    int gameData[4] = {(n-2) * (n-2) - 2, 0, 1, 1};
    short symbol;
    bool gameOver = false, winFirst = false, winSecond = false;
    fillingArea(n, gameArea);
    generatePositionSnakes(n, gameArea, positionSnakes);
    generateFood(n, gameData, gameArea);
    while (!gameOver) {
        showMenu(n, gameData, gameArea);
        symbol = getch();
        if (symbol == 224) symbol = getch();
        switch (symbol) {
            //верхняя стрелочка
            case 72:

                break;
                //нижняя стрелочка
            case 80:
                break;
                // правая стрелочка
            case 77:

                break;
                //левая стрелочка
            case 75:
                break;
                //A
            case 65:
                break;
                //D
            case 68:
                break;
                //W
            case 87:
                break;
                //S
            case 83:
                break;
        }
    }
    return 0;
}
