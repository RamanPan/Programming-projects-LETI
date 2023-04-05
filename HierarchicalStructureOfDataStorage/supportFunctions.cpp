#include <iostream>
#include <conio.h>
#include "supportFunctions.h"
#include "constants.h"
#include "Messages.h"
#include "validationFunctions.h"

void showMenuForUniversity(int position, University &university) {
    system("cls");
    bool flag = false;
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
    if (university.getFaculties().empty()) std::cout << std::endl;
    else
        for (const Faculty &faculty: university.getFaculties()) {
            std::cout << faculty.getTitle() << " ";
            flag = true;
        }
    if (flag)std::cout << std::endl;
}

void consoleInterfaceForUniversity(University &university) {
    bool exitFlag = false, permissionFlag;
    short symbol;
    short position = 1;
    char YN;
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
                else position = MAX_ARROW_POSITION_UNI;
                break;
            case S:
                if (position < MAX_ARROW_POSITION_UNI) position++;
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
                        if (f != nullptr) {
                            showMenuForFaculty(1, *f);
                            consoleInterfaceForFaculty(*f, university);
                            showMenuForUniversity(position, university);
                        }
                    } else showErrorMessage("Факультеты отсутствуют");
                }
                break;
            case 5:
                if (permissionFlag) {
                    university.writeToFile();
                }
                break;
            case 6:
                if (permissionFlag) {
                    if (university.readFromFile()) {
                        showMenuForUniversity(position, university);
                    }
                }
                break;
            case 7:
                if (permissionFlag) {
                    std::cout << "Сохранится перед выходом?(1 - да, 2 - нет)" << std::endl;
                    choice(YN);
                    if (YN == '1') {
                        university.writeToFile();
                    }
                    exit(0);
                }
                break;
            default:;
        }
    }
}

void showMenuForFaculty(int position, Faculty &faculty) {
    system("cls");
    bool flag = false;
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
    if (faculty.getDepartments().empty()) std::cout << std::endl;
    else
        for (const Department &department: faculty.getDepartments()) {
            std::cout << department.getTitle() << " ";
            flag = true;
        }
    if (flag)std::cout << std::endl;
}

void consoleInterfaceForFaculty(Faculty &faculty, University &university) {
    bool exitFlag = false, permissionFlag;
    short symbol;
    short position = 1;
    showMenuForFaculty(position, faculty);
    char YN;
    std::string title;
    while (!exitFlag) {
        permissionFlag = false;
        symbol = (short) getch();
        if (symbol == FIRST_BYTE_ARROW) symbol = (short) getch();
        switch (symbol) {
            case ARROW_UP:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION;
                break;
            case ARROW_DOWN:
                if (position < MAX_ARROW_POSITION) position++;
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
                    faculty.addDepartment();
                    showMenuForFaculty(position, faculty);
                }
                break;
            case 2:
                if (permissionFlag) {
                    if (!faculty.getDepartments().empty()) {
                        if (faculty.deleteDepartment(
                                validateString("Введите название кафедры", true)))
                            showMenuForFaculty(position, faculty);
                    } else showErrorMessage("Кафедра с таким названием отсутствует");
                }
                break;
            case 3:
                if (permissionFlag) {
                    std::cout << "Введите новое название!" << std::endl;
                    std::cin >> title;
                    if (title.empty()) showErrorMessage("Название не может быть пустым!");
                    else {
                        faculty.setTitle(title);
                        showMenuForFaculty(position, faculty);
                    }
                }
                break;
            case 4:
                if (permissionFlag) {
                    if (!faculty.getDepartments().empty()) {
                        Department *d = faculty.findDepartment(validateString("Введите название кафедры", true));
                        if (d != nullptr) {
                            consoleInterfaceForDepartment(*d, university);
                            showMenuForFaculty(position, faculty);
                        }
                    } else showErrorMessage("Кафедры с таким названием не существует");
                }
                break;
            case 5:
                if (permissionFlag) {
                    university.writeToFile();
                }
                break;
            case 6:
                if (permissionFlag) {
                    if (university.readFromFile()) {
                        showMenuForFaculty(position, faculty);
                    }
                }
                break;
            case 7:
                if (permissionFlag) {
                    showMenuForUniversity(1, university);
                    return;
                }
                break;
            case 8:
                if (permissionFlag) {
                    std::cout << "Сохранится перед выходом?(1 - да, 2 - нет)" << std::endl;
                    choice(YN);
                    if (YN == '1') {
                        std::ofstream out(
                                R"(E:\C_C++\Programming-projects-LETI\HierarchicalStructureOfDataStorage\data.bin)",
                                std::ios_base::binary | std::ios_base::out);
                        university.writeToFile();
                        out.close();
                    }
                    exit(0);
                }
            default:;
        }
    }
}


