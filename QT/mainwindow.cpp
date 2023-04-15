//
// Created by vpana on 13.04.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QLineEdit>
#include <QPushButton>

#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(handlePushButton()));

}
void MainWindow::handlePushButton()
{
    QMessageBox::information(this,"Полезная информация","Введенное ФИО: " + ui->line->text());
}
MainWindow::~MainWindow() {
    delete ui;
}
