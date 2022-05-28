#include "TaskButton.h"

TaskButton::TaskButton(QWidget *parent)
    : QWidget{parent}
    , _mainBackgroundColor(ColorController::Instance().GetTaskButtonColors().idle)
    , _mainButtonColor(ColorController::Instance().GetTaskButtonCloseButtonColors().idle)
    , _textColor(ColorController::Instance().GetTaskButtonColors().color)
    , _buttonText("Button")
    , _buttonStatus(TaskStatus::IDLE)
    , _isPress(false)
    , _isMouseInCloseButton(false)
    , _isFocused(false)
{
    setFixedHeight(40);
    setMouseTracking(true);
}

TaskButton::~TaskButton()
{
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
    if (value.length() >= 24)
    {
        QString text = value.mid(0, 23);
        text.append("...");
        this->_buttonText = text;
    }
    else
        this->_buttonText = value;
}

QString& TaskButton::GetText()
{
    return this->_buttonText;
}

void TaskButton::SetFocused(bool value)
{
    this->_isFocused = value;
    if (value)
    {
        this->_mainBackgroundColor = ColorController::Instance().GetTaskButtonColors().press;
        this->_textColor = "#FFFFFF";
    }
    else
    {
        this->_mainBackgroundColor = ColorController::Instance().GetTaskButtonColors().idle;
        this->_textColor = ColorController::Instance().GetTaskButtonColors().color;
    }
    update();
}

bool TaskButton::IsFocused()
{
    return this->_isFocused;
}

void TaskButton::enterEvent(QEvent* event)
{
    (void)event;

    if (!IsFocused())
        this->_mainBackgroundColor = ColorController::Instance().GetTaskButtonColors().enter;
    update();
}

void TaskButton::leaveEvent(QEvent* event)
{
    (void)event;

    if (!IsFocused())
        this->_mainBackgroundColor = ColorController::Instance().GetTaskButtonColors().idle;
    update();
}

void TaskButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (this->_isMouseInCloseButton)
        {
            emit this->closeClicked();
        }
        else
        {
            if (!IsFocused())
                this->_mainBackgroundColor = ColorController::Instance().GetTaskButtonColors().press;
            this->_isPress = true;
            if (!IsFocused())
            {
                this->SetFocused(true);
                emit this->clicked(this);
            }
        }
        update();
    }
}

void TaskButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->_mainBackgroundColor = ColorController::Instance().GetTaskButtonColors().enter;
        this->_isPress = false;
        update();
    }
}

void TaskButton::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    if (x >= width() - 24 && x <= width() - 10 &&
            y >= height() - 27 + static_cast<int>(this->_isPress) && y <= height() - 13 + static_cast<int>(this->_isPress))
    {
        this->_isMouseInCloseButton = true;
        this->_mainButtonColor = ColorController::Instance().GetTaskButtonCloseButtonColors().enter;
    }
    else
    {
        this->_isMouseInCloseButton = false;
        this->_mainButtonColor = ColorController::Instance().GetTaskButtonCloseButtonColors().idle;
    }
    update();
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
                                   0 + static_cast<int>(this->_isPress),
                                   width(),
                                   height() - 1),
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
    painter.drawEllipse(QRect(10,
                              16 + static_cast<int>(this->_isPress),
                              8,
                              8));

    // draw text
    painter.setPen(QPen(QColor(this->_textColor), 1));
    painter.drawText(QPoint(32,
                            height() / 2 + 5 + static_cast<int>(this->_isPress)),
                     this->GetText());

    // draw close button
    painter.setPen(QPen(QColor(QColor(this->_mainButtonColor)), 2));
    painter.drawLine(QPointF(static_cast<qreal>(width()) - 21.5, static_cast<qreal>(height()) - 24.5 + static_cast<int>(this->_isPress)),
                     QPointF(static_cast<qreal>(width()) - 12.5, static_cast<qreal>(height()) - 15.5 + static_cast<int>(this->_isPress)));
    painter.drawLine(QPointF(static_cast<qreal>(width()) - 12.5, static_cast<qreal>(height()) - 24.5 + static_cast<int>(this->_isPress)),
                     QPointF(static_cast<qreal>(width()) - 21.5, static_cast<qreal>(height()) - 15.5 + static_cast<int>(this->_isPress)));
}
