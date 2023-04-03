#include "Group.h"
#include "Messages.h"
#include "validationFunctions.h"

int Group::getNumber() const {
    return number;
}

void Group::setNumber(int number) {
    Group::number = number;
}

std::vector<Student> &Group::getStudents() {
    return students;
}

void Group::setStudents(const std::vector<Student> &students) {
    Group::students = students;
}

Group::Group(int number) : number(number) {}

Group::Group() {}

void Group::addStudent() {
    Student s;
    char permission;
    s.setFirstname(validateString("Введите имя студента", true));
    s.setSurname(validateString("Введите фамилию студента", true));
    s.setPatronymic(validateString("Введите отчество студента(если есть)", false));
    showInfoMessage("Мужчина или женщина?(1/2)");
    choice(permission);
    if (permission) s.setGender(MEN);
    else s.setGender(WOMEN);
    students.push_back(s);
}

Student *Group::findStudent(const std::string &data) {
    for (Student &s: students) {
        if (s.getSurname() == data)
            return &s;
    }
    showErrorMessage("Студент не был найден");
    return nullptr;
}

bool Group::deleteStudent(const std::string &data) {
    int index = -1;
    Student s;
    for (int i = 0; i < students.size(); ++i) {
        s = students.at(i);
        if (s.getSurname() == data) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        students.erase(students.begin() + index);
        return true;
    }
    else showErrorMessage("Студента с такой фамилией не существует");
    return false;

}

void Group::deleteAll() {
    students.clear();
}

void Group::writeToFile(std::ofstream &out) {
    out << std::bitset<8>(IDENTITY_GROUP) << ' ';
    out << std::bitset<16>(number) << ' ';
    for (Student &student: students)
        student.writeToFile(out);
}

