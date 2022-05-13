#include "ToogleButton.h"

ToogleButton::ToogleButton(QWidget *parent)
    : QWidget{parent}
    , _animation(nullptr)
    , _on_background_color_off("#1E2021")
    , _on_background_color_on("#76B39D")
    , _on_sliser_color_off("#76B39D")
    , _on_sliser_color_on("#1E2021")
    , _mainBackgroundColor(_on_background_color_off)
    , _mainSliserColor(_on_sliser_color_off)
    , _status(StatusType::OFF)
    , _sliserOFFSET(0)
{
    SetMemory();
    SetupModules();
}

ToogleButton::~ToogleButton()
{
    if (this->_animation != nullptr)
        delete this->_animation;
}

ToogleButton::StatusType ToogleButton::GetStatus()
{
    return this->_status;
}

void ToogleButton::SetStatus(StatusType value)
{
    this->_status = value;
}

void ToogleButton::SetMemory()
{
    if (this->_animation == nullptr)
        this->_animation = new QPropertyAnimation(this);
}

void ToogleButton::SetupModules()
{
    this->_animation->setTargetObject(this);
    this->_animation->setDuration(180);
    this->_animation->setPropertyName("_sliserOFFSET");

    setFixedSize(50, 25);
}

void ToogleButton::SetSliserOFFSET(int value)
{
    this->_sliserOFFSET = value;
    update();
}

int ToogleButton::GetSliserOFFSET()
{
    return this->_sliserOFFSET;
}

void ToogleButton::mousePressEvent(QMouseEvent *event)
{
    (void)event;

    if (this->GetStatus() == StatusType::OFF)
    {
        this->_mainBackgroundColor = this->_on_background_color_on;
        this->_mainSliserColor = this->_on_sliser_color_on;
        SetStatus(StatusType::ON);
    }
    else
    {
        this->_mainBackgroundColor = this->_on_background_color_off;
        this->_mainSliserColor = this->_on_sliser_color_off;
        SetStatus(StatusType::OFF);
    }

    this->_animation->setStartValue(this->_sliserOFFSET);
    this->_animation->setEndValue(this->_sliserOFFSET == 0 ? (width() - (height() - 6) - 6) : 0);
    this->_animation->start();

    emit this->clicked();
}

void ToogleButton::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // draw background rectangle
    painter.setPen(QPen(QColor(this->_mainBackgroundColor), 0.1));
    painter.setBrush(QColor(this->_mainBackgroundColor));
    painter.drawRoundedRect(QRect(0,
                                  0,
                                  width(),
                                  height()),
                            height() / 2,
                            height() / 2);

    // draw sliser
    painter.setPen(QPen(QColor(this->_mainSliserColor), 0.1));
    painter.setBrush(QColor(this->_mainSliserColor));
    painter.drawRoundedRect(QRect(3 + this->_sliserOFFSET,
                                  3,
                                  height() - 6,
                                  height() - 6),
                            (height() - 6) / 2,
                            (height() - 6) / 2);

}
