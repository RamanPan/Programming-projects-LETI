#include "Faculty.h"
#include "validationFunctions.h"

const std::string &Faculty::getTitle() const {
    return title;
}

void Faculty::setTitle(const std::string &title) {
    Faculty::title = title;
}

std::vector<Department> &Faculty::getDepartments() {
    return departments;
}

void Faculty::setDepartments(const std::vector<Department> &departments) {
    Faculty::departments = departments;
}

Faculty::Faculty(const std::string &title) : title(title) {}

Faculty::Faculty() {}

void Faculty::addDepartment() {
    Department department;
    char permission;
    department.setTitle(validateString("введите название кафедры", true));
    showInfoMessage("создать группы прямо сейчас?(1 - Да, 2 - Нет)");
    choice(permission);
    if (permission == '1') {
        showInfoMessage("введите кол-во создаваемых групп");
        int quantity = validation();
        for (int i = 0; i < quantity; ++i) {
            department.addGroup();
        }
    }
    departments.push_back(department);
}

void Faculty::deleteAll() {
    for (Department d: departments) {
        d.deleteAll();
    }
    departments.clear();
}

Department *Faculty::findDepartment(const std::string &data) {
    for (Department &d: departments) {
        if (d.getTitle() == data)
            return &d;
    }
    showErrorMessage("кафедра не была найдена");
    return nullptr;
}

bool Faculty::deleteDepartment(const std::string &data) {
    int index = -1;
    Department d;
    for (int i = 0; i < departments.size(); ++i) {
        d = departments.at(i);
        if (d.getTitle() == data) {
            d.deleteAll();
            index = i;
            break;
        }
    }
    if (index != -1) {
        departments.erase(departments.begin() + index);
        return true;
    } else showErrorMessage("такой кафедры не существует");
    return false;

}

void Faculty::writeToFile(std::ofstream &out) {
    out << std::bitset<8>(IDENTITY_FACULTY) << ' ' << std::endl;
    writeStringToFile(out, title);
    for (Department &department: departments)
        department.writeToFile(out);
}



