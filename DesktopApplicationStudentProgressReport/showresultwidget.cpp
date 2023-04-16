#include "showresultwidget.h"
#include "ui_ShowResultWidget.h"


ShowResultWidget::ShowResultWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::ShowResultWidget) {
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(
        QStringList()<<tr("ФИО")<<tr("Дисциплина")<<tr("Оценка"));
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setColumnWidth(0,293);
    ui->tableWidget->setColumnWidth(1,293);
    ui->tableWidget->setColumnWidth(2,293);
}

ShowResultWidget::~ShowResultWidget() {
    delete ui;
}
