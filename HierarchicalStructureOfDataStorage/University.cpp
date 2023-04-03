#include "University.h"

#include <utility>
#include <iostream>
#include "validationFunctions.h"
#include "Messages.h"

const std::string &University::getTitle() const {
    return title;
}

void University::setTitle(const std::string &title) {
    University::title = title;
}

std::vector<Faculty> &University::getFaculties() {
    return faculties;
}

void University::setFaculties(const std::vector<Faculty> &faculties) {
    University::faculties = faculties;
}

University::University(std::string title) : title(std::move(title)) {}

University::University() {}

void University::addFaculty() {
    Faculty faculty;
    char permission;
    faculty.setTitle(validateString("Введите название факультета", true));
    showInfoMessage("Создать кафедры прямо сейчас?(1 - Да, 2 - Нет)");
    choice(permission);
    if (permission == '1') {
        showInfoMessage("Введите кол-во создаваемых кафедр");
        int quantity = validation();
        for (int i = 0; i < quantity; ++i) {
            faculty.addDepartment();
        }
    }
    faculties.push_back(faculty);
}

Faculty *University::findFaculty(const std::string &data) {
    for (Faculty &f: faculties) {
        if (f.getTitle() == data)
            return &f;
    }
    showErrorMessage("Факультет не был найден");
    return nullptr;
}

bool University::deleteFaculty(const std::string &data) {
    int index = -1;
    Faculty f;
    for (int i = 0; i < faculties.size(); ++i) {
        f = faculties.at(i);
        if (f.getTitle() == data) {
            f.deleteAll();
            index = i;
            break;
        }
    }
    if (index != -1) {
        faculties.erase(faculties.begin() + index);
        return true;
    } else showErrorMessage("Такого факультета не существует");
    return false;
}

void University::deleteAll() {
    for (Faculty f: faculties) {
        f.deleteAll();
    }
    faculties.clear();
}

void University::writeToFile(std::ofstream &out) {
    out << std::bitset<8>(IDENTITY_UNIVERSITY) << ' ';
    writeStringToFile(out, title);
    for (Faculty &faculty: faculties)
        faculty.writeToFile(out);
}

bool University::readFromFile(std::ifstream &in) {
    if (readAndCheckIdentity(in, 'U')) {
        deleteAll();
        title = readStringFromFile(in);
        char status;
        Faculty *nowF = nullptr;
        Department *nowD = nullptr;
        Group *nowG = nullptr;
        bool notMistake = true, mistake = false;
        while (!in.eof()) {
            status = readIdentity(in);
            if (status == 0) break;
            if (mistake) {
                std::cout << 1;
                notMistake = false;
            }
            if (notMistake) {
                switch (status) {
                    case 'F': {
                        Faculty faculty(readStringFromFile(in));
                        faculties.push_back(faculty);
                        nowF = &faculties.at(faculties.size() - 1);
                    }
                        break;
                    case 'D': {
                        Department department(readStringFromFile(in));
                        if (nowF != nullptr) {
                            nowF->getDepartments().push_back(department);
                            nowD = &nowF->getDepartments().at(nowF->getDepartments().size() - 1);
                        } else mistake = true;
                    }
                        break;
                    case 'G': {
                        Group group(readIntFromFile(in));
                        if (nowD != nullptr) {
                            nowD->getGroups().push_back(group);
                            nowG = &nowD->getGroups().at(nowD->getGroups().size() - 1);
                        } else mistake = true;
                    }
                        break;
                    case 'S': {
                        Student student;
                        student.setFirstname(readStringFromFile(in));
                        student.setSurname(readStringFromFile(in));
                        student.setPatronymic(readStringFromFile(in));
                        if (readIntFromFile(in) == 0) student.setGender(MEN);
                        else student.setGender(WOMEN);
                        if (nowG != nullptr) {
                            nowG->getStudents().push_back(student);
                        } else mistake = true;
                    }
                        break;
                }
            } else {
                showErrorMessage("Данные в файле хранятся в неправильном формате");
                return false;
            }
        }
    } else {
        showErrorMessage("Данные в файле хранятся в неправильном формате");
        return false;
    }
    return true;
}

