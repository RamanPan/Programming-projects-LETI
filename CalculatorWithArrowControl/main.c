#include <stdio.h>
#include "functionality.h"
#include <stdbool.h>
#include <conio.h>

int main() {
    long firstValue;
    long secondValue;
    int power;
    short minPosition = 1, maxPosition = 10;
    short position = minPosition;
    int symbol;
    char YN;
    long swap;
    bool exitFlag = false;
    bool permissionFlag;
    printf("Welcome to Calculator!\n");
    printf("Enter first number\n");
    firstValue = validation();
    printf("Enter second number\n");
    secondValue = validation();
    showMenu(position, firstValue, secondValue);
    while (!exitFlag) {
        permissionFlag = false;
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
                scanf("%s", &YN);
                if (YN == 'Y') exitFlag = true;
                break;
            case 13:
                permissionFlag = true;
                break;
            case 48:
                position = 10;
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
        showMenu(position, firstValue, secondValue);
        if (permissionFlag) {
            switch (position) {
                case 1:
                    printf("Result = %ld\n", add(firstValue, secondValue));
                    break;
                case 2:
                    printf("Result = %ld\n", multiply(firstValue, secondValue));
                    break;
                case 3:
                    printf("Result = %ld\n", subtraction(firstValue, secondValue));
                    break;
                case 4:
                    if (validationForDivide(secondValue))
                        printf("Result = %ld\n", division(firstValue, secondValue));
                    break;
                case 5:
                    printf("Enter the power\n");
                    power = validation();
                    exponentiation(firstValue, power);
                    break;
                case 6:
                    if (validationForRoot(firstValue)) {
                        printf("Enter the power root\n");
                        power = validation();
                        if (power <= 0) {
                            printf("Wrong power! Power less or equals zero! Try again");
                            break;
                        }
                        rooting(firstValue, power);
                    } else printf("Wrong value! Value less then zero! Change it and try again");
                    break;
                case 7:
                    printf("Enter the number for change\n");
                    firstValue = validation();
                    showMenu(position, firstValue, secondValue);
                    printf("First value changed\n");
                    break;
                case 8:
                    printf("Enter the number for change\n");
                    secondValue = validation();
                    showMenu(position, firstValue, secondValue);
                    printf("Second value changed\n");
                    break;
                case 9:
                    swap = firstValue;
                    firstValue = secondValue;
                    secondValue = swap;
                    showMenu(position, firstValue, secondValue);
                    printf("Values was changed successfully");
                    break;
                case 10:
                    printf("Are you sure you wanna exit?(Y/N)\n");
                    scanf("%s", &YN);
                    if (YN == 'Y') exitFlag = true;
                    break;
                default:
                    break;
            }
        }
    }
    printf("See you soon!");
    return 0;
}
