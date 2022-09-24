#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "functionality.h"
int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    showHelloMessage();
    printf("Введите размерность поля\n");
    const long n = validationGameArea();
    int gameArea[n][n],positionSnakes[3];
    return 0;
}
