#ifndef DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_SUBJECT_H
#define DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_SUBJECT_H


#include <QString>

class Subject {
private:
    QString name;
    int mark;
public:
    Subject();

    Subject(const QString &name, int mark);

    const QString &getName() const;

    void setName(const QString &name);

    int getMark() const;

    void setMark(int mark);
};


#endif //DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_SUBJECT_H
