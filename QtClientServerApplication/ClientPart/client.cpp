#include <QtWidgets>
#include <QtNetwork>

#include "client.h"
#include "./ui_client.h"


Client::Client(QWidget *parent)
        : QDialog(parent), hostCombo(new QComboBox), portLineEdit(new QLineEdit),
          getFortuneButton(new QPushButton(tr("Get Fortune"))), tcpSocket(new QTcpSocket(this)),
          keys(new QList<QString>({"familystudent ", "namestudent ", "groupstudent ", "genderstudent "})),
          ui(new Ui::Client) {
    hostCombo->setEditable(true);
    QString name = QHostInfo::localHostName();
    if (!name.isEmpty()) {
        hostCombo->addItem(name);
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty())
            hostCombo->addItem(name + QChar('.') + domain);
    }
    if (name != QLatin1String("localhost"))
        hostCombo->addItem(QString("localhost"));
    // find out IP addresses of this machine
    const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (const QHostAddress &entry: ipAddressesList) {
        if (!entry.isLoopback())
            hostCombo->addItem(entry.toString());
    }
    // add localhost addresses
    for (const QHostAddress &entry: ipAddressesList) {
        if (entry.isLoopback())
            hostCombo->addItem(entry.toString());
    }
    portLineEdit->setValidator(new QIntValidator(1, 65535, this));
    auto hostLabel = new QLabel(tr("&Название сервера"));
    hostLabel->setBuddy(hostCombo);
    auto portLabel = new QLabel(tr("&Порт"));
    portLabel->setBuddy(portLineEdit);
    statusLabel = new QLabel(tr("                                       "));
    getFortuneButton->setDefault(true);
    getFortuneButton->setEnabled(false);
    auto quitButton = new QPushButton(tr("Quit"));
    auto buttonBox = new QDialogButtonBox;
    buttonBox->addButton(getFortuneButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_6_5);
    QGridLayout *mainLayout;
    if (QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()) {
        auto outerVerticalLayout = new QVBoxLayout(this);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
        auto outerHorizontalLayout = new QHBoxLayout;
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        auto groupBox = new QGroupBox(QGuiApplication::applicationDisplayName());
        mainLayout = new QGridLayout(groupBox);
        outerHorizontalLayout->addWidget(groupBox);
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        outerVerticalLayout->addLayout(outerHorizontalLayout);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
    } else {
        mainLayout = new QGridLayout(this);
    }
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(hostCombo, 0, 1);
    mainLayout->addWidget(portLabel, 1, 0);
    mainLayout->addWidget(portLineEdit, 1, 1);
    mainLayout->addWidget(statusLabel, 2, 0, 1, 2);
    mainLayout->addWidget(buttonBox, 3, 0, 1, 2);

    setWindowTitle(QGuiApplication::applicationDisplayName());
    portLineEdit->setFocus();
    getFortuneButton->hide();
    ui->setupUi(this);
    ui->addButton->setEnabled(false);
    buttonBox->hide();
    initConnections();

}

void Client::signalInsertDataOn() {
    ui->addButton->setEnabled(!ui->familyEdit->text().isEmpty()
                              && !ui->nameEdit->text().isEmpty()
                              && ui->groupBox->currentIndex() != 0
                              && ui->genderBox->currentIndex() != 0);
}

void Client::sendRequestToSelect() {
    tcpSocket->abort();
    tcpSocket->connectToHost(hostCombo->currentText(),
                             portLineEdit->text().toInt());
    tcpSocket->write("SELECT ");
    std::string text;
    if (!ui->familyEdit->text().isEmpty()) {
        tcpSocket->write(keys->at(0).toStdString().c_str());
        text = ui->familyEdit->text().toStdString() + " ";
        tcpSocket->write(text.c_str());
    }
    if (!ui->nameEdit->text().isEmpty()) {
        tcpSocket->write(keys->at(1).toStdString().c_str());
        text = ui->nameEdit->text().toStdString() + " ";
        tcpSocket->write(text.c_str());

    }
    if (ui->groupBox->currentIndex() != 0) {
        tcpSocket->write(keys->at(2).toStdString().c_str());
        text = ui->groupBox->currentText().toStdString() + " ";
        tcpSocket->write(text.c_str());
    }
    if (ui->genderBox->currentIndex() != 0) {
        tcpSocket->write(keys->at(3).toStdString().c_str());
        text = ui->genderBox->currentText().toStdString();
        tcpSocket->write(text.c_str());
    }

}

