#include "ProgramWindow.h"
#include "ui_ProgramWindow.h"
#include "../Controller/SaveController.h"
#include "../Controller/ComputersController.h"
#include "../Controller/ColorController.h"
#include <QDebug>
#include <QProcess>

ProgramWindow::ProgramWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgramWindow)
{
    ui->setupUi(this);
    SaveController::Instance().LoadProgramData();

    LoadComputersListToForm(ComputersController::Instance().GetComputerButtons());
    auto* butList = ComputersController::Instance().GetComputerButtons();
    for (auto it = butList->begin(); it != butList->end(); it++)
    {
        if (it->second->IsFocused())
        {
            ui->CenterPanelComputerName->setText(it->first->GetName());
            ui->CenterPanelComputerIP->setText(it->first->GetIP());
        }
    }

    if (ComputersController::Instance().GetActiveComputerTaskButtons() != nullptr)
        LoadTasksListToForm(ComputersController::Instance().GetActiveComputerTaskButtons());


    this->_SettingsButton = new ComputerButton();
    this->_AddNewMachineButton = new ComputerButton();
    this->_AddNewMachineButton->SetLeftPanelEnabled(false);
    this->_AddNewMachineButton->SetImage(":/images/Images/icon_add_machine.svg");

    this->_SettingsButton->SetLeftPanelEnabled(false);
    this->_SettingsButton->SetImage(":/images/Images/icon_settings.svg");
    this->ui->LeftPanelSettingsPanel->layout()->addWidget(this->_SettingsButton);

    this->ui->LeftPanelAddComputerPanel->layout()->addWidget(this->_AddNewMachineButton);
    connect(this->_SettingsButton, &ComputerButton::clicked, this, &ProgramWindow::SettingsButtonClicked);
    connect(this->_AddNewMachineButton, &ComputerButton::clicked, this, &ProgramWindow::AddMachineButtonClicked);

    connect(ui->AddTaskButton, &QPushButton::clicked, this, &ProgramWindow::AddTaskButtonClicked);
    this->_PopupModule = new PopupController(this);
    this->_PopupModule->hide();

    ui->BackPushButton->setVisible(false);

    this->_CustomConstructor = new CustomConstructor;
    ui->scrollAreaWidgetContents->layout()->addWidget(this->_CustomConstructor);

    connect(ui->EditModeButton, &QPushButton::clicked, this, &ProgramWindow::GoToTheEditMode);
    connect(ui->BackPushButton, &QPushButton::clicked, this, &ProgramWindow::FromEditModeToInfo);

    // ui
    ui->LeftPanel->setStyleSheet("#LeftPanel { background-color: " + ColorController::Instance().GetLeftPanelColor() + "; }");
    ui->LeftScrollAreaPanel->setStyleSheet("#LeftScrollAreaPanel { background-color: " + ColorController::Instance().GetLeftPanelColor() + "; }");
    ui->CenterPanel->setStyleSheet("#CenterPanel { background-color:" + ColorController::Instance().GetCenterPanelColor() + "; }");
    ui->CenterScrollAreaPanel->setStyleSheet("#CenterScrollAreaPanel { background-color:" + ColorController::Instance().GetCenterPanelColor() + "; }");
    ui->RightPanel->setStyleSheet("#RightPanel { background-color:" + ColorController::Instance().GetRightPanelColor() + "; }");
    ui->CenterBottomPanel->setStyleSheet("#CenterBottomPanel { background-color:" + ColorController::Instance().GetCenterPanelBottomColor() + "; }");
    ui->scrollAreaWidgetContents->setStyleSheet("#scrollAreaWidgetContents { background-color:" + ColorController::Instance().GetRightPanelColor() + "; }");
    showMaximized();
}

ProgramWindow::~ProgramWindow()
{
    delete ui;
}


ProgramWindow &ProgramWindow::Instance()
{
    static ProgramWindow instance;
    return instance;
}

