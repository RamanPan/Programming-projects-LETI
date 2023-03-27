#include <iostream>
#include <conio.h>
#include "supportFunctions.h"
#include "constants.h"
#include "Messages.h"
#include "validationFunctions.h"

void showMenuForUniversity(int position, University &university) {
    system("cls");
    printf("Выберите действие:\n");
    printf("1) Добавить факультет%s\n", position == 1 ? " <--" : " ");
    printf("2) Удалить факультет%s\n", position == 2 ? " <--" : " ");
    printf("3) Сменить название университета%s\n", position == 3 ? " <--" : " ");
    printf("4) Выбрать факультет для редактирования%s\n", position == 4 ? " <--" : " ");
    printf("5) Сохранить данные%s\n", position == 5 ? " <--" : " ");
    printf("6) Загрузить данные%s\n", position == 6 ? " <--" : " ");
    printf("7) Выход%s\n", position == 7 ? " <--" : " ");
    std::cout << "Название университета: " << university.getTitle() << std::endl;
    std::cout << "Факультеты университета: ";
    for (const Faculty &faculty: university.getFaculties())
        std::cout << faculty.getTitle() << std::endl;
    std::cout << std::endl;

}

void consoleInterfaceForUniversity(University &university) {
    bool exitFlag = false, permissionFlag;
    short symbol;
    short position = 1;
    showMenuForUniversity(position, university);
    std::string title;
    while (!exitFlag) {
        permissionFlag = false;
        symbol = (short) getch();
        if (symbol == FIRST_BYTE_ARROW) symbol = (short) getch();
        switch (symbol) {
            case ARROW_UP:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION_UNI;
                break;
            case ARROW_DOWN:
                if (position < MAX_ARROW_POSITION_UNI) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case W:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION;
                break;
            case S:
                if (position < MAX_ARROW_POSITION) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case ESC:
                exitFlag = true;
                break;
            case ENTER:
                permissionFlag = true;
                break;
            case ONE:
                position = 1;
                break;
            case TWO:
                position = 2;
                break;
            case THREE:
                position = 3;
                break;
            case FOUR:
                position = 4;
                break;
            case FIVE:
                position = 5;
                break;
            case SIX:
                position = 6;
                break;
            case SEVEN:
                position = 7;
                break;
            default:;
        }
        showMenuForUniversity(position, university);
        switch (position) {
            case 1:
                if (permissionFlag) {
                    university.addFaculty();
                    showMenuForUniversity(position, university);

                }
                break;
            case 2:
                if (permissionFlag) {
                    if (!university.getFaculties().empty()) {
                        if (university.deleteFaculty(
                                validateString("Введите название факультета", true)))
                            showMenuForUniversity(position, university);
                    } else showErrorMessage("Факультеты отсутствуют");
                }
                break;
            case 3:
                if (permissionFlag) {
                    std::cout << "Введите новое название!" << std::endl;
                    std::cin >> title;
                    if (title.empty()) showErrorMessage("Название не может быть пустым!");
                    else {
                        university.setTitle(title);
                        showMenuForUniversity(position, university);
                    }
                }
                break;
            case 4:
                if (permissionFlag) {
                    if (!university.getFaculties().empty()) {
                        Faculty *f = university.findFaculty(validateString("Введите название факультета", true));
                        if (f != nullptr) consoleInterfaceForFaculty(*f, university);
                    } else showErrorMessage("Факультеты отсутствуют");
                }
                break;
            case 5:
                if (permissionFlag) {

                    showMenuForUniversity(position, university);
                }
                break;
            case 6:
                if (permissionFlag) {

                    showMenuForUniversity(position, university);
                }
                break;
            case 7:
                if (permissionFlag) {
                    exit(0);
                }
                break;
            default:;
        }
    }
}

