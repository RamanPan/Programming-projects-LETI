#include <stdio.h>
#include "functionality.h"
#include <windows.h>
#include <stdbool.h>

int main() {
    long firstValue;
    long secondValue;
    int power;
    short position = 1;
    short maxPosition = 8;
    bool exitFlag = false;
    printf("Welcome to Calculator without shit\n");
    printf("Enter the number\n");
    firstValue = validation();
    showMenu(position);
    while (!exitFlag) {
        if (GetAsyncKeyState(VK_UP)) {
            keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);//Отжимаем кнопку
            if (0 != position - 1)
                position--;
            else
                position = maxPosition;
            showMenu(position);
        }
        if (GetAsyncKeyState(VK_DOWN)) {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
            if (position < maxPosition)
                position++;
            else
                position = 1;
            showMenu(position);
        }
        if (GetAsyncKeyState(VK_LCONTROL)) {
            keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
            switch (position) {
                case 1:
                    printf("Enter the second number for '+'\n");
                    secondValue = validation();
                    firstValue = add(firstValue, secondValue);
                    printf("Result = %ld\n", firstValue);
                    break;
                case 2:
                    printf("Enter the second number for '*'\n");
                    secondValue = validation();
                    firstValue = multiply(firstValue, secondValue);
                    printf("Result = %ld\n", firstValue);
                    break;
                case 3:
                    printf("Enter the second number for '-'\n");
                    secondValue = validation();
                    firstValue = subtraction(firstValue, secondValue);
                    printf("Result = %ld\n", firstValue);
                    break;
                case 4:
                    printf("Enter the second number for '/'\n");
                    secondValue = validationForDivide();
                    firstValue = division(firstValue, secondValue);
                    printf("Result = %ld\n", firstValue);
                    break;
                case 5:
                    printf("Enter the power\n");
                    power = validation();
                    firstValue = (long) exponentiation(firstValue, power);
                    printf("Result = %ld\n", firstValue);
                    break;
                case 6:
                    if (validationForRoot(firstValue)) {
                        printf("Enter the power root\n");
                        power = validation();
                        firstValue = (long) rooting(firstValue, power);
                        printf("Result = %ld\n", firstValue);
                    } else printf("Wrong value! Value less then zero! Change it and try again");
                    break;
                case 7:
                    printf("Enter the number\n");
                    firstValue = validation();
                    printf("Result = %ld\n", firstValue);
                    break;
                case 8:
                    printf("Are you sure you wanna exit?(Y/N)\n");
                    char YN;
                    scanf("%s", &YN);
                    if (YN == 'Y') exitFlag = true;
                    break;
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE)) {
            keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);
            printf("See you soon!");
            return 0;
        }
    }
    printf("See you soon!");
    return 0;
}