void showMenuForDepartment(int position, Department &department) {
    system("cls");
    bool flag = false;
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
    if (department.getGroups().empty()) std::cout << std::endl;
    else
        for (const Group &group: department.getGroups()) {
            std::cout << group.getNumber() << " ";
            flag = true;
        }
    if (flag)std::cout << std::endl;
}

void consoleInterfaceForDepartment(Department &department, University &university) {
    bool exitFlag = false, permissionFlag;
    short symbol;
    short position = 1;
    char YN;
    std::string title;
    showMenuForDepartment(position, department);
    while (!exitFlag) {
        permissionFlag = false;
        symbol = (short) getch();
        if (symbol == FIRST_BYTE_ARROW) symbol = (short) getch();
        switch (symbol) {
            case ARROW_UP:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION;
                break;
            case ARROW_DOWN:
                if (position < MAX_ARROW_POSITION) position++;
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
                    department.addGroup();
                    showMenuForDepartment(position, department);
                }
                break;
            case 2:
                if (permissionFlag) {
                    if (!department.getGroups().empty()) {
                        std::cout << "Введите номер группы" << std::endl;
                        if (department.deleteGroup(
                                validationWithArgument(0, 10000)))
                            showMenuForDepartment(position, department);
                    } else showErrorMessage("Группа с таким номером отсутствует");
                }
                break;
            case 3:
                if (permissionFlag) {
                    std::cout << "Введите новое название!" << std::endl;
                    std::cin >> title;
                    if (title.empty()) showErrorMessage("Название не может быть пустым!");
                    else {
                        department.setTitle(title);
                        showMenuForDepartment(position, department);
                    }
                }
                break;
            case 4:
                if (permissionFlag) {
                    if (!department.getGroups().empty()) {
                        std::cout << "Введите номер группы" << std::endl;
                        Group *g = department.findGroup(validation());
                        if (g != nullptr) {
                            consoleInterfaceForGroup(*g, university);
                            showMenuForDepartment(position, department);
                        }
                    } else showErrorMessage("Кафедры с таким названием не существует");
                }
                break;
            case 5:
                if (permissionFlag) {
                    university.writeToFile();
                }
                break;
            case 6:
                if (permissionFlag) {
                    if (university.readFromFile()) {
                        showMenuForDepartment(position, department);
                    }
                }
                break;
            case 7:
                if (permissionFlag) {
                    return;
                }
                break;
            case 8:
                if (permissionFlag) {
                    std::cout << "Сохранится перед выходом?(1 - да, 2 - нет)" << std::endl;
                    choice(YN);
                    if (YN == '1') {
                        university.writeToFile();
                    }
                    exit(0);
                }
            default:;
        }
    }
}

