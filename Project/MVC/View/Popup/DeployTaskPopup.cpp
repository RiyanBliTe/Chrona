#include "DeployTaskPopup.h"
#include "../../../Window/ProgramWindow.h"
#include "../../Controller/Manager/StartupManager.h"
#include "../../Controller/TaskController.h"
#include "../../Controller/ComputerController.h"
#include "../../Controller/Manager/SaveManager.h"

#include <QVBoxLayout>
#include <QDebug>

DeployTaskPopup::DeployTaskPopup(QWidget *parent)
    : Popup{parent}
    , _animation(nullptr)
    , _sections(nullptr)
    , _timeEdit(nullptr)
    , _dateEdit(nullptr)
    , _cancelButton(nullptr)
    , _deployButton(nullptr)
    , _dateWidget(nullptr)
    , _timeWidget(nullptr)
    , _group2(nullptr)
    , heightOFFSET(0)
{
    SetMemory();
    SetupModules();
}

DeployTaskPopup::~DeployTaskPopup()
{
    if (this->_animation != nullptr)
        delete this->_animation;
}

void DeployTaskPopup::SetMemory()
{
    if (this->_animation == nullptr)
        this->_animation = new QPropertyAnimation(this);
    if (this->_timeEdit == nullptr)
        this->_timeEdit = new QTimeEdit;
    if (this->_dateEdit == nullptr)
        this->_dateEdit = new QDateEdit;
    if (this->_sections == nullptr)
        this->_sections = new SectionButton;
    if (this->_cancelButton == nullptr)
        this->_cancelButton = new QPushButton;
    if (this->_deployButton == nullptr)
        this->_deployButton = new QPushButton;
    if (this->_dateWidget == nullptr)
        this->_dateWidget = new QWidget;
    if (this->_timeWidget == nullptr)
        this->_timeWidget = new QWidget;
    if (this->_group2 == nullptr)
        this->_group2 = new QWidget;
}

