#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <QDataStream>

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
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::processingRequest);
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
    db.setPassword("1234");
    db.setUserName("postgres");
    db.setHostName("LastLabOnEarth");
}


void Server::processingRequest() {
//    QByteArray block;
//    QDataStream out(&block, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);

//    out << fortunes[QRandomGenerator::global()->bounded(fortunes.size())];
    QList<QString> list;
    QTcpSocket *conn = tcpServer->nextPendingConnection();
    while (conn->canReadLine()) {
        QString data = QString(conn->readLine());
        list.append(data);
    }
    std::string firstLine = list.at(0).toStdString();
    if (firstLine == "SELECT") {
        switch (list.size()) {
            case 1:
                sendSelectAll(conn);
                break;
            case 3:
                sendSelectWithOneCondition(conn, list.at(1), list.at(2));
                break;
            case 5:
                sendSelectWithTwoCondition(conn, list.at(1), list.at(2), list.at(3), list.at(4));
                break;
            case 7:
                sendSelectWithThreeCondition(conn, list.at(1), list.at(2), list.at(3), list.at(4), list.at(5),
                                             list.at(6));
                break;
            case 9:
                sendSelectWithAllCondition(conn, list.at(1), list.at(2), list.at(3), list.at(4), list.at(5), list.at(6),
                                           list.at(7), list.at(8));
                break;
        }
    } else if (firstLine == "DELETE") {
        switch (list.size()) {
            case 1:
                sendDeleteAll(conn);
                break;
            case 3:
                sendDeleteWithOneCondition(conn, list.at(1), list.at(2));
                break;
            case 5:
                sendDeleteWithTwoCondition(conn, list.at(1), list.at(2), list.at(3), list.at(4));
                break;
            case 7:
                sendDeleteWithThreeCondition(conn, list.at(1), list.at(2), list.at(3), list.at(4), list.at(5),
                                             list.at(6));
                break;
            case 9:
                sendDeleteWithAllCondition(conn, list.at(1), list.at(2), list.at(3), list.at(4), list.at(5), list.at(6),
                                           list.at(7), list.at(8));
                break;
        }
    } else if (firstLine == "INSERT") sendInsertData(conn, list.at(1), list.at(2), list.at(3), list.at(4));
//    connect(conn, &QAbstractSocket::disconnected,
//            conn, &QObject::deleteLater);

//    conn->write(block);
//    conn->disconnectFromHost();
}

void Server::sendSelectAll(QTcpSocket *conn) {

}

