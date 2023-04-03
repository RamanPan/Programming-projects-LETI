#include "Student.h"


Student::Student() {}

Student::Student(const std::string &firstname, const std::string &surname, const std::string &patronymic, Gender gender)
        : firstname(firstname), surname(surname), patronymic(patronymic), gender(gender) {}

Student::Student(const std::string &firstname, const std::string &surname, const std::string &patronymic, int gender)
        : firstname(firstname), surname(surname), patronymic(patronymic) {
    if (gender == 0) this->gender = MEN;
    else this->gender = WOMEN;
}

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

void Student::writeToFile(std::ofstream &out) {
    out << std::bitset<8>(IDENTITY_STUDENT) << ' ' << std::endl;
    writeStringToFile(out, firstname);
    writeStringToFile(out, surname);
    writeStringToFile(out, patronymic);
    out << std::bitset<8>(gender) << ' ' << std::endl;
}

