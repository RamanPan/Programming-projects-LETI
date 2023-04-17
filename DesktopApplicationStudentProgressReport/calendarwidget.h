#ifndef DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_CALENDARWIDGET_H
#define DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_CALENDARWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class CalendarWidget; }
QT_END_NAMESPACE

class CalendarWidget : public QWidget {
Q_OBJECT

public:
    explicit CalendarWidget(QWidget *parent = nullptr);

    ~CalendarWidget() override;

private slots:

    void updateTime();

private:
    Ui::CalendarWidget *ui;
    QTimer *tmr;

};

#endif //DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_CALENDARWIDGET_H
