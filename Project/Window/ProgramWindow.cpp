#include "ProgramWindow.h"
#include "ui_ProgramWindow.h"
#include "../MVC/Controller/Manager/SaveManager.h"
#include "../MVC/Controller/Manager/PopupManager.h"
#include "../MVC/Controller/ComputerController.h"
#include "../MVC/Controller/TaskController.h"
#include "../MVC/Controller/FileController.h"
#include <QMenu>

ProgramWindow::ProgramWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgramWindow),
    _needToClose(false)
{
    ui->setupUi(this);
    SetupView();
}

ProgramWindow::~ProgramWindow()
{
    delete ui;
}

ProgramWindow& ProgramWindow::Instance()
{
    static ProgramWindow instance;
    return instance;
}

void ProgramWindow::SetupView()
{
    this->_trayMenu = new QMenu();
    this->_trayMenu->setStyleSheet("QMenu\
                                   {\
                                       background-color: rgb(40, 40, 40);\
                                       border-radius: 4px;\
                                       padding: 5px 1px;\
                                   }\
                                   QMenu::item \
                                   {\
                                       background-color: transparent;\
                                       padding: 5px 10px;\
                                       margin: 2px 0px;\
                                       color: white;\
                                   }\
                                   QMenu::item:selected \
                                   {\
                                       background-color: #76B39D;\
                                   }");
    this->_trayMenu->addAction("Exit", this, &ProgramWindow::TrayMenuClose);
    this->_systemTrayIcon = new QSystemTrayIcon(this);
    this->_systemTrayIcon->setIcon(QIcon(":/Image/icon_logo.svg"));
    this->_systemTrayIcon->setVisible(true);
    this->_systemTrayIcon->setToolTip("Chrona");
    this->_systemTrayIcon->setContextMenu(this->_trayMenu);
    connect(this->_systemTrayIcon, &QSystemTrayIcon::activated, [this](QSystemTrayIcon::ActivationReason reason)
    {
        if (reason == QSystemTrayIcon::DoubleClick)
        {
            if (!this->isVisible())
            {
                this->show();
            }
            else
            {
                this->showMaximized();
            }
        }

    });

    this->_taskStackedWidget = new QStackedWidget;
    ui->TasksWidget->layout()->addWidget(this->_taskStackedWidget);

    this->_taskViewStackedWidget = new QStackedWidget;
    ui->TaskViewWidget->layout()->addWidget(this->_taskViewStackedWidget);
    ui->TopNotificationButton->hide();

    ui->TopBackButton->hide();
    connect(ui->TopBackButton, &QPushButton::clicked, this, &ProgramWindow::BackButtonClicked);
    ui->DeployButton->hide();
    connect(ui->DeployButton, &QPushButton::clicked, this, &ProgramWindow::DeployButtonClicked);

    this->_settingsButton = new ComputerButton;
    this->_settingsButton->SetLeftPanelEnabled(false);
    this->_settingsButton->SetImage(":/Image/icon_settings.svg");
    ui->SettingsWidget->layout()->addWidget(this->_settingsButton);
    this->_addComputerButton = new ComputerButton;
    this->_addComputerButton->SetLeftPanelEnabled(false);
    this->_addComputerButton->SetImage(":/Image/icon_add_machine.svg");
    ui->AddComputerWidget->layout()->addWidget(this->_addComputerButton);

    connect(ui->AddTaskButton, &QPushButton::clicked, this, &ProgramWindow::AddTaskButtonClicked);
    connect(this->_settingsButton, &ComputerButton::clicked, this, &ProgramWindow::SettingsButtonClicked);
    connect(this->_addComputerButton, &ComputerButton::clicked, this, &ProgramWindow::AddComputerClicked);
    connect(ui->TopSaveButton, &QPushButton::clicked, this, &ProgramWindow::SaveButtonClicked);

    this->_popupManager = new PopupManager(this);
    _popupManager->hide();
    showMaximized();
}

