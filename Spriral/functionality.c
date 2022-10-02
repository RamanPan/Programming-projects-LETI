#include <stdlib.h>
#include <stdio.h>
#include "functionality.h"

void showHelloMessage() {
    printf("Добро пожаловать!!!\n");
}

void showMenu(int position) {
    system("cls");
    printf("Выберите действие:'\n");
    printf("1) Изменить длину%s\n", position == 1 ? "<-" : " ");
    printf("2) Изменить ширину%s\n", position == 2 ? "<-" : " ");
    printf("3) Спираль в центр по часовой%s\n", position == 3 ? "<-" : " ");
    printf("4) Спираль в центр против часовой%s\n", position == 4 ? "<-" : " ");
    printf("5) Спираль из центра по часовой%s\n", position == 5 ? "<-" : " ");
    printf("6) Спираль из центра против часовой%s\n", position == 6 ? "<-" : " ");
    printf("7) Выход%s\n", position == 7 ? "<-" : " ");
}