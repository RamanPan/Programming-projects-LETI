#include "University.h"

const std::string &University::getTitle() const {
    return title;
}

void University::setTitle(const std::string &title) {
    University::title = title;
}

const std::vector<Faculty> &University::getFaculties() const {
    return faculties;
}

void University::setFaculties(const std::vector<Faculty> &faculties) {
    University::faculties = faculties;
}

University::University(const std::string &title) : title(title) {}

University::University() {}
