#ifndef DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_SHOWRESULTWIDGET_H
#define DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_SHOWRESULTWIDGET_H

#include <QWidget>
#include "models/Student.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ShowResultWidget; }
QT_END_NAMESPACE

class ShowResultWidget : public QWidget {
Q_OBJECT

public:
    explicit ShowResultWidget(QWidget *parent = nullptr);

    ~ShowResultWidget() override;

public slots:

    void findRightData(QString fio, QString numberGroup, int gender);

    void saveAsXlsx();

private:
    Ui::ShowResultWidget *ui;
    QList<Student> students;

    void initTable();

    void initStudents();

    void initConnections();
};


#endif //DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_SHOWRESULTWIDGET_H
