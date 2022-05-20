#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../Controller/ComputersManager.h"
#include "../Controller/SaveManager.h"

#include <QFile>

#include "../Settings.h"

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

    this->_PopupModule->hide();
    connect(this->_SettingsButton, &ComputerButton::clicked, this, &MainWindow::settingsButtonClicked);
    connect(this->_AddNewMachineButton, &ComputerButton::clicked, this, &MainWindow::addMachineButtonClicked);
}

void MainWindow::LoadComputers(const QList<Computer*>& list)
{
    for (auto it = list.begin(); it != list.end(); it++)
    {
        ComputerButton *computerButton = new ComputerButton();
        computerButton->SetComputerPointer(*it);
        if ((*it)->IsThisComputer())
        {
            computerButton->SetFocused(true);
            ui->Label_SelectedMachineName->setText((*it)->GetName());
            ui->Label_SelectedMachineIP->setText((*it)->GetIP());
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

    this->_taskButtonsList.clear();

    for (auto it = list.begin(); it != list.end(); it++)
    {
        TaskButton *taskButton = new TaskButton();
        taskButton->SetTaskPointer(*it);
        taskButton->SetText((*it)->GetName());
        this->_taskButtonsList.push_back(taskButton);
        this->ui->Widget_TasksList->layout()->addWidget(taskButton);
    }
}

void MainWindow::machineButtonChangedFocus(ComputerButton *button)
{
    // change computer button focus
    for (auto it = this->_machinesList.begin(); it != this->_machinesList.end(); it++)
    {
        if (*it != button)
        {
            (*it)->SetFocused(false);
        }
    }

    // clean tasks list widget
    for (auto it = this->_taskButtonsList.begin(); it != this->_taskButtonsList.end(); it++)
    {
        this->ui->Widget_TasksList->layout()->removeWidget((*it));
    }
    // load curent tasks
    this->LoadTasks(ComputersManager::Instance().GetTasksByComputer(button->GetComputerPointer()));

    // computer data
    this->ui->Label_SelectedMachineName->setText(button->GetComputerPointer()->GetName());
    this->ui->Label_SelectedMachineIP->setText(button->GetComputerPointer()->GetIP());
}

void MainWindow::settingsButtonClicked()
{
    this->_PopupModule->setGeometry(0, 0, width(), height());
    this->_PopupModule->raise();
    this->_PopupModule->PushPopup(PopupModule::PopupType::SETTINGS);
    this->_PopupModule->show();
    SaveManager::Instance().Save();
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
    Computer *computer = new Computer();
    computer->SetIP(machine_ip);
    computer->SetName(machine_name);
    ComputersManager::Instance().AddComputer(computer);
    but->SetComputerPointer(computer);
}

// add task button
void MainWindow::on_pushButton_2_clicked()
{
    this->_PopupModule->setGeometry(0, 0, width(), height());
    this->_PopupModule->raise();
    this->_PopupModule->PushPopup(PopupModule::PopupType::ADDTASK);
    Popup *popup = this->_PopupModule->TopPopup();
    if (popup != nullptr)
    {
        connect(popup, &AddTaskPopup::addTask, this, &MainWindow::AddTaskTriger);
    }
    this->_PopupModule->show();
}

void MainWindow::AddTaskTriger(QString task_id, QString task_name)
{
    Task *task = new Task();
    task->SetID(task_id);
    task->SetName(task_name);
    for (auto it = this->_machinesList.begin(); it != this->_machinesList.end(); it++)
    {
        if ((*it)->IsFocused())
        {
            (*it)->GetComputerPointer()->AddTask(task);
            this->LoadTasks((*it)->GetComputerPointer()->GetTasks());
            break;
        }
    }
}