int ProgramWindow::GenerateTaskWidget()
{
    static int index = 0;

    QWidget *backWidget = new QWidget;
    backWidget->setLayout(new QVBoxLayout);
    backWidget->layout()->setContentsMargins(0, 0, 0, 0);
    QWidget *listWidget = new QWidget;
    listWidget->setLayout(new QVBoxLayout);
    listWidget->layout()->setContentsMargins(0, 0, 0, 0);
    QWidget *spacerWidget = new QWidget;
    spacerWidget->setLayout(new QVBoxLayout);
    spacerWidget->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    backWidget->layout()->addWidget(listWidget);
    backWidget->layout()->addWidget(spacerWidget);

    this->_taskStackedWidget->addWidget(backWidget);
    this->_tasksWidgetList.append(std::make_pair(listWidget, index));
    return index++;
}

void ProgramWindow::AddComputerButton(ComputerButton *button)
{
    button->SetStackedIndex(GenerateTaskWidget());
    ui->ComputersWidget->layout()->addWidget(button);
}

int ProgramWindow::GenerateTaskViewWidget()
{
    static int indexView = 0;

    TaskView *taskView = new TaskView;
    this->_taskViewStackedWidget->addWidget(taskView);

    _tasksViewList.append(std::make_pair(taskView, indexView));
    return indexView++;
}

void ProgramWindow::AddTaskByIndex(int index, TaskButton *button)
{
    if (button != nullptr)
    {
        for (auto it = this->_tasksWidgetList.begin(); it != this->_tasksWidgetList.end(); it++)
        {
            if (index == it->second)
            {
                if (button->GetStackedIndex() == -1)
                    button->SetStackedIndex(GenerateTaskViewWidget());
                it->first->layout()->addWidget(button);
                break;
            }
        }
    }
}

void ProgramWindow::SetActiveTaskWidget(int index)
{
    this->_taskStackedWidget->setCurrentIndex(index);
}

void ProgramWindow::SetActiveTaskViewWidget(int index)
{
    this->_taskViewStackedWidget->setCurrentIndex(index);
    for (auto it = this->_tasksViewList.begin(); it != this->_tasksViewList.end(); it++)
    {
        if (it->second == index)
        {
            it->first->CheckButtonState();
        }
    }
}

void ProgramWindow::AddHistoryToTaskButton(TaskButton* taskButton, Task::StatisticLineData *data)
{
    for (auto it = this->_tasksViewList.begin(); it != this->_tasksViewList.end(); it++)
    {
        if (it->second == taskButton->GetStackedIndex())
        {
            it->first->AddHistory(data);
        }
    }
}

void ProgramWindow::ChangeStatus(TaskButton* taskButton)
{
    for (auto it = this->_tasksViewList.begin(); it != this->_tasksViewList.end(); it++)
    {
        if (it->second == taskButton->GetStackedIndex())
        {
            QString status = "Idle";
            if (taskButton->GetTask()->GetStatus() == Task::TaskStatus::IDLE)
            {
                status = "Idle";
            }
            else if (taskButton->GetTask()->GetStatus() == Task::TaskStatus::STARTWAIT)
            {
                status = "Wait";
            }
            else if (taskButton->GetTask()->GetStatus() == Task::TaskStatus::RUNNING)
            {
                status = "Working";
            }
            else if (taskButton->GetTask()->GetStatus() == Task::TaskStatus::SUCCESS)
            {
                status = "Success";
            }
            else if (taskButton->GetTask()->GetStatus() == Task::TaskStatus::FAILED)
            {
                status = "Failed";
            }
            it->first->ChangeStatus(status);
        }
    }
}

void ProgramWindow::GenerateTaskConstructor(TaskButton *button)
{
    button->SetStackedIndex(GenerateTaskViewWidget());
}

void ProgramWindow::AddPipelineByIndex(PipelineContainer* container, int index)
{
    if (container != nullptr)
    {
        for (auto it = this->_tasksViewList.begin(); it != this->_tasksViewList.end(); it++)
        {
            if (index == it->second)
            {
                it->first->AddPpipeline(container);
                break;
            }
        }
    }
}

void ProgramWindow::SetComputerInfo(QString name, QString ip)
{
    ui->ComputerName->setText(name);
    ui->ComputerIP->setText(ip);
}

