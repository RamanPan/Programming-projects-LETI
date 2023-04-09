#include <cstdio>
#include <iostream>
#include "validationFunctions.h"

std::string validateString(const std::string& message, bool validate) {
    std::string string;
    showInfoMessage(message);
    std::cin >> string;
    if (validate) {
        while (string.empty()) {
            showErrorMessage("Строка не может быть пустой");
            std::cin >> string;
        }
    }
    return string;
}

long validation() {
    bool validationFlag = false;
    double result;
    while (!validationFlag) {
        if (scanf("%lf", &result)) {
            if (!checkOverflow(result)) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("Неправильный ввод! Число вышло за границу дозволенного! Попробуйте снова!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            } else validationFlag = true;
        } else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Неправильный ввод! Попробуйте снова!\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
        fflush(stdin);
    }
    return (long) result;
}

long validationWithArgument(int min, int max) {
    long result;
    do {
        result = validation();
        if (result > max || result < min) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("неверный ввод! Значение должно быть от %d до %d\n", min,
                   max);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
    } while (result > max || result < min);
    return result;
}

void choice(char &YN) {
    bool exit = false;
    while (!exit) {
        fflush(stdin);
        YN = (char) getchar();
        fflush(stdin);
        if (YN == '1' || YN == '2') exit = true;
        else if (YN != ENTER) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("неверный ввод! Значение должно быть либо 1, либо 2 \n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        }
    }
}

bool checkOverflow(double d) {
    return d >= -2147483648 && d <= 2147483647;
}
