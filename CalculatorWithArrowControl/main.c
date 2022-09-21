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
    bool permissionToInput = false;
    bool permissionToChoice = false;
    printf("Welcome to Calculator without shit\n");
    printf("Enter the number\n");
    firstValue = validation();
    showMenu(position);
    while (!exitFlag) {
        if (GetAsyncKeyState(VK_UP) && permissionToInput) {
            keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);//Отжимаем кнопку
            if (0 != position - 1)
                position--;
            else
                position = maxPosition;
            showMenu(position);
        }
        if (GetAsyncKeyState(VK_DOWN) && permissionToInput) {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
            if (position < maxPosition)
                position++;
            else
                position = 1;
            showMenu(position);
        }
        permissionToInput = true;
        if (GetAsyncKeyState(VK_LCONTROL) && permissionToChoice) {
            keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
            switch (position) {
                case 1:
                    printf("Enter the second number for '+'\n");
                    secondValue = validation();
                    permissionToInput = false;
                    firstValue = add(firstValue, secondValue);
                    printf("Result = %ld\n", firstValue);
                    break;
                case 2:
                    printf("Enter the second number for '*'\n");
                    secondValue = validation();
                    permissionToInput = false;
                    firstValue = multiply(firstValue, secondValue);
                    printf("Result = %ld\n", firstValue);
                    break;
                case 3:
                    printf("Enter the second number for '-'\n");
                    secondValue = validation();
                    permissionToInput = false;
                    firstValue = subtraction(firstValue, secondValue);
                    printf("Result = %ld\n", firstValue);
                    break;
                case 4:
                    printf("Enter the second number for '/'\n");
                    secondValue = validationForDivide();
                    permissionToInput = false;
                    firstValue = division(firstValue, secondValue);
                    break;
                case 5:
                    printf("Enter the power\n");
                    power = validation();
                    permissionToInput = false;
                    firstValue = (long) exponentiation(firstValue, power);
                    break;
                case 6:
                    if (validationForRoot(firstValue)) {
                        printf("Enter the power root\n");
                        power = validation();
                        permissionToInput = false;
                        firstValue = (long) rooting(firstValue, power);
                    } else printf("Wrong value! Value less then zero! Change it and try again");
                    break;
                case 7:
                    printf("Enter the number\n");
                    firstValue = validation();
                    permissionToInput = false;
                    printf("Result = %ld\n", firstValue);
                    break;
                case 8:
                    printf("Are you sure you wanna exit?(Y/N)\n");
                    char YN;
                    scanf("%s", &YN);
                    if (YN == 'Y') exitFlag = true;
                    break;
                default:
                    printf("It's impossible but you seeing this text now");
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE)) {
            keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);
            printf("See you soon!");
            return 0;
        }
        permissionToChoice = true;
    }
    printf("See you soon!");
    return 0;
}