void ProgramWindow::ShowBackButton()
{
    ui->TopBackButton->show();
    ui->DeployButton->show();
    ui->TopTitle->setText("Edit Task");
}

void ProgramWindow::HideBackButton()
{
    ui->TopBackButton->hide();
    ui->DeployButton->hide();
    ui->TopTitle->setText("Manage Task");
}

void ProgramWindow::ShowFilePopup(FileContainer *container)
{
    CustomFile *file = FileController::Instance().GetFileByView(container);
    if (file != nullptr)
    {
        this->_popupManager->setGeometry(0, 0, width(), height());
        this->_popupManager->raise();
        this->_popupManager->UsedFile(file);
        this->_popupManager->PushPopup(PopupManager::PopupType::FILEINFO);
        this->_popupManager->show();
    }
}

PopupManager* ProgramWindow::GetPopupManager()
{
    return this->_popupManager;
}

void ProgramWindow::ShowSystemTrayMessage(QString title, QString message, bool style)
{
    this->_systemTrayIcon->showMessage("Chrona", title + "\n" + message, style ? QSystemTrayIcon::Information : QSystemTrayIcon::Warning, 2000);
}

void ProgramWindow::AddTaskButtonClicked()
{
    this->_popupManager->setGeometry(0, 0, width(), height());
    this->_popupManager->raise();
    this->_popupManager->PushPopup(PopupManager::PopupType::ADDTASK);
    Popup *popup = this->_popupManager->TopPopup();
    if (popup != nullptr)
    {
        connect(popup, &Popup::addTask, this, &ProgramWindow::AddTaskTriger);
    }
    this->_popupManager->show();
}

void ProgramWindow::SettingsButtonClicked(ComputerButton *button)
{
    (void)button;
    this->_popupManager->setGeometry(0, 0, width(), height());
    this->_popupManager->raise();
    this->_popupManager->PushPopup(PopupManager::PopupType::SETTINGS);
    this->_popupManager->show();
}

void ProgramWindow::AddComputerClicked(ComputerButton *button)
{
    (void)button;
    this->_popupManager->setGeometry(0, 0, width(), height());
    this->_popupManager->raise();
    this->_popupManager->PushPopup(PopupManager::PopupType::ADDMACHINE);
    Popup *popup = this->_popupManager->TopPopup();
    if (popup != nullptr)
    {
        connect(popup, &Popup::connectedSucces, this, &ProgramWindow::AddComputerTriger);
    }
    this->_popupManager->show();
}

void ProgramWindow::SaveButtonClicked()
{
    SaveManager::Instance().Save();
}

void ProgramWindow::BackButtonClicked()
{
    ui->TopBackButton->hide();
    ui->DeployButton->hide();
    int index = TaskController::Instance().GetActiveTaskButton()->GetStackedIndex();
    for (auto it = this->_tasksViewList.begin(); it != this->_tasksViewList.end(); it++)
    {
        if (it->second == index)
        {
            it->first->GoToManage();
            break;
        }
    }
}

void ProgramWindow::DeployButtonClicked()
{
    this->_popupManager->setGeometry(0, 0, width(), height());
    this->_popupManager->raise();
    this->_popupManager->PushPopup(PopupManager::PopupType::DEPLOY);
    this->_popupManager->show();
}

void ProgramWindow::TrayMenuClose()
{
    this->_needToClose = true;
    close();
}

void ProgramWindow::AddTaskTriger(QString id, QString name)
{
    ComputerController::Instance().AddTaskToActiveComputer(name, id);
}

void ProgramWindow::AddComputerTriger(QString name, QString ip)
{
    ComputerController::Instance().AddComputer(name, ip);
}

void ProgramWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    this->_popupManager->setGeometry(0, 0, width(), height());
    this->_popupManager->Update();
}

void ProgramWindow::closeEvent(QCloseEvent *event)
{
    if(this->isVisible() && !this->_needToClose)
    {
        event->ignore();
        this->hide();

        this->_systemTrayIcon->showMessage("Chrona", "Application minimized to system tray", QSystemTrayIcon::Information, 2000);
     }
}
