#include "AddComputerPopup.h"

#include <QVBoxLayout>

AddComputerPopup::AddComputerPopup(QWidget *parent)
    : Popup{parent}
    , _machineName(nullptr)
    , _machineIP(nullptr)
    , _connectButton(nullptr)
{
    SetMemory();
    SetupModules();
}

void AddComputerPopup::SetMemory()
{
    if (this->_machineName == nullptr)
        this->_machineName = new QLineEdit();
    if (this->_machineIP == nullptr)
        this->_machineIP = new QLineEdit();
    if (this->_connectButton == nullptr)
        this->_connectButton = new QPushButton();
}

void AddComputerPopup::SetupModules()
{
    setFixedSize(450, 350);
    SetTitleText("Add Machine");

    _centerWidget->setLayout(new QVBoxLayout());
    _centerWidget->setStyleSheet("QLineEdit\
                                 {\
                                    border-radius: 4px;\
                                    background-color: rgb(227, 229, 232);\
                                    color: rgb(46, 51, 56);\
                                    padding-left: 10px;\
                                    padding-right: 10px;\
                                 }\
                                 QLineEdit:hover \
                                 {\
                                    background-color: rgb(221, 223, 226);\
                                 }\
                                 QLineEdit:focus \
                                 {\
                                    background-color: rgb(215, 220, 226);\
                                 }\
                                 QPushButton\
                                 {\
                                    border-radius: 4px;\
                                    background-color: rgb(118, 179, 157);\
                                    color: rgb(253, 253, 253);\
                                 }\
                                 QPushButton:hover \
                                 {\
                                    background-color: rgb(95, 167, 144);\
                                 }\
                                 QPushButton:pressed \
                                 {\
                                    background-color: rgb(88, 158, 133);\
                                 }\
                                 QPushButton:disabled \
                                 {\
                                    background-color: rgb(17, 17, 17);\
                                 }");

    this->_machineName->setFixedHeight(40);
    this->_machineIP->setFixedHeight(40);
    this->_connectButton->setFixedHeight(40);
    this->_connectButton->setText("Connect");
    connect(this->_connectButton, &QPushButton::clicked, this, &AddComputerPopup::connectButtonPressed);

    QLabel *machineNameLabel = new QLabel();
    machineNameLabel->setText("MACHINE NAME");
    QFont font;
    font.setPointSize(10);
    machineNameLabel->setFont(font);
    _centerWidget->layout()->addWidget(machineNameLabel);
    _centerWidget->layout()->addWidget(this->_machineName);
    QLabel *machineIPLabel = new QLabel();
    machineIPLabel->setText("MACHINE IP");
    machineIPLabel->setFont(font);
    QFont buttonFont = QFont(font);
    buttonFont.setWeight(QFont::Bold);
    this->_connectButton->setFont(buttonFont);
    _centerWidget->layout()->addWidget(machineIPLabel);
    _centerWidget->layout()->addWidget(this->_machineIP);
    _centerWidget->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    _centerWidget->layout()->addWidget(this->_connectButton);
    this->_connectButton->setEnabled(false);
    connect(this->_machineIP, &QLineEdit::textChanged, this, &AddComputerPopup::taskTextChanged);
}

void AddComputerPopup::connectButtonPressed()
{
    emit this->connectedSucces(this->_machineName->text(), this->_machineIP->text());
    emit closeButtonPressed();
}

void AddComputerPopup::taskTextChanged()
{
    if (this->_machineIP->text() == "" || this->_machineIP->text().isEmpty())
    {
        this->_connectButton->setEnabled(false);
    }
    else
    {
        this->_connectButton->setEnabled(true);
    }
}
