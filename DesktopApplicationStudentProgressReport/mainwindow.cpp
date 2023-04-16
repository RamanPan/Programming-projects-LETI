#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "findwidget.h"
#include "showresultwidget.h"
#include "calendarwidget.h"

#include <QGridLayout>


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Лучшее приложение на свете");
    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->setTabShape(QTabWidget::Triangular);
    tabWidget->setTabPosition(QTabWidget::North);

    QWidget *pageWidget_0 = new FindWidget(this);
    QWidget *pageWidget_1 = new ShowResultWidget(this);
    QWidget *pageWidget_2 = new CalendarWidget(this);

    tabWidget->addTab(pageWidget_0, "Поиск студента");
    tabWidget->addTab(pageWidget_1, "Результаты поиска");
    tabWidget->addTab(pageWidget_2, "Календарь");
//    tabWidget->setTabEnabled(1,false);
    this->resize(950, 500);
    this->setCentralWidget(tabWidget);
}

MainWindow::~MainWindow() {
    delete ui;
}


