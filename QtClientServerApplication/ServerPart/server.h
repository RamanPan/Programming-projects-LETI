#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
class QLabel;

class QTcpServer;

QT_END_NAMESPACE

//! [0]
class Server : public QDialog {
Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);

private slots:

    void processingRequest();

    void sendSelectAll(QTcpSocket *conn);

    void sendSelectWithOneCondition(QTcpSocket *conn, QString key, QString value);

    void sendSelectWithTwoCondition(QTcpSocket *conn, QString key1, QString value1, QString key2, QString value2);

    void sendSelectWithThreeCondition(QTcpSocket *conn, QString key, QString value, QString key2, QString value2,
                                      QString key3, QString value3);

    void sendSelectWithAllCondition(QTcpSocket* conn, QString keyFamily, QString valueFamily,
                                    QString keyName, QString valueName, QString keyGroup, QString valueGroup,
                                    QString keyGender, QString valueGender);

    void sendDeleteAll(QTcpSocket *conn);

    void sendDeleteWithOneCondition(QTcpSocket *conn, QString key, QString value);

    void sendDeleteWithTwoCondition(QTcpSocket *conn, QString key1, QString value1, QString key2, QString value2);

    void sendDeleteWithThreeCondition(QTcpSocket *conn, QString key, QString value, QString key2, QString value2,
                                      QString key3, QString value3);

    void sendDeleteWithAllCondition(QTcpSocket* conn, QString keyFamily, QString valueFamily,
                                    QString keyName, QString valueName, QString keyGroup, QString valueGroup,
                                    QString keyGender, QString valueGender);

    void sendInsertData(QTcpSocket* conn,QString valueF,QString valueN,QString valueGroup, QString valueGender);

private:
    void initServer();

    QLabel *statusLabel = nullptr;
    QTcpServer *tcpServer = nullptr;
    QList<QString> fortunes;
    QSqlDatabase db;
};
//! [0]

#endif
