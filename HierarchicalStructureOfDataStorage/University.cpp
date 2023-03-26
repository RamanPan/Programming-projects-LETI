#include "University.h"

#include <utility>
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
    faculty.setTitle(validateString("Введите название факультета"));
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

void University::deleteFaculty(const std::string &data) {
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
    if (index != -1) faculties.erase(faculties.begin() + index);
    else showErrorMessage("Такого факультета не существует");
}

void University::deleteAll() {
    for (Faculty f: faculties) {
        f.deleteAll();
    }
    faculties.clear();
}

