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
    s.setFirstname(validateString("введите имя студента", true));
    s.setSurname(validateString("введите фамилию студента", true));
    s.setPatronymic(validateString("введите отчество студента(если есть)", false));
    showInfoMessage("мужчина или женщина?(1/2)");
    choice(permission);
    if (permission == '1') s.setGender(MEN);
    else s.setGender(WOMEN);
    students.push_back(s);
}

Student *Group::findStudent(const std::string &data) {
    for (Student &s: students) {
        if (s.getSurname() == data)
            return &s;
    }
    showErrorMessage("студент не был найден");
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
    } else showErrorMessage("студента с такой фамилией не существует");
    return false;

}

void Group::deleteAll() {
    students.clear();
}

void Group::writeToFile(std::ofstream &out) {
    out << std::bitset<8>(IDENTITY_GROUP) << ' ' << std::endl;
    out << std::bitset<16>(number) << ' ' << std::endl;
    for (Student &student: students)
        student.writeToFile(out);
}

