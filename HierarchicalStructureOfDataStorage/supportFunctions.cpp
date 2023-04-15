#include <iostream>
#include <conio.h>
#include "supportFunctions.h"
#include "constants.h"
#include "Messages.h"
#include "validationFunctions.h"

void showStudents(std::vector<std::string> students) {
    std::cout << "найденные студенты:" << std::endl;
    if (!students.empty())
        for (const std::string &student: students) {
            std::cout << student
                      << std::endl;
        }
    else showErrorMessage("никто не нашелся...");
}

void showMenuForUniversity(int position, University &university) {
    system("cls");
    bool flag = false;
    printf("выберите действие:\n");
    printf("1) добавить факультет%s\n", position == 1 ? " <--" : " ");
    printf("2) удалить факультет%s\n", position == 2 ? " <--" : " ");
    printf("3) сменить название университета%s\n", position == 3 ? " <--" : " ");
    printf("4) выбрать факультет для редактирования%s\n", position == 4 ? " <--" : " ");
    printf("5) найти студента(ов)%s\n", position == 5 ? " <--" : " ");
    printf("6) сохранить данные%s\n", position == 6 ? " <--" : " ");
    printf("7) загрузить данные%s\n", position == 7 ? " <--" : " ");
    printf("8) выход%s\n", position == 8 ? " <--" : " ");
    std::cout << "название университета: " << university.getTitle() << std::endl;
    std::cout << "факультеты университета: ";
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
                else position = MAX_ARROW_POSITION_UNI_AND_STUD;
                break;
            case ARROW_DOWN:
                if (position < MAX_ARROW_POSITION_UNI_AND_STUD) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case W:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION_UNI_AND_STUD;
                break;
            case S:
                if (position < MAX_ARROW_POSITION_UNI_AND_STUD) position++;
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
                                validateString("введите название факультета", true)))
                            showMenuForUniversity(position, university);
                    } else showErrorMessage("факультеты отсутствуют");
                }
                break;
            case 3:
                if (permissionFlag) {
                    std::cout << "введите новое название!" << std::endl;
                    std::cin >> title;
                    if (title.empty()) showErrorMessage("название не может быть пустым!");
                    else {
                        university.setTitle(title);
                        showMenuForUniversity(position, university);
                    }
                }
                break;
            case 4:
                if (permissionFlag) {
                    if (!university.getFaculties().empty()) {
                        Faculty *f = university.findFaculty(validateString("введите название факультета", true));
                        if (f != nullptr) {
                            showMenuForFaculty(1, *f);
                            consoleInterfaceForFaculty(*f, university);
                            showMenuForUniversity(position, university);
                        }
                    } else showErrorMessage("факультеты отсутствуют");
                }
                break;
            case 5:
                if (permissionFlag) {
                    int mode;
                    std::cout << "выберите параметр поиска(0 - по фамилии, 1 - по имени, 2 - по отчеству, 3 - по полу"
                              << std::endl;
                    mode = validationWithArgument(0, 3);
                    showStudents(university.findStudent(mode));
                }
                break;
            case 6:
                if (permissionFlag) {
                    university.writeToFile(false);
                }
                break;
            case 7:
                if (permissionFlag) {
                    if (university.readFromFile(false)) {
                        showMenuForUniversity(position, university);
                    }
                }
                break;
            case 8:
                if (permissionFlag) {
                    std::cout << "сохранится перед выходом?(1 - да, 2 - нет)" << std::endl;
                    choice(YN);
                    if (YN == '1') {
                        university.writeToFile(false);
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
    printf("выберите действие:\n");
    printf("1) добавить кафедру%s\n", position == 1 ? " <--" : " ");
    printf("2) удалить кафедру%s\n", position == 2 ? " <--" : " ");
    printf("3) сменить название факультета%s\n", position == 3 ? " <--" : " ");
    printf("4) выбрать кафедру для редактирования%s\n", position == 4 ? " <--" : " ");
    printf("5) найти студента(ов)%s\n", position == 5 ? " <--" : " ");
    printf("6) сохранить данные%s\n", position == 6 ? " <--" : " ");
    printf("7) загрузить данные%s\n", position == 7 ? " <--" : " ");
    printf("8) вернуться на уровень университета%s\n", position == 8 ? " <--" : " ");
    printf("9) выход%s\n", position == 9 ? " <--" : " ");
    std::cout << "название факультета: " << faculty.getTitle() << std::endl;
    std::cout << "кафедры факультета: ";
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
                                validateString("введите название кафедры", true)))
                            showMenuForFaculty(position, faculty);
                    } else showErrorMessage("кафедра с таким названием отсутствует");
                }
                break;
            case 3:
                if (permissionFlag) {
                    std::cout << "введите новое название!" << std::endl;
                    std::cin >> title;
                    if (title.empty()) showErrorMessage("название не может быть пустым!");
                    else {
                        faculty.setTitle(title);
                        showMenuForFaculty(position, faculty);
                    }
                }
                break;
            case 4:
                if (permissionFlag) {
                    if (!faculty.getDepartments().empty()) {
                        Department *d = faculty.findDepartment(validateString("введите название кафедры", true));
                        if (d != nullptr) {
                            consoleInterfaceForDepartment(*d, university);
                            showMenuForFaculty(position, faculty);
                        }
                    } else showErrorMessage("кафедры с таким названием не существует");
                }
                break;
            case 5:
                if (permissionFlag) {
                    int mode;
                    std::cout << "выберите параметр поиска(0 - по фамилии, 1 - по имени, 2 - по отчеству, 3 - по полу"
                              << std::endl;
                    mode = validationWithArgument(0, 3);
                    showStudents(university.findStudent(mode));
                }
                break;
            case 6:
                if (permissionFlag) {
                    university.writeToFile(false);
                }
                break;
            case 7:
                if (permissionFlag) {
                    if (university.readFromFile(false)) {
                        showMenuForFaculty(position, faculty);
                    }
                }
                break;
            case 8:
                if (permissionFlag) {
                    showMenuForUniversity(1, university);
                    return;
                }
                break;
            case 9:
                if (permissionFlag) {
                    std::cout << "сохранится перед выходом?(1 - да, 2 - нет)" << std::endl;
                    choice(YN);
                    if (YN == '1') {
                        university.writeToFile(false);
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
    printf("выберите действие:\n");
    printf("1) добавить группу%s\n", position == 1 ? " <--" : " ");
    printf("2) удалить группу%s\n", position == 2 ? " <--" : " ");
    printf("3) сменить название кафедры%s\n", position == 3 ? " <--" : " ");
    printf("4) выбрать группу для редактирования%s\n", position == 4 ? " <--" : " ");
    printf("5) найти студента(ов)%s\n", position == 5 ? " <--" : " ");
    printf("6) сохранить данные%s\n", position == 6 ? " <--" : " ");
    printf("7) загрузить данные%s\n", position == 7 ? " <--" : " ");
    printf("8) вернуться на уровень факультета%s\n", position == 8 ? " <--" : " ");
    printf("9) выход%s\n", position == 9 ? " <--" : " ");
    std::cout << "название кафедры: " << department.getTitle() << std::endl;
    std::cout << "группы кафедры: ";
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
                        std::cout << "введите номер группы" << std::endl;
                        if (department.deleteGroup(
                                validationWithArgument(0, 10000)))
                            showMenuForDepartment(position, department);
                    } else showErrorMessage("группа с таким номером отсутствует");
                }
                break;
            case 3:
                if (permissionFlag) {
                    std::cout << "введите новое название!" << std::endl;
                    std::cin >> title;
                    if (title.empty()) showErrorMessage("название не может быть пустым!");
                    else {
                        department.setTitle(title);
                        showMenuForDepartment(position, department);
                    }
                }
                break;
            case 4:
                if (permissionFlag) {
                    if (!department.getGroups().empty()) {
                        std::cout << "введите номер группы" << std::endl;
                        Group *g = department.findGroup(validation());
                        if (g != nullptr) {
                            consoleInterfaceForGroup(*g, university);
                            showMenuForDepartment(position, department);
                        }
                    } else showErrorMessage("кафедры с таким названием не существует");
                }
                break;
            case 5:
                if (permissionFlag) {
                    int mode;
                    std::cout << "выберите параметр поиска(0 - по фамилии, 1 - по имени, 2 - по отчеству, 3 - по полу"
                              << std::endl;
                    mode = validationWithArgument(0, 3);
                    showStudents(university.findStudent(mode));
                }
                break;
            case 6:
                if (permissionFlag) {
                    university.writeToFile(false);
                }
                break;
            case 7:
                if (permissionFlag) {
                    if (university.readFromFile(false)) {
                        showMenuForDepartment(position, department);
                    }
                }
                break;
            case 8:
                if (permissionFlag) {
                    return;
                }
                break;
            case 9:
                if (permissionFlag) {
                    std::cout << "сохранится перед выходом?(1 - да, 2 - нет)" << std::endl;
                    choice(YN);
                    if (YN == '1') {
                        university.writeToFile(false);
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
    printf("выберите действие:\n");
    printf("1) добавить студента%s\n", position == 1 ? " <--" : " ");
    printf("2) отчислить студента%s\n", position == 2 ? " <--" : " ");
    printf("3) сменить номер группы%s\n", position == 3 ? " <--" : " ");
    printf("4) изменить данные студента%s\n", position == 4 ? " <--" : " ");
    printf("5) сохранить данные%s\n", position == 5 ? " <--" : " ");
    printf("6) загрузить данные%s\n", position == 6 ? " <--" : " ");
    printf("7) вернуться на уровень группы%s\n", position == 7 ? " <--" : " ");
    printf("8) выход%s\n", position == 8 ? " <--" : " ");
    std::cout << "номер группы: " << group.getNumber() << std::endl;
    std::cout << "студенты: " << std::endl;
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
                else position = MAX_ARROW_POSITION_UNI_AND_STUD;
                break;
            case ARROW_DOWN:
                if (position < MAX_ARROW_POSITION_UNI_AND_STUD) position++;
                else
                    position = MIN_ARROW_POSITION;
                break;
            case W:
                if (0 != position - 1)
                    position--;
                else position = MAX_ARROW_POSITION_UNI_AND_STUD;
                break;
            case S:
                if (position < MAX_ARROW_POSITION_UNI_AND_STUD) position++;
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
                                validateString("введите фамилию студента", true)))
                            showMenuForGroup(position, group);
                    } else showErrorMessage("группа с таким номером отсутствует");
                }
                break;
            case 3:
                if (permissionFlag) {
                    std::cout << "введите новый номер" << std::endl;
                    group.setNumber(validationWithArgument(0, 10000));
                    showMenuForGroup(position, group);
                }
                break;
            case 4:
                if (permissionFlag) {
                    if (!group.getStudents().empty()) {
                        Student *s = group.findStudent(validateString("введите фамилию студента", true));
                        if (s != nullptr) {
                            std::cout << "выберите что хотите изменить(1 - фамилия, 2 - имя, 3 - отчество, 4 - пол)"
                                      << std::endl;
                            int choice = validationWithArgument(1, 4);
                            switch (choice) {
                                case 1:
                                    s->setSurname(validateString("введите новую фамилию", true));
                                    break;
                                case 2:
                                    s->setFirstname(validateString("введите новое имя", true));
                                    break;
                                case 3:
                                    s->setPatronymic(validateString("введите новое отчество", true));
                                    break;
                                case 4:
                                    std::cout << "выберите пол(1 - мужской, 2 - женский)" << std::endl;
                                    choice = validationWithArgument(1, 2);
                                    if (choice == 1) s->setGender(MEN);
                                    else s->setGender(WOMEN);
                                    break;
                            }
                            showMenuForGroup(position, group);
                        }
                    } else showErrorMessage("студента с таким ФИО не существует");
                }
                break;
            case 5:
                if (permissionFlag) {
                    university.writeToFile(false);
                }
                break;
            case 6:
                if (permissionFlag) {
                    if (university.readFromFile(false)) {
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
                    std::cout << "сохранится перед выходом?(1 - да, 2 - нет)" << std::endl;
                    choice(YN);
                    if (YN == '1') {
                        university.writeToFile(false);
                    }
                    exit(0);
                }
            default:;
        }
    }

}