void ProgramWindow::SettingsButtonClicked(ComputerButton *button)
{
    (void)button;
    this->_PopupModule->setGeometry(0, 0, width(), height());
    this->_PopupModule->raise();
    this->_PopupModule->PushPopup(PopupController::PopupType::SETTINGS);
    this->_PopupModule->show();
}

void ProgramWindow::AddMachineButtonClicked(ComputerButton *button)
{
    (void)button;
    this->_PopupModule->setGeometry(0, 0, width(), height());
    this->_PopupModule->raise();
    this->_PopupModule->PushPopup(PopupController::PopupType::ADDMACHINE);
    Popup *popup = this->_PopupModule->TopPopup();
    if (popup != nullptr)
    {
        connect(popup, &AddMachinePopup::connectedSucces, this, &ProgramWindow::AddMachineTriger);
    }
    this->_PopupModule->show();
}


void ProgramWindow::AddTaskButtonClicked()
{
    this->_PopupModule->setGeometry(0, 0, width(), height());
    this->_PopupModule->raise();
    this->_PopupModule->PushPopup(PopupController::PopupType::ADDTASK);
    Popup *popup = this->_PopupModule->TopPopup();
    if (popup != nullptr)
    {
        connect(popup, &AddTaskPopup::addTask, this, &ProgramWindow::AddTaskTriger);
    }
    this->_PopupModule->show();
}

void ProgramWindow::AddTaskTriger(QString id, QString name)
{
    ComputersController::Instance().AddTaskToActiveComputer(name, id);
}

void ProgramWindow::AddMachineTriger(QString name, QString ip)
{
    ComputersController::Instance().AddComputer(name, ip);
}

void ProgramWindow::GoToTheEditMode()
{
    ui->RightStackedWidget->setCurrentIndex(1);
    ui->TaskEditStackedWidget->setCurrentIndex(0);
    ui->BackPushButton->setVisible(true);
}

void ProgramWindow::FromEditModeToInfo()
{
    ui->RightStackedWidget->setCurrentIndex(0);
    ui->BackPushButton->setVisible(false);
}

void ProgramWindow::LoadComputersListToForm(const QList<std::pair<Computer*, ComputerButton*>> *list)
{
    ClearLayout(ui->LeftPanelComputerList->layout());
    for (auto it = list->begin(); it != list->end(); it++)
    {
        ui->LeftPanelComputerList->layout()->addWidget(it->second);
    }
}

void ProgramWindow::LoadTasksListToForm(const QList<std::pair<Task*, TaskButton*>> *list)
{
    ClearLayout(ui->CenterTaskListPanel->layout());
    for (auto it = list->begin(); it != list->end(); it++)
    {
        ui->CenterTaskListPanel->layout()->addWidget(it->second);
    }
}

void ProgramWindow::AddCompterToTorm(ComputerButton *button)
{
    ui->LeftPanelComputerList->layout()->addWidget(button);
}

void ProgramWindow::ChangeComputerData(QString name, QString ip)
{
    ui->CenterPanelComputerName->setText(name);
    ui->CenterPanelComputerIP->setText(ip);
}

PopupController* ProgramWindow::GetPopupController()
{
    return this->_PopupModule;
}

void ProgramWindow::ClearLayout(QLayout* layout)
{
    if (!layout->isEmpty())
    {
        QLayoutItem *layoutItem = nullptr;
        while ((layoutItem = layout->takeAt(0)) != nullptr)
        {
            layout->removeWidget(layoutItem->widget());
        }
    }
}

void ProgramWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    this->_PopupModule->setGeometry(0, 0, width(), height());
    this->_PopupModule->Update();
}

void ProgramWindow::closeEvent(QCloseEvent *event)
{
    SaveController::Instance().Save();
}

void ProgramWindow::on_SaveButton_clicked()
{
    SaveController::Instance().Save();
}

