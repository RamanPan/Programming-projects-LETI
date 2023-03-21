#include "supportFunctions.h"

void showMenuForUniversity(int position) {
    system("cls");
    printf("Выберите действие:\n");
    printf("1) Добавить новый факультет%s\n", position == 1 ? " <--" : " ");
    printf("2) Сложить/Вычесть матрицы%s\n", position == 2 ? " <--" : " ");
    printf("3) Умножить матрицы в порядке A*B%s\n", position == 3 ? " <--" : " ");
    printf("4) Умножить матрицы в порядке B*A%s\n", position == 4 ? " <--" : " ");
    printf("5) Транспонировать матрицы%s\n", position == 5 ? " <--" : " ");
    printf("6) Посчитать определитель%s\n", position == 6 ? " <--" : " ");
    printf("7) Посчитать обратную матрицу%s\n", position == 7 ? " <--" : " ");
    printf("8) Ввести(сгенерировать или вручную) первую матрицу по новой%s\n", position == 8 ? " <--" : " ");
    printf("9) Ввести(сгенерировать или вручную) вторую матрицу по новой%s\n", position == 9 ? " <--" : " ");
    printf("0) Выход%s\n", position == 10 ? " <--" : " ");
}