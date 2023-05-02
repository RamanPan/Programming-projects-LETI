#ifndef CLIENT_H
#define CLIENT_H

#include <QDataStream>
#include <QDialog>
#include <QTcpSocket>


QT_BEGIN_NAMESPACE
class QComboBox;

class QLabel;

class QLineEdit;

class QPushButton;

class QTcpSocket;

QT_END_NAMESPACE
namespace Ui {
    class Client;
}

class Client : public QDialog {
Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);

    ~Client() override;

private:
    void initConnections();

private slots:

    void signalInsertDataOn();

    void sendRequestToSelect();

    void sendRequestToInsert();

    void sendRequestToDelete();

    void readResponse();

    void displayError(QAbstractSocket::SocketError socketError);


private:
    QComboBox *hostCombo = nullptr;
    QLineEdit *portLineEdit = nullptr;
    QLabel *statusLabel = nullptr;
    QPushButton *getFortuneButton = nullptr;
    QList<QString> *keys;

    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    QString currentFortune;
    Ui::Client *ui;
};

#endif
