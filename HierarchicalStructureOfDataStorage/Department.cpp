#include "Department.h"

const std::string &Department::getTitle() const {
    return title;
}

void Department::setTitle(const std::string &title) {
    Department::title = title;
}

std::vector<Group> &Department::getGroups() const {
    return groups;
}

void Department::setGroups(const std::vector<Group> &groups) {
    Department::groups = groups;
}

Department::Department(const std::string &title) : title(title) {}

Department::Department() {}
