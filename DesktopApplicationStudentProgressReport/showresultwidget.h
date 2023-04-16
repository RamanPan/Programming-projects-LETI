#ifndef DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_SHOWRESULTWIDGET_H
#define DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_SHOWRESULTWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class ShowResultWidget; }
QT_END_NAMESPACE

class ShowResultWidget : public QWidget {
Q_OBJECT

public:
    explicit ShowResultWidget(QWidget *parent = nullptr);

    ~ShowResultWidget() override;

private:
    Ui::ShowResultWidget *ui;
};


#endif //DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_SHOWRESULTWIDGET_H
