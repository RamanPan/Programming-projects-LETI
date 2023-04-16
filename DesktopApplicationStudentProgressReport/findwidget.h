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

private:
    Ui::FindWidget *ui;
};


#endif //DESKTOPAPPLICATIONSTUDENTPROGRESSREPORT_FINDWIDGET_H
