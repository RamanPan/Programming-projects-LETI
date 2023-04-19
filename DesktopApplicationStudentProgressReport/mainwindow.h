
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "findwidget.h"
#include "showresultwidget.h"
#include "calendarwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public slots:

    void enableTab(bool flag);

    void checkNumberTabClicked(int num);

    void sendRightData(QString fio, QString numberGroup, int gender);

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FindWidget *findWidget;
    ShowResultWidget *viewWidget;
    CalendarWidget *calendarWidget;
    QTabWidget *tabWidget;

    void initWidgets();

    void initConnections();

};

#endif // MAINWINDOW_H
