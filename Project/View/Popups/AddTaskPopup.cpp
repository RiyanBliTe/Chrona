#include "AddTaskPopup.h"
#include <time.h>>

AddTaskPopup::AddTaskPopup(QWidget *parent)
    : Popup{parent}
    , _taskName(nullptr)
    , _addButton(nullptr)
{
    this->SetMemory();
    this->SetupModules();
}

AddTaskPopup::~AddTaskPopup()
{

}

void AddTaskPopup::SetMemory()
{
    if (this->_taskName == nullptr)
        this->_taskName = new QLineEdit();
    if (this->_addButton == nullptr)
        this->_addButton = new QPushButton();
}

void AddTaskPopup::SetupModules()
{
    setFixedSize(350, 250);
    SetTitleText("Add Task");

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

    this->_taskName->setFixedHeight(40);
    this->_addButton->setFixedHeight(40);
    this->_addButton->setText("Add Task");
    connect(this->_addButton, &QPushButton::clicked, this, &AddTaskPopup::addButtonPressed);

    QLabel *taskNameLabel = new QLabel();
    taskNameLabel->setText("TASK NAME");
    QFont font = QFont(Settings::GetInstance().GetApplicationFont(Settings::Fonts::SEN_REGULAR), 10);
    taskNameLabel->setFont(font);
    _centerWidget->layout()->addWidget(taskNameLabel);
    _centerWidget->layout()->addWidget(this->_taskName);
    QFont buttonFont = QFont(font);
    buttonFont.setWeight(QFont::Bold);
    this->_addButton->setFont(buttonFont);
    _centerWidget->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    _centerWidget->layout()->addWidget(this->_addButton);

    this->_addButton->setEnabled(false);
    connect(this->_taskName, &QLineEdit::textChanged, this, &AddTaskPopup::taskTextChanged);
}

void AddTaskPopup::addButtonPressed()
{
    emit addTask(std::to_string(time(NULL)).c_str(), this->_taskName->text());
    emit closeButtonPressed();
}

void AddTaskPopup::taskTextChanged()
{
    if (this->_taskName->text() == "" || this->_taskName->text().isEmpty())
    {
        this->_addButton->setEnabled(false);
    }
    else
    {
        this->_addButton->setEnabled(true);
    }
}
