#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <QDataStream>
#include <QSqlQuery>

#include "server.h"

Server::Server(QWidget *parent)
        : QDialog(parent), statusLabel(new QLabel) {
    statusLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    initServer();
    fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
             << tr("You've got to think about tomorrow.")
             << tr("You will be surprised by a loud noise.")
             << tr("You will feel hungry again in another hour.")
             << tr("You might have mail.")
             << tr("You cannot kill time without injuring eternity.")
             << tr("Computers are not intelligent. They only think they are.");
    auto quitButton = new QPushButton(tr("Выход"));
    quitButton->setAutoDefault(false);
    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::getNextPending);
    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout * mainLayout = nullptr;
    if (QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()) {
        auto outerVerticalLayout = new QVBoxLayout(this);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
        auto outerHorizontalLayout = new QHBoxLayout;
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        auto groupBox = new QGroupBox(QGuiApplication::applicationDisplayName());
        mainLayout = new QVBoxLayout(groupBox);
        outerHorizontalLayout->addWidget(groupBox);
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        outerVerticalLayout->addLayout(outerHorizontalLayout);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
    } else {
        mainLayout = new QVBoxLayout(this);
    }

    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);

    setWindowTitle(QGuiApplication::applicationDisplayName());
}

void Server::getNextPending() {
    conn = tcpServer->nextPendingConnection();
    connect(conn, &QTcpSocket::readyRead, this, &Server::processingRequest);
}

void Server::initServer() {
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen()) {
        QMessageBox::critical(this, tr("Server"),
                              tr("Unable to start the server: %1.")
                                      .arg(tcpServer->errorString()));
        close();
        return;
    }
    QString ipAddress;
    const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (const QHostAddress &entry: ipAddressesList) {
        if (entry != QHostAddress::LocalHost && entry.toIPv4Address()) {
            ipAddress = entry.toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    statusLabel->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n")
                                 .arg(ipAddress).arg(tcpServer->serverPort()));
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("LastLab");
    db.setPort(5432);
    db.setPassword("1234");
    db.setUserName("postgres");
    db.setHostName("localhost");
    db.open();
}


void Server::processingRequest() {
    QList<QString> list;
    for (const auto &arr: conn->readAll().split(' ')) {
        list.append(QString(arr));
    }
    std::string firstLine = list.at(0).toStdString();
    if (firstLine == "SELECT") {
        switch (list.size()) {
            default:
                sendSelectAll();
                break;
            case 3:
            case 4:
                sendSelectWithOneCondition(list.at(1), list.at(2));
                break;
            case 5:
            case 6:
                sendSelectWithTwoCondition(list.at(1), list.at(2), list.at(3), list.at(4));
                break;
            case 7:
            case 8:
                sendSelectWithThreeCondition(list.at(1), list.at(2), list.at(3), list.at(4), list.at(5),
                                             list.at(6));
                break;
            case 9:
            case 10:
                sendSelectWithAllCondition(list.at(1), list.at(2), list.at(3), list.at(4), list.at(5), list.at(6),
                                           list.at(7), list.at(8));
                break;
        }
    } else if (firstLine == "DELETE") {
        switch (list.size()) {
            default:
                sendDeleteAll();
                break;
            case 3:
            case 4:
                sendDeleteWithOneCondition(list.at(1), list.at(2));
                break;
            case 5:
            case 6:
                sendDeleteWithTwoCondition(list.at(1), list.at(2), list.at(3), list.at(4));
                break;
            case 7:
            case 8:
                sendDeleteWithThreeCondition(list.at(1), list.at(2), list.at(3), list.at(4), list.at(5),
                                             list.at(6));
                break;
            case 9:
            case 10:
                sendDeleteWithAllCondition(list.at(1), list.at(2), list.at(3), list.at(4), list.at(5), list.at(6),
                                           list.at(7), list.at(8));
                break;
        }
    } else if (firstLine == "INSERT") sendInsertData(list.at(1), list.at(2), list.at(3), list.at(4));
    connect(conn, &QAbstractSocket::disconnected,
            conn, &QObject::deleteLater);
    conn->disconnectFromHost();
}

void Server::sendSelectAll() {
    QSqlQuery query("SELECT * FROM student", db);
    QString column;
    if (query.exec("SELECT * FROM student")) {
        while (query.next()) {
            column +=
                    query.value(1).toString() + " " + query.value(2).toString() + " " + query.value(3).toString() +
                    " " + query.value(4).toString() + "\n";
        }
    }
    if (column.isEmpty()) column = "По заданным параметрам записей в БД нет";
    conn->write(column.toStdString().c_str());
}

void Server::sendSelectWithOneCondition(const QString &key, const QString &value) {
    QSqlQuery query(db);
    QString column;
    if (query.exec("SELECT * FROM student WHERE " + key + " = " + '\'' + value + '\'')) {
        while (query.next()) {
            column +=
                    query.value(1).toString() + " " + query.value(2).toString() + " " + query.value(3).toString() +
                    " " + query.value(4).toString() + "\n";
        }
    } else column = "Ошибка";
    if (column.isEmpty()) column = "По заданным параметрам записей в БД нет";
    conn->write(column.toStdString().c_str());
}

