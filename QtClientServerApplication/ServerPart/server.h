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

    ~Server() override;

private slots:

    void getNextPending();

    void processingRequest();

    void sendSelectAll();

    void sendSelectWithOneCondition(const QString &key, const QString &value);

    void
    sendSelectWithTwoCondition(const QString &key1, const QString &value1, const QString &key2, const QString &value2);

    void
    sendSelectWithThreeCondition(const QString &key1, const QString &value1, const QString &key2, const QString &value2,
                                 const QString &key3, const QString &value3);

    void sendSelectWithAllCondition(const QString &keyFamily, const QString &valueFamily,
                                    const QString &keyName, const QString &valueName, const QString &keyGroup,
                                    const QString &valueGroup,
                                    const QString &keyGender, const QString &valueGender);

    void sendDeleteAll();

    void sendDeleteWithOneCondition(const QString &key, const QString &value);

    void
    sendDeleteWithTwoCondition(const QString &key1, const QString &value1, const QString &key2, const QString &value2);

    void
    sendDeleteWithThreeCondition(const QString &key1, const QString &value1, const QString &key2, const QString &value2,
                                 const QString &key3, const QString &value3);

    void sendDeleteWithAllCondition(const QString &key1, const QString &value1,
                                    const QString &key2, const QString &value2, const QString &key3,
                                    const QString &value3,
                                    const QString &key4, const QString &value4);

    void
    sendInsertData(const QString &valueF, const QString &valueN, const QString &valueGroup, const QString &valueGender);

private:
    void initServer();

    QLabel *statusLabel = nullptr;
    QTcpServer *tcpServer = nullptr;
    QTcpSocket *conn;
    QList<QString> fortunes;
    QSqlDatabase db;
};

#endif
