#include "ProgramWindow.h"
#include "ui_ProgramWindow.h"
#include <QDebug>
#include "../MVC/Controller/Manager/SaveManager.h"
#include "../MVC/Controller/Manager/PopupManager.h"
#include "../MVC/Controller/ComputerController.h"
#include "../MVC/Controller/TaskController.h"
#include "../MVC/Controller/FileController.h"

ProgramWindow::ProgramWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgramWindow)
{
    qDebug() << "[CREATED]" << this;
    ui->setupUi(this);
    SetupView();
}

ProgramWindow::~ProgramWindow()
{
    qDebug() << "[DELETED]" << this;
    delete ui;
}

ProgramWindow& ProgramWindow::Instance()
{
    static ProgramWindow instance;
    return instance;
}

void ProgramWindow::SetupView()
{
    this->_taskStackedWidget = new QStackedWidget;
    ui->TasksWidget->layout()->addWidget(this->_taskStackedWidget);

    this->_taskViewStackedWidget = new QStackedWidget;
    ui->TaskViewWidget->layout()->addWidget(this->_taskViewStackedWidget);

    ui->TopBackButton->hide();
    connect(ui->TopBackButton, &QPushButton::clicked, this, &ProgramWindow::BackButtonClicked);

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
}

void ProgramWindow::HideBackButton()
{
    ui->TopBackButton->hide();
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
