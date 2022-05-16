#include "AddMachinePopup.h"

AddMachinePopup::AddMachinePopup(QWidget *parent)
    : Popup{parent}
    , _machineName(nullptr)
    , _machineIP(nullptr)
    , _connectButton(nullptr)
{
    SetMemory();
    SetupModules();
}

AddMachinePopup::~AddMachinePopup()
{

}

void AddMachinePopup::SetMemory()
{
    if (this->_machineName == nullptr)
        this->_machineName = new QLineEdit();
    if (this->_machineIP == nullptr)
        this->_machineIP = new QLineEdit();
    if (this->_connectButton == nullptr)
        this->_connectButton = new QPushButton();
}

void AddMachinePopup::SetupModules()
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
                                 }");

    this->_machineName->setFixedHeight(40);
    this->_machineIP->setFixedHeight(40);
    this->_connectButton->setFixedHeight(40);
    this->_connectButton->setText("Connect");
    connect(this->_connectButton, &QPushButton::clicked, this, &AddMachinePopup::connectButtonPressed);

    QLabel *machineNameLabel = new QLabel();
    machineNameLabel->setText("MACHINE NAME");
    QFont font = QFont(Settings::GetInstance().GetApplicationFont(Settings::Fonts::SEN_REGULAR), 10);
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
}

void AddMachinePopup::connectButtonPressed()
{
    emit this->connectedSucces(this->_machineName->text(), this->_machineIP->text());
    emit closeButtonPressed();
}
