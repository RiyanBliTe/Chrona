#include "Popup.h"

Popup::Popup(QWidget *parent)
    : QWidget{parent}
    , _widthAnimation(nullptr)
    , _heightAnimation(nullptr)
    , _opacityAnimation(nullptr)
    , _widthOFFSET(0)
    , _heightOFFSET(0)
    , _opacityOFFSET(0)
{
    SetMemory();
    SetupModules();
}

void Popup::SetMemory()
{
    if (this->_widthAnimation == nullptr)
        this->_widthAnimation = new QPropertyAnimation(this);
    if (this->_heightAnimation == nullptr)
        this->_heightAnimation = new QPropertyAnimation(this);
    if (this->_opacityAnimation == nullptr)
        this->_opacityAnimation = new QPropertyAnimation(this);
}

void Popup::SetupModules()
{
    this->_widthAnimation->setTargetObject(this);
    this->_widthAnimation->setDuration(100);
    this->_widthAnimation->setPropertyName("_widthOFFSET");

    this->_heightAnimation->setTargetObject(this);
    this->_heightAnimation->setDuration(150);
    this->_heightAnimation->setPropertyName("_heightOFFSET");

    this->_opacityAnimation->setTargetObject(this);
    this->_opacityAnimation->setDuration(180);
    this->_opacityAnimation->setPropertyName("_opacityOFFSET");
}

void Popup::SetWidthOFFSET(int value)
{
    this->_widthOFFSET = value;
    update();
}

int Popup::GetWidthOFFSET()
{
    return this->_widthOFFSET;
}

void Popup::SetHeightOFFSET(int value)
{
    this->_heightOFFSET = value;
    update();
}

int Popup::GetHeightOFFSET()
{
    return this->_widthOFFSET;
}

void Popup::SetOpacityOFFSET(int value)
{
    this->_opacityOFFSET = value;
    update();
}

int Popup::GetOpacityOFFSET()
{
    return this->_opacityOFFSET;
}

void Popup::showEvent(QShowEvent *event)
{
    (void)event;

    if (this->_widthAnimation->state() == QPropertyAnimation::Running)
    {
        this->_widthAnimation->stop();
    }
    this->_widthAnimation->setStartValue(width() / 2);
    this->_widthAnimation->setEndValue(width());
    this->_widthAnimation->start();

    if (this->_heightAnimation->state() == QPropertyAnimation::Running)
    {
        this->_heightAnimation->stop();
    }
    this->_heightAnimation->setStartValue(height() / 2);
    this->_heightAnimation->setEndValue(height());
    this->_heightAnimation->start();

    if (this->_opacityAnimation->state() == QPropertyAnimation::Running)
    {
        this->_opacityAnimation->stop();
    }
    this->_opacityAnimation->setStartValue(0);
    this->_opacityAnimation->setEndValue(255);
    this->_opacityAnimation->start();
}

void Popup::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // draw background
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255, this->_opacityOFFSET));
    painter.drawRoundedRect(QRectF(width() - this->_widthOFFSET,
                                   height() - this->_heightOFFSET,
                                   width() - (width() - this->_widthOFFSET) * 2,
                                   height() - (height() - this->_heightOFFSET) * 2),
                            4, 4);
}
