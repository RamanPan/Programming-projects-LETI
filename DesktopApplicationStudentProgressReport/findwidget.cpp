#include "findwidget.h"
#include "ui_FindWidget.h"


FindWidget::FindWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::FindWidget) {
    ui->setupUi(this);
    initConnections();
}

FindWidget::~FindWidget() {
    delete ui;
}

void FindWidget::initConnections() {
    connect(ui->lineFIO, SIGNAL(textEdited(QString)), this, SLOT(signalInsertDataOn()));
    connect(ui->groupBox, SIGNAL(currentIndexChanged(int)), this, SLOT(signalInsertDataOn()));
    connect(ui->isMen, SIGNAL(clicked(bool)), this, SLOT(signalInsertDataOn()));
    connect(ui->isWomen, SIGNAL(clicked(bool)), this, SLOT(signalInsertDataOn()));
}

void FindWidget::signalInsertDataOn() {
    if (!ui->lineFIO->text().isEmpty() || ui->groupBox->currentIndex() != 0 || ui->isMen->isChecked() ||
        ui->isWomen->isChecked()) emit insertData(true);
    else emit insertData(false);
}

void FindWidget::prepareData() {
    int gender = 0;
    if (ui->isMen->isChecked()) gender = 1;
    else if (ui->isWomen->isChecked()) gender = 2;
    emit dataForView(ui->lineFIO->text(), ui->groupBox->currentText(), gender);
}
