#include <QFileDialog>
#include <QAxObject>
#include "showresultwidget.h"
#include "ui_ShowResultWidget.h"

ShowResultWidget::ShowResultWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::ShowResultWidget) {
    ui->setupUi(this);
    initStudents();
    initConnections();
}

ShowResultWidget::~ShowResultWidget() {
    delete ui;
}

void ShowResultWidget::initTable() {
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(
            QStringList() << tr("ФИО") << tr("Дисциплина") << tr("Оценка"));
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setColumnWidth(0, 293);
    ui->tableWidget->setColumnWidth(1, 293);
    ui->tableWidget->setColumnWidth(2, 240);
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->setEditTriggers(static_cast<QFlag>(0));
}

void ShowResultWidget::findRightData(QString fio, QString numberGroup, int gender) {
    initTable();
    bool isAlwaysRightFIO = fio.isEmpty(), isAlwaysRightNumber = numberGroup.isEmpty(), isAlwaysRightGender =
            gender == 0;
    bool isRightFIO, isRightNumber, isRightGender;
    for (const Student &student: students) {
        if (isAlwaysRightFIO) isRightFIO = true;
        else {
            if (student.getFio().startsWith(fio)) isRightFIO = true;
            else isRightFIO = false;
        }
        if (isAlwaysRightNumber) isRightNumber = true;
        else {
            if (student.getNumberGroup() == numberGroup) isRightNumber = true;
            else isRightNumber = false;
        }
        if (isAlwaysRightGender) isRightGender = true;
        else {
            if (student.getGender() == gender) isRightGender = true;
            else isRightGender = false;
        }
        if (isRightFIO && isRightNumber && isRightGender) {
            for (const Subject &s: student.getSubjects()) {

                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(student.getFio()));
                ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1,
                                         new QTableWidgetItem(s.getName()));
                ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2,
                                         new QTableWidgetItem(QString::number(s.getMark())));
            }

        }
    }
}


void ShowResultWidget::saveAsXlsx() {
    QString filepath = QFileDialog::getSaveFileName(this, tr("Save"), ".", tr(" (*.xlsx)"));
    if (!filepath.isEmpty()) {
        QAxObject *excel = new QAxObject(this);
        excel->setControl("Excel.Application");
        excel->dynamicCall("SetVisible (bool Visible)", "false");
        excel->setProperty("DisplayAlerts", false);
        QAxObject *workbooks = excel->querySubObject("WorkBooks");
        workbooks->dynamicCall("Add");
        QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
        QAxObject *worksheets = workbook->querySubObject("Sheets");
        QAxObject *worksheet = worksheets->querySubObject("Item(int)", 1);
        for (int i = 1; i < ui->tableWidget->columnCount() + 1; i++) {
            QAxObject *Range = worksheet->querySubObject("Cells(int,int)", 1, i);
            Range->dynamicCall("SetValue(const QString &)", ui->tableWidget->horizontalHeaderItem(i - 1)->text());
        }
        for (int i = 1; i < ui->tableWidget->rowCount() + 1; i++) {
            for (int j = 1; j < ui->tableWidget->columnCount() + 1; j++) {
                QAxObject *Range = worksheet->querySubObject("Cells(int,int)", i + 1, j);
                Range->dynamicCall("SetValue(const QString &)",
                                   ui->tableWidget->item(i - 1, j - 1)->data(Qt::DisplayRole).toString());
            }
        }
        workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filepath));
        workbook->dynamicCall("Close()");
        excel->dynamicCall("Quit()");
        delete excel;
        excel = nullptr;
    }
}

void ShowResultWidget::initConnections() {
    connect(ui->exportButton, SIGNAL(clicked(bool)), this, SLOT(saveAsXlsx()));
}

void ShowResultWidget::initStudents() {
    students.push_back(*(new Student("Врублевская Любовь Максимовна", "2375", 2,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 5)), *(new Subject("АиГ", 5)),
                                                           *(new Subject("Программирование", 5))})))));
    students.push_back(*(new Student("Панаёт Роман Тудорович", "2375", 1,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 5)), *(new Subject("АиГ", 5)),
                                                           *(new Subject("Программирование", 5))})))));
    students.push_back(*(new Student("Ашанин Андрей Юрьевич", "2375", 1,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 4)), *(new Subject("АиГ", 4)),
                                                           *(new Subject("Программирование", 4))})))));
    students.push_back(*(new Student("Беберина Камилла Юрьевна", "2375", 2,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 3)), *(new Subject("АиГ", 4)),
                                                           *(new Subject("Программирование", 3))})))));
    students.push_back(*(new Student("Данейкий Андрей Александрович", "2375", 1,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 2)), *(new Subject("АиГ", 2)),
                                                           *(new Subject("Программирование", 4))})))));
    students.push_back(*(new Student("Токарев Иван Дмитриевич", "2375", 1,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 5)), *(new Subject("АиГ", 5)),
                                                           *(new Subject("Программирование", 5))})))));
    students.push_back(*(new Student("Иванченко Архип Павлович", "2375", 1,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 5)), *(new Subject("АиГ", 4)),
                                                           *(new Subject("Программирование", 5))})))));
    students.push_back(*(new Student("Иванов Дмитрий Кириллович", "2375", 1,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 2)), *(new Subject("АиГ", 2)),
                                                           *(new Subject("Программирование", 2))})))));
    students.push_back(*(new Student("Кузьмичева Юнона", "2395", 2,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 5)), *(new Subject("АиГ", 5)),
                                                           *(new Subject("Программирование", 5))})))));
    students.push_back(*(new Student("Карпова Александра", "2374", 2,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 5)), *(new Subject("АиГ", 5)),
                                                           *(new Subject("Программирование", 5))})))));
    students.push_back(*(new Student("Рагозина Татьяна", "2374", 2,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 5)), *(new Subject("АиГ", 4)),
                                                           *(new Subject("Программирование", 4))})))));
    students.push_back(*(new Student("Щеглова Варвара", "2374", 2,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 4)), *(new Subject("АиГ", 4)),
                                                           *(new Subject("Программирование", 4))})))));
    students.push_back(*(new Student("Пулина Ангелина", "2395", 2,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 4)), *(new Subject("АиГ", 4)),
                                                           *(new Subject("Программирование", 5))})))));
    students.push_back(*(new Student("Сергеева Арина", "2395", 2,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 3)), *(new Subject("АиГ", 3)),
                                                           *(new Subject("Программирование", 3))})))));
    students.push_back(*(new Student("Крачковская Анастасия", "2374", 2,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 5)), *(new Subject("АиГ", 5)),
                                                           *(new Subject("Программирование", 5))})))));
    students.push_back(*(new Student("Лукашин Владимир", "2374", 1,
                                     *(new QList<Subject>({*(new Subject("МАТАН", 5)), *(new Subject("АиГ", 5)),
                                                           *(new Subject("Программирование", 5))})))));
}
