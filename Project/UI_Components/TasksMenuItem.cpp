#include "TasksMenuItem.h"
#include "ui_TasksMenuItem.h"

TasksMenuItem::TasksMenuItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TasksMenuItem)
    , _isFocused(false)
    , _buttonState(MenuItemState::IDLE)
{
    ui->setupUi(this);
    SetupModules();
    LeaveUI();
}

TasksMenuItem::~TasksMenuItem()
{
    delete ui;
}

void TasksMenuItem::SetupModules()
{
    this->_enteredStyle = QString("#frame \
                                  { \
                                      background-color: rgb(30, 32, 33); \
                                      border-radius: 10px; \
                                  }");
    this->_leavedStyle = QString("#frame \
                                 { \
                                     background-color: transparent; \
                                     border-radius: 10px; \
                                 }");
    this->_pressedStyle = QString("#frame \
                                  { \
                                      background-color: rgb(48, 52, 53); \
                                      border-radius: 10px; \
                                  }");
}

void TasksMenuItem::SetFocused(bool value)
{
    this->_isFocused = value;
    if (value)
    {
        EnterUI();
    }
    else
    {
        LeaveUI();
    }
}

void TasksMenuItem::SetText(QString value)
{
    this->ui->label->setText(value);
}

void TasksMenuItem::SetState(MenuItemState value)
{
    this->_buttonState = value;

    QString styleString = "";
    switch (this->_buttonState) {
    case IDLE:
        styleString.append("background-image: url(:/icons_svg/Images/icons_svg/icon_task_idle.svg);");
        break;
    case RUNNING:
        styleString.append("background-image: url(:/icons_svg/Images/icons_svg/icon_task_running.svg);");
        break;
    case FINISHED:
        styleString.append("background-image: url(:/icons_svg/Images/icons_svg/icon_task_finished.svg);");
        break;
    case FAILED:
        styleString.append("background-image: url(:/icons_svg/Images/icons_svg/icon_task_error.svg);");
        break;
    default:
        styleString.append("background-image: url(:/icons_svg/Images/icons_svg/icon_task_idle.svg);");
        break;
    }
    styleString.append(" background-repeat: no-repeat; background-position: center;");

    this->ui->Frame_Status->setStyleSheet(styleString);
}

void TasksMenuItem::EnterUI()
{
    this->ui->widget->setStyleSheet(this->_enteredStyle);
    this->ui->pushButton->show();
}

void TasksMenuItem::LeaveUI()
{
    this->ui->widget->setStyleSheet(this->_leavedStyle);
    this->ui->pushButton->hide();
}

void TasksMenuItem::enterEvent(QEnterEvent *event)
{
    (void)event;

    if (!this->_isFocused)
        this->EnterUI();
}

void TasksMenuItem::leaveEvent(QEvent *event)
{
    (void)event;

    if (!this->_isFocused)
        this->LeaveUI();
}

void TasksMenuItem::mousePressEvent(QMouseEvent *event)
{
    (void)event;

    this->ui->widget->setStyleSheet(this->_pressedStyle);
    this->ui->pushButton->show();
}

void TasksMenuItem::mouseReleaseEvent(QMouseEvent *event)
{
    (void)event;

    EnterUI();
    emit focusChanged(this);
    this->SetFocused(true);
}