void showMenuForGroup(int position, Group &group) {
    system("cls");
    bool flag = false;
    std::string gender;
    printf("Выберите действие:\n");
    printf("1) Добавить студента%s\n", position == 1 ? " <--" : " ");
    printf("2) Отчислить студента%s\n", position == 2 ? " <--" : " ");
    printf("3) Сменить номер группы%s\n", position == 3 ? " <--" : " ");
    printf("4) Изменить данные студента%s\n", position == 4 ? " <--" : " ");
    printf("5) Сохранить данные%s\n", position == 5 ? " <--" : " ");
    printf("6) Загрузить данные%s\n", position == 6 ? " <--" : " ");
    printf("7) Вернуться на уровень группы%s\n", position == 7 ? " <--" : " ");
    printf("8) Выход%s\n", position == 8 ? " <--" : " ");
    std::cout << "Номер группы: " << group.getNumber() << std::endl;
    std::cout << "Студенты: " << std::endl;
    for (const Student &student: group.getStudents()) {
        gender = (student.getGender() == MEN) ? "- men" : "- women";
        std::cout << student.getFirstname() << " " << student.getSurname() << " " << student.getPatronymic() << " "
                  << gender << std::endl;
        flag = true;
    }
    if (flag)std::cout << std::endl;
}

void consoleInterfaceForGroup(Group &group, University &university) {
    bool exitFlag = false, permissionFlag;
    short symbol;
    short position = 1;
    char YN;
    showMenuForGroup(position, group);
    while (!exitFlag) {
        permissionFlag = false;
        symbol = (short) getch();
        if (symbol == FIRST_BYTE_ARROW) symbol = (short) getch();
        switch (symbol) {
            case ARROW_UP:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION;
                break;
            case ARROW_DOWN:
                if (position < MAX_ARROW_POSITION) position++;
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
                    group.addStudent();
                    showMenuForGroup(position, group);
                }
                break;
            case 2:
                if (permissionFlag) {
                    if (!group.getStudents().empty()) {
                        if (group.deleteStudent(
                                validateString("Введите фамилию студента", true)))
                            showMenuForGroup(position, group);
                    } else showErrorMessage("Группа с таким номером отсутствует");
                }
                break;
            case 3:
                if (permissionFlag) {
                    std::cout << "Введите новый номер" << std::endl;
                    group.setNumber(validationWithArgument(0, 10000));
                    showMenuForGroup(position, group);
                }
                break;
            case 4:
                if (permissionFlag) {
                    if (!group.getStudents().empty()) {
                        Student *s = group.findStudent(validateString("Введите фамилию студента", true));
                        if (s != nullptr) {
                            std::cout << "Выберите что хотите изменить(1 - фамилия, 2 - имя, 3 - отчество, 4 - пол)"
                                      << std::endl;
                            int choice = validationWithArgument(1, 4);
                            switch (choice) {
                                case 1:
                                    s->setSurname(validateString("Введите новую фамилию", true));
                                    break;
                                case 2:
                                    s->setFirstname(validateString("Введите новое имя", true));
                                    break;
                                case 3:
                                    s->setPatronymic(validateString("Введите новое отчество", true));
                                    break;
                                case 4:
                                    std::cout << "Выберите пол(1 - мужской, 2 - женский)" << std::endl;
                                    choice = validationWithArgument(1, 2);
                                    if (choice == 1) s->setGender(MEN);
                                    else s->setGender(WOMEN);
                                    break;
                            }
                            showMenuForGroup(position, group);
                        }
                    } else showErrorMessage("Студента с таким ФИО не существует");
                }
                break;
            case 5:
                if (permissionFlag) {
                    university.writeToFile();
                }
                break;
            case 6:
                if (permissionFlag) {
                    if (university.readFromFile()) {
                        showMenuForGroup(position, group);
                    }
                }
                break;
            case 7:
                if (permissionFlag) {
                    return;
                }
                break;
            case 8:
                if (permissionFlag) {
                    std::cout << "Сохранится перед выходом?(1 - да, 2 - нет)" << std::endl;
                    choice(YN);
                    if (YN == '1') {
                        university.writeToFile();
                    }
                    exit(0);
                }
            default:;
        }
    }

}