void showMenuForFaculty(int position, Faculty &faculty) {
    system("cls");
    printf("Выберите действие:\n");
    printf("1) Добавить кафедру%s\n", position == 1 ? " <--" : " ");
    printf("2) Удалить кафедру%s\n", position == 2 ? " <--" : " ");
    printf("3) Сменить название факультета%s\n", position == 3 ? " <--" : " ");
    printf("4) Выбрать кафедру для редактирования%s\n", position == 4 ? " <--" : " ");
    printf("5) Сохранить данные%s\n", position == 5 ? " <--" : " ");
    printf("6) Загрузить данные%s\n", position == 6 ? " <--" : " ");
    printf("7) Вернуться на уровень университета%s\n", position == 7 ? " <--" : " ");
    printf("8) Выход%s\n", position == 8 ? " <--" : " ");
    std::cout << "Название факультета: " << faculty.getTitle() << std::endl;
    std::cout << "Кафедры факультета: ";
    for (const Department &department: faculty.getDepartments())
        std::cout << department.getTitle() << std::endl;
}

void consoleInterfaceForFaculty(Faculty &faculty, University &university) {
    bool exitFlag = false, permissionFlag;
    short symbol;
    short position = 1;
    showMenuForUniversity(position, university);
    while (!exitFlag) {
        permissionFlag = false;
        symbol = (short) getch();
        if (symbol == FIRST_BYTE_ARROW) symbol = (short) getch();
        switch (symbol) {
            case ARROW_UP:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION_UNI;
                break;
            case ARROW_DOWN:
                if (position < MAX_ARROW_POSITION_UNI) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case W:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION;
                break;
            case S:
                if (position < MAX_ARROW_POSITION) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case ESC:
                exitFlag = true;
                break;
            case ENTER:
                permissionFlag = true;
                break;
            case ONE:
                position = 1;
                break;
            case TWO:
                position = 2;
                break;
            case THREE:
                position = 3;
                break;
            case FOUR:
                position = 4;
                break;
            case FIVE:
                position = 5;
                break;
            case SIX:
                position = 6;
                break;
            case SEVEN:
                position = 7;
                break;
            case EIGHT:
                position = 8;
                break;
            default:;
        }
        showMenuForFaculty(position, faculty);
        switch (position) {
            case 1:
                if (permissionFlag) {

                }
                break;
            case 2:
                if (permissionFlag) {

                }
                break;
            case 3:
                if (permissionFlag) {

                }
                break;
            case 4:
                if (permissionFlag) {

                }
                break;
            case 5:
                if (permissionFlag) {

                }
                break;
            case 6:
                if (permissionFlag) {

                }
                break;
            case 7:
                if (permissionFlag) {

                }
                break;
            case 8:
                if (permissionFlag) {
                    exit(0);
                }
                break;
            default:;
        }
    }
}


void showMenuForDepartment(int position, Department &department) {
    system("cls");
    printf("Выберите действие:\n");
    printf("1) Добавить группу%s\n", position == 1 ? " <--" : " ");
    printf("2) Удалить группу%s\n", position == 2 ? " <--" : " ");
    printf("3) Сменить название кафедры%s\n", position == 3 ? " <--" : " ");
    printf("4) Выбрать группу для редактирования%s\n", position == 4 ? " <--" : " ");
    printf("5) Сохранить данные%s\n", position == 5 ? " <--" : " ");
    printf("6) Загрузить данные%s\n", position == 6 ? " <--" : " ");
    printf("7) Вернуться на уровень факультета%s\n", position == 7 ? " <--" : " ");
    printf("8) Выход%s\n", position == 8 ? " <--" : " ");
    std::cout << "Название кафедры: " << department.getTitle() << std::endl;
    std::cout << "Группы кафедры: ";
    for (const Group &group: department.getGroups())
        std::cout << group.getNumber() << std::endl;
}

