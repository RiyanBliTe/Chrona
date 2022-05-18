#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ComputersManager.h"

#include <QFile>

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

MainWindow& MainWindow::Instance()
{
    static MainWindow instance;
    return instance;
}

void MainWindow::SetMemory()
{
    this->_SettingsButton = new ComputerButton();
    this->_AddNewMachineButton = new ComputerButton();
    this->_PopupModule = new PopupModule(this);
}

void MainWindow::SetupModules()
{
    ui->setupUi(this);

    this->ui->Frame_LeftPanel->setStyleSheet("#Frame_LeftPanel { background-color: " + Settings::GetInstance()._left_panel_background_color + "; }");
    this->ui->Frame_CenterPanel->setStyleSheet("#Frame_CenterPanel { background-color: " + Settings::GetInstance()._center_panel_background_center_color + "; }");
    this->ui->scrollAreaWidgetContents->setStyleSheet("#scrollAreaWidgetContents { background-color: " + Settings::GetInstance()._center_panel_background_center_color + "; }");
    this->ui->Frame_CenterBottom->setStyleSheet("background-color: " + Settings::GetInstance()._center_panel_background_bottom_color + ";");
    this->ui->Frame_RightPanel->setStyleSheet("#Frame_RightPanel { background-color: " + Settings::GetInstance()._right_panel_background_color + "; }");
    this->ui->Widget_TaskControl->setStyleSheet("background-color: " + Settings::GetInstance()._right_panel_background_color + ";");
    this->ui->Widget_ScrollArea->setStyleSheet("#Widget_ScrollArea { background-color: " + Settings::GetInstance()._left_panel_background_color + "; }");


    this->_AddNewMachineButton->SetLeftPanelEnabled(false);
    this->_AddNewMachineButton->SetImage(":/icons_svg/Images/icons_svg/icon_add_machine.svg");

    this->_SettingsButton->SetLeftPanelEnabled(false);
    this->_SettingsButton->SetImage(":/icons_svg/Images/icons_svg/icon_settings.svg");
    this->ui->Widget_Settings->layout()->addWidget(this->_SettingsButton);

    /*this->_machinesList.push_back(new ComputerButton()); // [0] this PC
    this->_machinesList[0]->SetFocused(true);
    this->_machinesList.push_back(new ComputerButton());
    this->_machinesList.push_back(new ComputerButton());
    this->_machinesList.push_back(new ComputerButton());
    this->_machinesList.push_back(new ComputerButton());

    for (int i = 0; i < this->_machinesList.size(); i++)
    {
        this->_machinesList[i]->SetImage(":/icons_svg/Images/icons_svg/icon_machine.svg");
        this->ui->Widget_MachinesList->layout()->addWidget(this->_machinesList[i]);
        connect(this->_machinesList[i], &ComputerButton::focusChanged, this, &MainWindow::machineButtonChangedFocus);
    }*/

    this->ui->Widget_AddNewMachine->layout()->addWidget(this->_AddNewMachineButton);

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
    this->_taskButtonsList[0]->SetStatus(TaskButton::TaskStatus::FAILED);
    this->_taskButtonsList[1]->SetStatus(TaskButton::TaskStatus::IDLE);
    this->_taskButtonsList[2]->SetStatus(TaskButton::TaskStatus::RUNNING);
    this->_taskButtonsList[3]->SetStatus(TaskButton::TaskStatus::SUCCESS);
    this->_taskButtonsList[4]->SetStatus(TaskButton::TaskStatus::SUCCESS);
    this->_taskButtonsList[5]->SetStatus(TaskButton::TaskStatus::FAILED);
    for (int i = 0; i < this->_taskButtonsList.size(); i++)
    {
        this->ui->Widget_TasksList->layout()->addWidget(this->_taskButtonsList[i]);
    }

    this->_PopupModule->hide();
    connect(this->_SettingsButton, &ComputerButton::clicked, this, &MainWindow::settingsButtonClicked);
    connect(this->_AddNewMachineButton, &ComputerButton::clicked, this, &MainWindow::addMachineButtonClicked);
}

void MainWindow::LoadComputers(const QList<Computer*>& list)
{
    for (auto it = list.begin(); it != list.end(); it++)
    {
        ComputerButton *computerButton = new ComputerButton();
        computerButton->SetComputerName((*it)->GetName());
        computerButton->SetComputerIP((*it)->GetIP());
        computerButton->SetComputerPointer(*it);
        if ((*it)->IsThisComputer())
        {
            computerButton->SetFocused(true);
            ui->Label_SelectedMachineName->setText(computerButton->GetComputerName());
            ui->Label_SelectedMachineIP->setText(computerButton->GetComputerIP());
            this->LoadTasks((*it)->GetTasks());
        }
        computerButton->SetImage(":/icons_svg/Images/icons_svg/icon_machine.svg");
        this->ui->Widget_MachinesList->layout()->addWidget(computerButton);
        connect(computerButton, &ComputerButton::focusChanged, this, &MainWindow::machineButtonChangedFocus);
        this->_machinesList.push_back(computerButton);
    }
}

void MainWindow::LoadTasks(const QList<Task*>& list)
{
    if (!this->ui->Widget_TasksList->layout()->isEmpty())
    {
        for (auto it = this->_taskButtonsList.begin(); it != this->_taskButtonsList.end(); it++)
        {
            this->ui->Widget_TasksList->layout()->removeWidget((*it));
        }
    }

    for (auto it = list.begin(); it != list.end(); it++)
    {
        TaskButton *taskButton = new TaskButton();
        this->_taskButtonsList.push_back(taskButton);
        this->ui->Widget_TasksList->layout()->addWidget(taskButton);
    }
}

void MainWindow::machineButtonChangedFocus(ComputerButton *button)
{
    for (auto it = this->_machinesList.begin(); it != this->_machinesList.end(); it++)
    {
        if (*it != button)
        {
            (*it)->SetFocused(false);
        }
    }

    for (auto it = this->_taskButtonsList.begin(); it != this->_taskButtonsList.end(); it++)
    {
        this->ui->Widget_TasksList->layout()->removeWidget((*it));
    }

    this->LoadTasks(COMPUTERS_MANAGER.GetTasksByComputer(button->GetComputerPointer()));
}

void MainWindow::settingsButtonClicked()
{
    this->_PopupModule->setGeometry(0, 0, width(), height());
    this->_PopupModule->raise();
    this->_PopupModule->PushPopup(PopupModule::PopupType::SETTINGS);
    this->_PopupModule->show();
}

void MainWindow::addMachineButtonClicked()
{
    this->_PopupModule->setGeometry(0, 0, width(), height());
    this->_PopupModule->raise();
    this->_PopupModule->PushPopup(PopupModule::PopupType::ADDMACHINE);
    Popup *popup = this->_PopupModule->TopPopup();
    if (popup != nullptr)
    {
        connect(popup, &AddMachinePopup::connectedSucces, this, &MainWindow::AddMachineTriger);
    }
    this->_PopupModule->show();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    this->_PopupModule->setGeometry(0, 0, width(), height());
    this->_PopupModule->Update();
}

void MainWindow::AddMachineTriger(QString machine_name, QString machine_ip)
{
    ComputerButton *but = new ComputerButton();
    this->_machinesList.push_back(but);
    but->SetImage(":/icons_svg/Images/icons_svg/icon_machine.svg");
    this->ui->Widget_MachinesList->layout()->addWidget(but);
    connect(but, &ComputerButton::focusChanged, this, &MainWindow::machineButtonChangedFocus);
}
