
#include "calendarwidget.h"
#include "ui_CalendarWidget.h"

#include <QTimer>


CalendarWidget::CalendarWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::CalendarWidget) {
    ui->setupUi(this);
    tmr = new QTimer();
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();

}

void CalendarWidget::updateTime() {
    ui->labelTime->setText(QTime::currentTime().toString("hh:mm:ss"));
}

CalendarWidget::~CalendarWidget() {
    delete ui;
    delete tmr;
}
