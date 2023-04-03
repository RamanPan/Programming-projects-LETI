#include "University.h"

#include <utility>
#include "validationFunctions.h"
#include "Messages.h"
#include "FileManager.h"

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
    writeStringToFile(out,"u");
    writeStringToFile(out, title);
    for (Faculty &faculty: faculties)
        faculty.writeToFile(out);
}

void University::readFromFile(std::istream &in) {

}

