#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "functionality.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    bool exitFlag = false;
    while (!exitFlag) {
        srand(time(NULL));
        showHelloMessage();
        bool startAgain = false;
        printf("Введите размерность поля\n");
        const long n = validationGameArea() + 2;
        int gameArea[n][n], positionSnakes[3];
        //0 - кол-во свободных клеток, 1 - кол-во еды, 2 - длина первой змейки, 3 - длина второй змейки
        int gameData[4] = {(n - 2) * (n - 2) - 2, 0, 1, 1};
        int symbol;
        char YN;
        bool winFirst = false, winSecond = false;
        fillingArea(n, gameArea);
        generatePositionSnakes(n, gameArea, positionSnakes);
        generateFood(n, gameData, gameArea);
        while (!startAgain) {
            showMenu(n, gameData, gameArea);
            symbol = getch();
            if (symbol == 224) symbol = getch();
            switch (symbol) {
                //верхняя стрелочка
                case 72:
                    winSecond = snakeMotion(n, gameArea, gameData, positionSnakes, 0, false);
                    break;
                    //нижняя стрелочка
                case 80:
                    winSecond = snakeMotion(n, gameArea, gameData, positionSnakes, 1, false);
                    break;
                    //левая стрелочка
                case 75:
                    winSecond = snakeMotion(n, gameArea, gameData, positionSnakes, 2, false);
                    break;
                    // правая стрелочка
                case 77:
                    winSecond = snakeMotion(n, gameArea, gameData, positionSnakes, 3, false);
                    break;
                    //W
                case 119:
                    winFirst = snakeMotion(n, gameArea, gameData, positionSnakes, 0, true);
                    break;
                    //S
                case 115:
                    winFirst = snakeMotion(n, gameArea, gameData, positionSnakes, 1, true);
                    break;
                    //A
                case 97:
                    winFirst = snakeMotion(n, gameArea, gameData, positionSnakes, 2, true);
                    break;
                    //D
                case 100:
                    winFirst = snakeMotion(n, gameArea, gameData, positionSnakes, 3, true);
                    break;
                case 27:
                    printf("Вы уверены что хотите выйти?(Y/N)\n");
                    scanf("%s", &YN);
                    if (YN == 'Y') return 0;
                    break;
            }
            if (winFirst) {
                printf("Первая змейка победила!\n");
                printf("Поздравляем с победой!\n");
            }
            if (winSecond) {
                printf("Вторая змейка победила!\n");
                printf("Поздравляем с победой!\n");
            }
            if (winFirst || winSecond) {
                printf("Хотите сыграть ещё раз?(Y/N)\n");
                scanf("%s", &YN);
                startAgain = true;
                if (YN == 'Y') {}
                else exitFlag = true;
            }
        }
    }
    printf("Не забывайте иногда играть снова!");
    return 0;
}
