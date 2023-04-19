#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "findwidget.h"
#include "showresultwidget.h"
#include "calendarwidget.h"

#include <QGridLayout>
#include <utility>


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("Лучшее приложение на свете");
    resize(950, 500);
    initWidgets();
    initConnections();
    setCentralWidget(tabWidget);
}

void MainWindow::enableTab(bool flag) {
    tabWidget->setTabEnabled(1, flag);
}

MainWindow::~MainWindow() {
    delete ui;
    delete findWidget;
    delete viewWidget;
    delete calendarWidget;
}

void MainWindow::initWidgets() {
    tabWidget = new QTabWidget(this);
    tabWidget->setTabShape(QTabWidget::Triangular);
    tabWidget->setTabPosition(QTabWidget::North);

    findWidget = new FindWidget(this);
    viewWidget = new ShowResultWidget(this);
    calendarWidget = new CalendarWidget(this);

    tabWidget->addTab(findWidget, "Поиск студента");
    tabWidget->addTab(viewWidget, "Результаты поиска");
    tabWidget->addTab(calendarWidget, "Календарь");
    tabWidget->setTabEnabled(1, false);

}

void MainWindow::initConnections() {
    connect(findWidget, SIGNAL(insertData(bool)),
            this, SLOT(enableTab(bool)));
    connect(tabWidget, SIGNAL(tabBarClicked(int)),
            this, SLOT(checkNumberTabClicked(int)));
    connect(findWidget, SIGNAL(dataForView(QString, QString, int)),
            this, SLOT(sendRightData(QString, QString, int)));
}

void MainWindow::checkNumberTabClicked(int num) {
    if (num == 1) {
        findWidget->prepareData();
    }
}

void MainWindow::sendRightData(QString fio, QString numberGroup, int gender) {
    viewWidget->findRightData(std::move(fio), std::move(numberGroup), gender);
}