void consoleInterfaceForDepartment(Department &department, University &university) {
    bool exitFlag = false, permissionFlag;
    short symbol;
    short position = 1;
    showMenuForUniversity(position, university);
    while (!exitFlag) {
        permissionFlag = false;
        symbol = (short) getch();
        if (symbol == FIRST_BYTE_ARROW) symbol = (short) getch();
        switch (symbol) {
            case ARROW_UP:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION_UNI;
                break;
            case ARROW_DOWN:
                if (position < MAX_ARROW_POSITION_UNI) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case W:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION;
                break;
            case S:
                if (position < MAX_ARROW_POSITION) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case ESC:
                exitFlag = true;
                break;
            case ENTER:
                permissionFlag = true;
                break;
            case ONE:
                position = 1;
                break;
            case TWO:
                position = 2;
                break;
            case THREE:
                position = 3;
                break;
            case FOUR:
                position = 4;
                break;
            case FIVE:
                position = 5;
                break;
            case SIX:
                position = 6;
                break;
            case SEVEN:
                position = 7;
                break;
            case EIGHT:
                position = 8;
                break;
            default:;
        }
        showMenuForDepartment(position, department);
        switch (position) {
            case 1:
                if (permissionFlag) {

                }
                break;
            case 2:
                if (permissionFlag) {

                }
                break;
            case 3:
                if (permissionFlag) {

                }
                break;
            case 4:
                if (permissionFlag) {

                }
                break;
            case 5:
                if (permissionFlag) {

                }
                break;
            case 6:
                if (permissionFlag) {

                }
                break;
            case 7:
                if (permissionFlag) {

                }
                break;
            case 8:
                if (permissionFlag) {
                    if (permissionFlag) {
                        exit(0);
                    }
                    break;
                }
                break;
            default:;
        }
    }
}

void showMenuForGroup(int position, Group &group) {
    system("cls");
    printf("Выберите действие:\n");
    printf("1) Добавить студента%s\n", position == 1 ? " <--" : " ");
    printf("2) Отчислить студента%s\n", position == 2 ? " <--" : " ");
    printf("3) Сменить номер группы%s\n", position == 3 ? " <--" : " ");
    printf("4) Изменить данные студента%s\n", position == 4 ? " <--" : " ");
    printf("5) Сохранить данные%s\n", position == 5 ? " <--" : " ");
    printf("6) Загрузить данные%s\n", position == 6 ? " <--" : " ");
    printf("7) Вернуться на уровень кафедры%s\n", position == 7 ? " <--" : " ");
    printf("8) Выход%s\n", position == 8 ? " <--" : " ");
    std::cout << "Номер группы: " << group.getNumber() << std::endl;
    std::cout << "Студенты: ";
    for (const Student &student: group.getStudents())
        std::cout << student.getFirstname() << " " << student.getSurname() << " " << student.getPatronymic() << " "
                  << student.getGender() << std::endl;
}

void consoleInterfaceForGroup(Group &group, University &university) {
    bool exitFlag = false, permissionFlag;
    short symbol;
    short position = 1;
    showMenuForUniversity(position, university);
    while (!exitFlag) {
        permissionFlag = false;
        symbol = (short) getch();
        if (symbol == FIRST_BYTE_ARROW) symbol = (short) getch();
        switch (symbol) {
            case ARROW_UP:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION_UNI;
                break;
            case ARROW_DOWN:
                if (position < MAX_ARROW_POSITION_UNI) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case W:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION;
                break;
            case S:
                if (position < MAX_ARROW_POSITION) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case ESC:
                exitFlag = true;
                break;
            case ENTER:
                permissionFlag = true;
                break;
            case ONE:
                position = 1;
                break;
            case TWO:
                position = 2;
                break;
            case THREE:
                position = 3;
                break;
            case FOUR:
                position = 4;
                break;
            case FIVE:
                position = 5;
                break;
            case SIX:
                position = 6;
                break;
            case SEVEN:
                position = 7;
                break;
            case EIGHT:
                position = 8;
                break;
            default:;
        }
        showMenuForGroup(position, group);
        switch (position) {
            case 1:
                if (permissionFlag) {

                }
                break;
            case 2:
                if (permissionFlag) {

                }
                break;
            case 3:
                if (permissionFlag) {

                }
                break;
            case 4:
                if (permissionFlag) {

                }
                break;
            case 5:
                if (permissionFlag) {

                }
                break;
            case 6:
                if (permissionFlag) {

                }
                break;
            case 7:
                if (permissionFlag) {

                }
                break;
            case 8:
                if (permissionFlag) {
                    if (permissionFlag) {
                        exit(0);
                    }
                    break;
                }
                break;
            default:;
        }
    }
}



