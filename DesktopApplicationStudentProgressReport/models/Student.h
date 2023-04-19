#ifndef DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_STUDENT_H
#define DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_STUDENT_H


#include <QString>
#include <QList>
#include "Subject.h"

class Student {
private:
    QString fio;
    QString numberGroup;
    int gender;
    QList<Subject> subjects;
public:
    Student(const QString &fio, const QString &numberGroup, int gender, const QList<Subject> &subjects);

    Student(const QString &fio, const QString &numberGroup, int gender);

    const QList<Subject> &getSubjects() const;

    void setSubjects(const QList<Subject> &subjects);

    const QString &getFio() const;

    void setFio(const QString &fio);

    const QString &getNumberGroup() const;

    void setNumberGroup(const QString &numberGroup);

    int getGender() const;

    void setGender(int gender);
};


#endif //DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_STUDENT_H
