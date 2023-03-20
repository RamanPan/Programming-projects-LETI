#include "Faculty.h"

const std::string &Faculty::getTitle() const {
    return title;
}

void Faculty::setTitle(const std::string &title) {
    Faculty::title = title;
}

const std::vector<Department> &Faculty::getDepartments() const {
    return departments;
}

void Faculty::setDepartments(const std::vector<Department> &departments) {
    Faculty::departments = departments;
}

Faculty::Faculty(const std::string &title) : title(title) {}

Faculty::Faculty() {}
