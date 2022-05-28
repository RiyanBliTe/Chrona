#include "InfoSpawner.h"

InfoSpawner::InfoSpawner(QWidget *parent)
    : QWidget{parent}
    , _type(InfoSpawner::SpawnerType::LEFT)
    , _widthAnimation(nullptr)
    , _heightAnimation(nullptr)
    , _opacityAnimation(nullptr)
{
    this->_widthAnimation = new QPropertyAnimation(this);
    this->_heightAnimation = new QPropertyAnimation(this);
    this->_opacityAnimation = new QPropertyAnimation(this);

    this->_widthAnimation->setTargetObject(this);
    this->_heightAnimation->setTargetObject(this);
    this->_opacityAnimation->setTargetObject(this);

    setGeometry(0, 0, 20, 20);
    this->setLayout(new QVBoxLayout());
}

InfoSpawner::~InfoSpawner()
{
    if (this->_widthAnimation != nullptr)
        delete this->_widthAnimation;
    if (this->_heightAnimation != nullptr)
        delete this->_heightAnimation;
    if (this->_opacityAnimation != nullptr)
        delete this->_opacityAnimation;
}

void InfoSpawner::AddText(QString value, bool isBold, bool isItalic)
{
    QFont font;
    font.setBold(isBold);
    font.setItalic(isItalic);
    QLabel *label = new QLabel(value);
    label->setFont(font);
    this->_labels.append(label);
    this->layout()->addWidget(label);
}

void InfoSpawner::SetType(SpawnerType value)
{
    this->_type = value;
}

void InfoSpawner::SetWidthOFFSET(int value)
{
    this->_widthOFFSET = value;
    update();
}

void InfoSpawner::SetHeightOFFSET(int value)
{
    this->_heightOFFSET = value;
    update();
}

void InfoSpawner::SetOpacityOFFSET(int value)
{
    this->_opacityOFFSET = value;
    update();
}

int InfoSpawner::GetWidthOFFSET()
{
    return this->_widthOFFSET;
}

int InfoSpawner::GetHeightOFFSET()
{
    return this->_heightOFFSET;
}

int InfoSpawner::GetOpacityOFFSET()
{
    return this->_opacityOFFSET;
}

void InfoSpawner::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(QColor(255, 255, 255, this->_opacityOFFSET));
    painter.drawRoundedRect(QRectF(width() - this->_widthOFFSET,
                                   height() - this->_heightOFFSET,
                                   width() - (width() - this->_widthOFFSET) * 2,
                                   height() - (height() - this->_heightOFFSET) * 2),
                            4, 4);
}

void InfoSpawner::showEvent(QShowEvent *event)
{
    if (this->_widthAnimation->state() == QPropertyAnimation::Running)
    {
        this->_widthAnimation->stop();
    }
    this->_widthAnimation->setStartValue(width() / 1.5);
    this->_widthAnimation->setEndValue(width());
    this->_widthAnimation->start();

    if (this->_heightAnimation->state() == QPropertyAnimation::Running)
    {
        this->_heightAnimation->stop();
    }
    this->_heightAnimation->setStartValue(height() / 1.5);
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

void InfoSpawner::hideEvent(QHideEvent *event)
{
    for (auto it = this->_labels.begin(); it != this->_labels.end(); it++)
    {
        if (*it != nullptr)
        {
            delete *it;
        }
    }
}