void DeployTaskPopup::SetupModules()
{
    setFixedSize(450, 250);
    SetTitleText("Deploy Task");
    _centerWidget->setLayout(new QVBoxLayout);

    this->_animation->setTargetObject(this);
    this->_animation->setPropertyName("heightOFFSET");

    QLabel *topText = new QLabel("START TIME");
    _centerWidget->layout()->addWidget(topText);
    this->_sections->setFixedHeight(40);
    this->_sections->createSection("Now");
    this->_sections->createSection("Custom");
    this->_sections->setSelected(0);
    _centerWidget->layout()->addWidget(this->_sections);

    this->_dateWidget->setLayout(new QHBoxLayout);
    this->_dateWidget->layout()->setContentsMargins(0, 0, 0, 0);
    QLabel *dateLabel = new QLabel("DATE: ");
    this->_dateEdit->setFixedHeight(40);
    this->_dateWidget->layout()->addWidget(dateLabel);
    this->_dateWidget->layout()->addWidget(this->_dateEdit);
    this->_dateEdit->setDate(QDate::currentDate());
    //this->_dateEdit->setMinimumDate(QDate::currentDate());
    _centerWidget->layout()->addWidget(this->_dateWidget);

    this->_timeWidget->setLayout(new QHBoxLayout);
    this->_timeWidget->layout()->setContentsMargins(0, 0, 0, 0);
    QLabel *timeLabel = new QLabel("TIME: ");
    this->_timeEdit->setFixedHeight(40);
    this->_timeWidget->layout()->addWidget(timeLabel);
    this->_timeWidget->layout()->addWidget(this->_timeEdit);
    this->_timeEdit->setTime(QTime::currentTime());
    this->_timeEdit->setMinimumTime(QTime::currentTime());
    _centerWidget->layout()->addWidget(this->_timeWidget);

    _centerWidget->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    this->_group2->setLayout(new QHBoxLayout);
    this->_group2->layout()->setContentsMargins(0, 0, 0, 0);
    this->_group2->setFixedHeight(40);
    this->_cancelButton->setFixedHeight(40);
    this->_cancelButton->setText("Cancel");
    this->_cancelButton->setObjectName("CancelButton");
    this->_group2->layout()->addWidget(this->_cancelButton);
    this->_deployButton->setFixedHeight(40);
    this->_deployButton->setText("Deploy");
    this->_group2->layout()->addWidget(this->_deployButton);

    _centerWidget->layout()->addWidget(this->_group2);

    connect(this->_cancelButton, &QPushButton::clicked, this, &DeployTaskPopup::CancelClicked);
    connect(this->_deployButton, &QPushButton::clicked, this, &DeployTaskPopup::DeployClicked);
    connect(this->_sections, &SectionButton::selectionChanged, this, &DeployTaskPopup::ChangedSelection);
    connect(this->_animation, &QPropertyAnimation::finished, this, &DeployTaskPopup::AnimationFinished);

    this->_dateWidget->hide();
    this->_timeWidget->hide();

    _centerWidget->setStyleSheet("    QPushButton\
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
                                 #CancelButton \
                                 {\
                                     border-radius: 4px;\
                                     background-color: rgb(227, 229, 232);\
                                     color: rgb(17, 17, 17);\
                                 }\
                                 #CancelButton:hover \
                                 {\
                                     background-color: rgb(221, 223, 226);\
                                 }\
                                 #CancelButton:pressed \
                                 {\
                                     background-color: rgb(215, 220, 226);\
                                 }\
                                 QDateEdit, QTimeEdit\
                                  {\
                                     border-radius: 4px;\
                                     background-color: rgb(227, 229, 232);\
                                     color: rgb(46, 51, 56);\
                                     padding-left: 10px;\
                                     padding-right: 15px;\
                                 }\
                                 \
                                 QDateEdit:hover, QTimeEdit:hover \
                                 {\
                                     background-color: rgb(221, 223, 226);\
                                 }\
                                 QDateEdit:focus, QTimeEdit:focus \
                                 {\
                                     background-color: rgb(215, 220, 226);\
                                 }\
                                 \
                                 QDateEdit::up-button, QTimeEdit::up-button {\
                                     subcontrol-origin: border;\
                                     subcontrol-position: top right;\
                                     width: 20px;\
                                     background-color: transparent;\
                                     border-top-right-radius: 4px;\
                                 }\
                                 \
                                 QDateEdit::down-button, QTimeEdit::down-button {\
                                     subcontrol-origin: border;\
                                     subcontrol-position: bottom right;\
                                     width: 20px;\
                                     background-color: transparent;\
                                     border-bottom-right-radius: 4px;\
                                 }\
                                 \
                                 QDateEdit::up-button:hover, QDateEdit::down-button:hover, QTimeEdit::up-button:hover, QTimeEdit::down-button:hover{\
                                     background-color: #D6D6D6;\
                                 }\
                                 \
                                 QDateEdit::up-button:pressed, QDateEdit::down-button:pressed, QTimeEdit::up-button:pressed, QTimeEdit::down-button:pressed {\
                                     background-color: #76B39D;\
                                 }\
                                 \
                                 QDateEdit::up-arrow, QTimeEdit::up-arrow {\
                                     image: url(C:/Users/march/Downloads/Vector 39.png);\
                                 }\
                                 \
                                 QDateEdit::down-arrow, QTimeEdit::down-arrow {\
                                     image: url(C:/Users/march/Downloads/Vector 14.png);\
                                 }");
}

void DeployTaskPopup::CancelClicked()
{
    emit closeButtonPressed();
}

void DeployTaskPopup::DeployClicked()
{
    if (this->_sections->GetActiveSection() == 1)
    {
        TaskController::Instance().GetActiveTaskButton()->GetTask()->SetStartDateTime(QDateTime(this->_dateEdit->date(), this->_timeEdit->time()));
    }
    else
    {
        TaskController::Instance().GetActiveTaskButton()->GetTask()->SetStartDateTime(QDateTime(QDateTime::currentDateTime().date(), QDateTime::currentDateTime().time().addSecs(23)));
    }
    TaskController::Instance().GetActiveTaskButton()->GetTask()->Reset();
    for (auto it = TaskController::Instance().GetActiveTaskButton()->GetTask()->GetPipelines().begin();
         it != TaskController::Instance().GetActiveTaskButton()->GetTask()->GetPipelines().end();
         it++)
    {
        (*it)->Reset();
        for (auto it2 = (*it)->GetFiles().begin(); it2 != (*it)->GetFiles().end(); it2++)
        {
            (*it2)->Reset();
        }
    }
    TaskController::Instance().GetActiveTaskButton()->GetTask()->AddHistoryLine(new Task::StatisticLineData{
                                         ComputerController::Instance().GetActiveComputerButton()->GetComputer()->GetName(),
                                         "Wait",
                                         ComputerController::Instance().GetActiveComputerButton()->GetComputer()->GetName(),
                                         QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"),
                                         this->_sections->GetActiveSection() == 0 ? QDateTime(this->_dateEdit->date(), this->_timeEdit->time().addSecs(5)).toString("dd.MM.yyyy hh:mm:ss")
                                         : QDateTime(this->_dateEdit->date(), this->_timeEdit->time()).toString("dd.MM.yyyy hh:mm:ss"),
                                     }, true);
    Task::StatisticLineData *data = TaskController::Instance().GetActiveTaskButton()->GetTask()->GetTopHistory();
    if (data != nullptr)
        ProgramWindow::Instance().AddHistoryToTaskButton(TaskController::Instance().GetActiveTaskButton(), data);
    SaveManager::Instance().Save();
    StartupManager::Instance().Deploy(TaskController::Instance().GetActiveTaskButton()->GetTask());
    emit closeButtonPressed();
}

void DeployTaskPopup::ChangedSelection(int id)
{
    if (!id)
    {
        if (!this->_sections->GetActiveSection())
        {
            this->_dateWidget->hide();
            this->_timeWidget->hide();

            if (this->_animation->state() == QPropertyAnimation::Running)
                this->_animation->stop();
            this->_animation->setDuration(100);
            this->_animation->setStartValue(350);
            this->_animation->setEndValue(250);
            this->_animation->start();
        }
    }
    else
    {
        if (this->_sections->GetActiveSection())
        {
            if (this->_animation->state() == QPropertyAnimation::Running)
                this->_animation->stop();
            this->_animation->setDuration(100);
            this->_animation->setStartValue(250);
            this->_animation->setEndValue(350);
            this->_animation->start();
        }
    }
}

void DeployTaskPopup::AnimationFinished()
{
    if (this->_sections->GetActiveSection())
    {
        this->_dateWidget->show();
        this->_timeWidget->show();
    }
}

void DeployTaskPopup::SetHeightOFFSET(int value)
{
    this->heightOFFSET = value;
    setFixedSize(450, value);
    Popup::SetHeightOFFSET(value);
    ProgramWindow::Instance().GetPopupManager()->Update();
    update();
}

int DeployTaskPopup::GetHeightOFFSET()
{
    return this->heightOFFSET;
}