void Client::sendRequestToInsert() {
    tcpSocket->abort();
    tcpSocket->connectToHost(hostCombo->currentText(),
                             portLineEdit->text().toInt());
    tcpSocket->write("INSERT ");
    std::string text;
    text = "'" + ui->familyEdit->text().toStdString() + "' ";
    tcpSocket->write(text.c_str());
    text = "'" + ui->nameEdit->text().toStdString() + "' ";
    tcpSocket->write(text.c_str());
    text = "'" + ui->groupBox->currentText().toStdString() + "' ";
    tcpSocket->write(text.c_str());
    text = "'" + ui->genderBox->currentText().toStdString() + "'";
    tcpSocket->write(text.c_str());

}

void Client::sendRequestToDelete() {
    tcpSocket->abort();
    tcpSocket->connectToHost(hostCombo->currentText(),
                             portLineEdit->text().toInt());
    tcpSocket->write("DELETE ");
    std::string text;
    if (!ui->familyEdit->text().isEmpty()) {
        tcpSocket->write(keys->at(0).toStdString().c_str());
        text = ui->familyEdit->text().toStdString() + " ";
        tcpSocket->write(text.c_str());
    }
    if (!ui->nameEdit->text().isEmpty()) {
        tcpSocket->write(keys->at(1).toStdString().c_str());
        text = ui->nameEdit->text().toStdString() + " ";
        tcpSocket->write(text.c_str());

    }
    if (ui->groupBox->currentIndex() != 0) {
        tcpSocket->write(keys->at(2).toStdString().c_str());
        text = ui->groupBox->currentText().toStdString() + " ";
        tcpSocket->write(text.c_str());
    }
    if (ui->genderBox->currentIndex() != 0) {
        tcpSocket->write(keys->at(3).toStdString().c_str());
        text = ui->genderBox->currentText().toStdString();
        tcpSocket->write(text.c_str());
    }

}


void Client::readResponse() {
    QMessageBox::information(this, "Результат запроса", tcpSocket->readAll());
}

void Client::initConnections() {
    connect(ui->findButton, &QAbstractButton::clicked,
            this, &Client::sendRequestToSelect);
    connect(ui->addButton, &QAbstractButton::clicked,
            this, &Client::sendRequestToInsert);
    connect(ui->deleteButton, &QAbstractButton::clicked,
            this, &Client::sendRequestToDelete);
    connect(tcpSocket, &QIODevice::readyRead, this, &Client::readResponse);
    connect(tcpSocket, &QAbstractSocket::errorOccurred,
            this, &Client::displayError);
    connect(ui->familyEdit, SIGNAL(textEdited(QString)), this, SLOT(signalInsertDataOn()));
    connect(ui->groupBox, SIGNAL(currentIndexChanged(int)), this, SLOT(signalInsertDataOn()));
    connect(ui->nameEdit, SIGNAL(textEdited(QString)), this, SLOT(signalInsertDataOn()));
    connect(ui->genderBox, SIGNAL(currentIndexChanged(int)), this, SLOT(signalInsertDataOn()));

}

void Client::displayError(QAbstractSocket::SocketError socketError) {
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, tr("Client Part"),
                                     tr("Хост не был найден. Проверьте имя хоста и номер порта."));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, tr("Client Part"),
                                     tr("Связь не была установлена. "
                                        "Убедитесь что сервер включен "
                                        "и проверьте имя хоста и номер порта."));
            break;
        default:
            QMessageBox::information(this, tr("Client Part"),
                                     tr("Ошибка: Проверьте имя хоста и номер порта.")
                                             .arg(tcpSocket->errorString()));
    }

    getFortuneButton->setEnabled(true);
}


Client::~Client() {
    delete ui;
}


