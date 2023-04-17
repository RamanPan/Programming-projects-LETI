#ifndef DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_FINDWIDGET_H
#define DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_FINDWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class FindWidget; }
QT_END_NAMESPACE

class FindWidget : public QWidget {
Q_OBJECT

public:
    explicit FindWidget(QWidget *parent = nullptr);

    ~FindWidget() override;

signals:

    void insertData(bool flag);

    void dataForView(QString fio, QString numberGroup, int gender);

public slots:

    void signalInsertDataOn();

public:
    void prepareData();

private:
    Ui::FindWidget *ui;

    void initConnections();
};


#endif //DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_FINDWIDGET_H
