#include "Student.h"

#include <utility>



Student::Student() {}

Student::Student(const std::string &firstname, const std::string &surname, const std::string &patronymic, Gender gender)
        : firstname(firstname), surname(surname), patronymic(patronymic), gender(gender) {}

const std::string &Student::getFirstname() const {
    return firstname;
}

void Student::setFirstname(const std::string &firstname) {
    Student::firstname = firstname;
}

const std::string &Student::getSurname() const {
    return surname;
}

void Student::setSurname(const std::string &surname) {
    Student::surname = surname;
}

const std::string &Student::getPatronymic() const {
    return patronymic;
}

void Student::setPatronymic(const std::string &patronymic) {
    Student::patronymic = patronymic;
}

Gender Student::getGender() const {
    return gender;
}

void Student::setGender(Gender gender) {
    Student::gender = gender;
}
