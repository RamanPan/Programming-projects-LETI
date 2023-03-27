#include "Department.h"
#include "Messages.h"
#include "validationFunctions.h"

const std::string &Department::getTitle() const {
    return title;
}

void Department::setTitle(const std::string &title) {
    Department::title = title;
}

std::vector<Group> &Department::getGroups() {
    return groups;
}

void Department::setGroups(const std::vector<Group> &groups) {
    Department::groups = groups;
}

Department::Department(const std::string &title) : title(title) {}

Department::Department() {}

void Department::addGroup() {
    Group group;
    char permission;
    showInfoMessage("Введите номер создаваемой группы");
    group.setNumber(validationWithArgument(0, 10000));
    showInfoMessage("Добавить студентов прямо сейчас?(1 - Да, 2 - Нет)");
    choice(permission);
    if (permission == '1') {
        showInfoMessage("Введите кол-во создаваемых групп");
        int quantity = validation();
        for (int i = 0; i < quantity; ++i) {
            group.addStudent();
        }
    }
    groups.push_back(group);
}

Group *Department::findGroup(int data) {
    for (Group &g: groups) {
        if (g.getNumber() == data)
            return &g;
    }
    showErrorMessage("Группа не была найдена");
    return nullptr;
}

void Department::deleteGroup(int data) {
    int index = -1;
    Group g;
    for (int i = 0; i < groups.size(); ++i) {
        g = groups.at(i);
        if (g.getNumber() == data) {
            g.deleteAll();
            index = i;
            break;
        }
    }
    if (index != -1) groups.erase(groups.begin() + index);
    else showErrorMessage("Такой кафедры не существует");

}

void Department::deleteAll() {
    for (Group g: groups) {
        g.deleteAll();
    }
    groups.clear();
}
