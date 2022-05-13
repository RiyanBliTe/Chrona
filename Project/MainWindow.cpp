#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QHostAddress>
#include <QNetworkInterface>
#include <QHostInfo>

#include "Settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    SetMemory();
    SetupModules();
    Settings::GetInstance();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetMemory()
{
    this->_SettingsButton = new LeftBorderButton();
    this->_AddNewMachineButton = new LeftBorderButton();
}

void MainWindow::SetupModules()
{
    ui->setupUi(this);
    ui->Label_SelectedMachineName->setText(QSysInfo::machineHostName());

    QString ipString = "";
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
        {
             ipString = address.toString();
             break;
        }
    }
    ui->Label_SelectedMachineIP->setText(ipString);

    this->_AddNewMachineButton->SetLeftPanelEnabled(false);
    this->_AddNewMachineButton->SetImage(":/icons_svg/Images/icons_svg/icon_add_machine.svg");
    this->ui->Widget_AddNewMachine->layout()->addWidget(this->_AddNewMachineButton);

    this->_SettingsButton->SetLeftPanelEnabled(false);
    this->_SettingsButton->SetImage(":/icons_svg/Images/icons_svg/icon_settings.svg");
    this->ui->Widget_Settings->layout()->addWidget(this->_SettingsButton);

    this->_machinesList.push_back(new LeftBorderButton()); // [0] this PC
    this->_machinesList[0]->SetFocused(true);
    this->_machinesList.push_back(new LeftBorderButton());
    this->_machinesList.push_back(new LeftBorderButton());
    this->_machinesList.push_back(new LeftBorderButton());
    this->_machinesList.push_back(new LeftBorderButton());

    for (int i = 0; i < this->_machinesList.size(); i++)
    {
        this->_machinesList[i]->SetImage(":/icons_svg/Images/icons_svg/icon_machine.svg");
        this->ui->Widget_MachinesList->layout()->addWidget(this->_machinesList[i]);
        connect(this->_machinesList[i], &LeftBorderButton::focusChanged, this, &MainWindow::machineButtonChangedFocus);
    }

    this->_topButtons.push_back(new TopMenuButton());
    this->_topButtons.push_back(new TopMenuButton());
    this->_topButtons.push_back(new TopMenuButton());
    this->_topButtons.push_back(new TopMenuButton());
    this->_topButtons.push_back(new TopMenuButton());
    for (int i = 0; i < this->_topButtons.size(); i++)
    {
        this->ui->Widget_TopButtonsList->layout()->addWidget(this->_topButtons[i]);
    }

    this->ui->Widget_ToogleButton->layout()->addWidget(new ToogleButton());

    this->_taskButtonsList.push_back(new TaskButton());
    this->_taskButtonsList.push_back(new TaskButton());
    this->_taskButtonsList.push_back(new TaskButton());
    this->_taskButtonsList.push_back(new TaskButton());
    this->_taskButtonsList.push_back(new TaskButton());
    this->_taskButtonsList.push_back(new TaskButton());
    for (int i = 0; i < this->_taskButtonsList.size(); i++)
    {
        this->ui->Widget_TasksList->layout()->addWidget(this->_taskButtonsList[i]);
    }
}

void MainWindow::machineButtonChangedFocus(LeftBorderButton *button)
{
    for (auto it = this->_machinesList.begin(); it != this->_machinesList.end(); it++)
    {
        if (*it != button)
        {
            (*it)->SetFocused(false);
        }
    }
}
