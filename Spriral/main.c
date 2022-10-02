#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

int main() {
    bool exitFlag = false;
    int I, J;
    short symbol;
    short minPosition = 1, maxPosition = 10;
    short position = minPosition;
    char YN;
    while (!exitFlag) {
        symbol = getch();
        if (symbol == 224) symbol = getch();
        switch (symbol) {
            case 72:
                if (0 != position - 1)
                    position--;
                else position = maxPosition;
                break;
            case 80:
                if (position < maxPosition) position++;
                else
                    position = minPosition;
                break;
            case 27:
                printf("Вы уверены что хотите выйти?(Y/N)\n");
                scanf("%s", &YN);
                if (YN == 'Y') exitFlag = true;
                break;
            case 49:
                position = 1;
                break;
            case 50:
                position = 2;
                break;
            case 51:
                position = 3;
                break;
            case 52:
                position = 4;
                break;
            case 53:
                position = 5;
                break;
            case 54:
                position = 6;
                break;
            case 55:
                position = 7;
                break;
            case 56:
                position = 8;
                break;
            case 57:
                position = 9;
                break;
            default:;
        }
        switch (position) {

        }
    }
}