void Server::sendSelectWithTwoCondition(const QString &key1, const QString &value1, const QString &key2,
                                        const QString &value2) {
    QSqlQuery query(db);
    QString column;
    if (query.exec("SELECT * FROM student WHERE " + key1 + " = " + '\'' + value1 + '\'' + " AND " +
                   key2 + " = " + '\'' + value2 + '\'')) {

        while (query.next()) {
            column +=
                    query.value(1).toString() + " " + query.value(2).toString() + " " + query.value(3).toString() +
                    " " + query.value(4).toString() + "\n";
        }
    } else column = "Ошибка";
    if (column.isEmpty()) column = "По заданным параметрам записей в БД нет";
    conn->write(column.toStdString().c_str());
}

void Server::sendSelectWithThreeCondition(const QString &key1, const QString &value1, const QString &key2,
                                          const QString &value2,
                                          const QString &key3, const QString &value3) {
    QSqlQuery query(db);
    QString column;
    if (query.exec("SELECT * FROM student WHERE " + key1 + " = " + '\'' + value1 + '\'' + " AND " +
                   key2 + " = " + '\'' + value2 + '\'' + " AND " +
                   key3 + " = " + '\'' + value3 + '\'')) {
        while (query.next()) {
            column +=
                    query.value(1).toString() + " " + query.value(2).toString() + " " + query.value(3).toString() +
                    " " + query.value(4).toString() + "\n";
        }
    } else column = "Ошибка";
    if (column.isEmpty()) column = "По заданным параметрам записей в БД нет";
    conn->write(column.toStdString().c_str());
}

void Server::sendSelectWithAllCondition(const QString &key1, const QString &value1,
                                        const QString &key2, const QString &value2, const QString &key3,
                                        const QString &value3,
                                        const QString &key4, const QString &value4) {
    QSqlQuery query(db);
    QString column;
    if (query.exec("SELECT * FROM student WHERE " + key1 + " = " + '\'' + value1 + '\'' + " AND " +
                   key2 + " = " + '\'' + value2 + '\'' + " AND " +
                   key3 + " = " + '\'' + value3 + '\'' + " AND " +
                   key4 + " = " + '\'' + value4 + '\'')) {
        while (query.next()) {
            column +=
                    query.value(1).toString() + " " + query.value(2).toString() + " " + query.value(3).toString() +
                    " " + query.value(4).toString() + "\n";
        }
    }
    if (column.isEmpty()) column = "По заданным параметрам записей в БД нет";
    conn->write(column.toStdString().c_str());

}

void Server::sendDeleteAll() {
    QSqlQuery query(db);
    QString column;
    if (query.exec("DELETE FROM student")) {
        column = "Все записи успешно удалены";
    } else column = "Не удалось удалить";
    conn->write(column.toStdString().c_str());
}

void Server::sendDeleteWithOneCondition(const QString &key, const QString &value) {
    QSqlQuery query(db);
    QString column;
    if (query.exec("DELETE FROM student WHERE " + key + " = " + '\'' + value + '\'')) column = "Запись успешно удалена";
    else column = "Ошибка: Запись не найдена";
    conn->write(column.toStdString().c_str());
}

void Server::sendDeleteWithTwoCondition(const QString &key1, const QString &value1, const QString &key2,
                                        const QString &value2) {
    QSqlQuery query(db);
    QString column;
    if (query.exec("DELETE FROM student WHERE " + key1 + " = " + '\'' + value1 + '\'' + " AND " +
                   key2 + " = " + '\'' + value2 + '\''))
        column = "Запись успешно удалена";
    else column = "Ошибка: Запись не найдена";
    conn->write(column.toStdString().c_str());
}

void Server::sendDeleteWithThreeCondition(const QString &key1, const QString &value1, const QString &key2,
                                          const QString &value2,
                                          const QString &key3, const QString &value3) {
    QSqlQuery query(db);
    QString column;
    if (query.exec("DELETE FROM student WHERE " + key1 + " = " + '\'' + value1 + '\'' + " AND " +
                   key2 + " = " + '\'' + value2 + '\'' + " AND " +
                   key3 + " = " + '\'' + value3 + '\''))
        column = "Запись успешна удалена";
    else column = "Ошибка: Запись не найдена";
    conn->write(column.toStdString().c_str());
}

void Server::sendDeleteWithAllCondition(const QString &key1, const QString &value1,
                                        const QString &key2, const QString &value2, const QString &key3,
                                        const QString &value3,
                                        const QString &key4, const QString &value4) {
    QSqlQuery query(db);
    QString column;
    if (query.exec("DELETE FROM student WHERE " + key1 + " = " + '\'' + value1 + '\'' + " AND " +
                   key2 + " = " + '\'' + value2 + '\'' + " AND " +
                   key3 + " = " + '\'' + value3 + '\'' + " AND " +
                   key4 + " = " + '\'' + value4 + '\''))
        column = "Запись успешна удалена";
    else column = "Ошибка: Запись не найдена";
    conn->write(column.toStdString().c_str());
}

void Server::sendInsertData(const QString &valueF, const QString &valueN, const QString &valueGroup,
                            const QString &valueGender) {
    QSqlQuery query(db);
    QString column;
    if (query.exec("INSERT INTO student(familystudent,namestudent,groupstudent,genderstudent) VALUES("
                   + valueF + ", " + valueN + ", " + valueGroup + ", " + valueGender +
                   ")"))
        column = "Запись успешна добавлена";
    else column = "Ошибка: Запись не добавлена";
    conn->write(column.toStdString().c_str());
}

Server::~Server() {
    delete conn;
    delete statusLabel;
    db.close();
}

