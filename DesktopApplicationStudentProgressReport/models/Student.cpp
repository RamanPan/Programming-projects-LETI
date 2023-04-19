#include "Student.h"

const QString &Student::getFio() const {
    return fio;
}

void Student::setFio(const QString &fio) {
    Student::fio = fio;
}

const QString &Student::getNumberGroup() const {
    return numberGroup;
}

void Student::setNumberGroup(const QString &numberGroup) {
    Student::numberGroup = numberGroup;
}

int Student::getGender() const {
    return gender;
}

void Student::setGender(int gender) {
    Student::gender = gender;
}

Student::Student(const QString &fio, const QString &numberGroup, int gender, const QList<Subject> &subjects) : fio(fio),
                                                                                                               numberGroup(numberGroup),
                                                                                                               gender(gender),
                                                                                                               subjects(subjects) {}

const QList<Subject> &Student::getSubjects() const {
    return subjects;
}

void Student::setSubjects(const QList<Subject> &subjects) {
    Student::subjects = subjects;
}

Student::Student(const QString &fio, const QString &numberGroup, int gender) : fio(fio), numberGroup(numberGroup),
                                                                               gender(gender) {}
