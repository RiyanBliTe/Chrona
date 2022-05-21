#include "TaskInfoPanel.h"

TaskInfoPanel::TaskInfoPanel(QWidget *parent)
    : QWidget{parent}
    , _headerWidget(nullptr)
    , _contentWidget(nullptr)
    , _taskName(nullptr)
    , _goToEditMode(nullptr)
{
    SetMemory();
    SetupModules();
}

TaskInfoPanel::~TaskInfoPanel()
{
    if (this->_headerWidget != nullptr)
        delete this->_headerWidget;
    if (this->_contentWidget != nullptr)
        delete this->_contentWidget;
}

void TaskInfoPanel::SetMemory()
{
    if (this->_headerWidget == nullptr)
        this->_headerWidget = new QWidget();
    if (this->_contentWidget == nullptr)
        this->_contentWidget = new QWidget();
    if (this->_taskName == nullptr)
        this->_taskName = new QLabel();
    if (this->_goToEditMode == nullptr)
        this->_goToEditMode = new QPushButton();
}

void TaskInfoPanel::SetupModules()
{
    this->setLayout(new QVBoxLayout());
    this->layout()->setContentsMargins(0, 0, 0, 0);

    // header
    this->layout()->addWidget(this->_headerWidget);
    this->_headerWidget->setFixedHeight(40);
    this->_headerWidget->setLayout(new QHBoxLayout());
    this->_headerWidget->layout()->setContentsMargins(20, 0, 10, 0);
    this->_headerWidget->layout()->addWidget(this->_taskName);
    this->_headerWidget->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    this->_headerWidget->layout()->addWidget(this->_goToEditMode);
    this->_headerWidget->setStyleSheet("QPushButton\
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

    // content
    this->layout()->addWidget(this->_contentWidget);


    // header content
    this->_taskName->setText("Task");
    this->_taskName->setStyleSheet("color: rgb(255, 255, 255);");
    QFont taskFont;
    taskFont.setPointSize(14);
    taskFont.setBold(true);
    this->_taskName->setFont(taskFont);

    this->_goToEditMode->setText("Edit Mode");
    this->_goToEditMode->setFixedSize(150, 40);
}
