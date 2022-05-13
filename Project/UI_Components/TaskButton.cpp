#include "TaskButton.h"

TaskButton::TaskButton(QWidget *parent)
    : QWidget{parent}
    , _mainBackgroundColor(Settings::GetInstance()._on_center_panel_task_button_idle_color)
    , _mainButtonColor(Settings::GetInstance()._on_center_panel_task_button_close_button_idle_color)
    , _textColor(Settings::GetInstance()._on_center_panel_task_button_text_color)
    , _buttonText("Button")
    , _buttonStatus(TaskStatus::IDLE)
{
    setFixedHeight(40);
}

void TaskButton::SetStatus(TaskStatus value)
{
    this->_buttonStatus = value;
}

TaskButton::TaskStatus TaskButton::GetStatus()
{
    return this->_buttonStatus;
}

void TaskButton::SetText(QString &value)
{
    this->_buttonText = value;
}

QString& TaskButton::GetText()
{
    return this->_buttonText;
}

void TaskButton::enterEvent(QEnterEvent* event)
{
    (void)event;

    this->_mainBackgroundColor = Settings::GetInstance()._on_center_panel_task_button_enter_color;
    update();
}

void TaskButton::leaveEvent(QEvent* event)
{
    (void)event;

    this->_mainBackgroundColor = Settings::GetInstance()._on_center_panel_task_button_idle_color;
    update();
}

void TaskButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->_mainBackgroundColor = Settings::GetInstance()._on_center_panel_task_button_press_color;
        update();
    }
}

void TaskButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->_mainBackgroundColor = Settings::GetInstance()._on_center_panel_task_button_enter_color;
        update();
    }
}

void TaskButton::paintEvent(QPaintEvent* event)
{
    (void)event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // draw background
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(this->_mainBackgroundColor));
    painter.drawRoundedRect(QRectF(0,
                                   0,
                                   width(),
                                   height()),
                            4, 4);

    // draw status idicator
    switch (this->GetStatus())
    {
    case TaskButton::TaskStatus::IDLE:
        painter.setBrush(QColor("#7C7C7C"));
        break;
    case TaskButton::TaskStatus::RUNNING:
        painter.setBrush(QColor("#FBBE20"));
        break;
    case TaskButton::TaskStatus::SUCCESS:
        painter.setBrush(QColor("#189C3D"));
        break;
    case TaskButton::TaskStatus::FAILED:
        painter.setBrush(QColor("#E11E1E"));
        break;
    }
    painter.drawEllipse(QRect(10, 16, 8, 8));

    // draw text
    painter.setPen(QPen(QColor(this->_textColor), 1));
    painter.drawText(QPoint(32, height() / 2 + 6), this->GetText());

    // draw close button
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(this->_mainButtonColor));
    painter.drawRoundedRect(QRectF(width() - 24,
                                  height() - 27,
                                  14,
                                  14),
                            4, 4);

    // draw close button image
    QImage image(":/icons_svg/Images/icons_svg/icon_task_close.svg");
    painter.drawImage(QRectF(width() - 17 - image.width() / 2,
                             height() - 20 - image.height() / 2,
                             image.width(),
                             image.height()),
                       image);
}
