#include "Popup.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

Popup::Popup(QWidget *parent)
    : QWidget{parent}
    , _widthAnimation(nullptr)
    , _heightAnimation(nullptr)
    , _opacityAnimation(nullptr)
    , _widthOFFSET(0)
    , _heightOFFSET(0)
    , _opacityOFFSET(0)
    , _topPanel(nullptr)
    , _closeButton(nullptr)
    , _titleLabel(nullptr)
    , _separator(nullptr)
    , _centerWidget(nullptr)
{
    SetMemory();
    SetupModules();
}

Popup::~Popup()
{
    if (this->_widthAnimation != nullptr)
        delete this->_widthAnimation;
    if (this->_heightAnimation != nullptr)
        delete this->_heightAnimation;
    if (this->_opacityAnimation != nullptr)
        delete this->_opacityAnimation;
    if (this->_topPanel != nullptr)
        delete this->_topPanel;
    if (this->_centerWidget != nullptr)
        delete this->_centerWidget;
    if (this->_separator != nullptr)
        delete this->_separator;
    emit this->popupClosed();
}

void Popup::SetMemory()
{
    if (this->_widthAnimation == nullptr)
        this->_widthAnimation = new QPropertyAnimation(this);
    if (this->_heightAnimation == nullptr)
        this->_heightAnimation = new QPropertyAnimation(this);
    if (this->_opacityAnimation == nullptr)
        this->_opacityAnimation = new QPropertyAnimation(this);
    if (this->_topPanel == nullptr)
        this->_topPanel = new QWidget();
    if (this->_closeButton == nullptr)
        this->_closeButton = new QPushButton;
    if (this->_titleLabel == nullptr)
        this->_titleLabel = new QLabel();
    if (this->_centerWidget == nullptr)
        this->_centerWidget = new QWidget();
    if (this->_separator == nullptr)
        this->_separator = new QWidget();
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
    connect(this->_opacityAnimation, &QPropertyAnimation::finished, this, &Popup::openAnimationFinished);

    this->_topPanel->hide();
    this->_centerWidget->hide();
    this->_separator->hide();
    this->setLayout(new QVBoxLayout());
    this->layout()->setContentsMargins(5, 5, 5, 5);

    this->_topPanel->setFixedHeight(50);
    this->_topPanel->setLayout(new QHBoxLayout());
    this->_topPanel->setStyleSheet("QPushButton {	\
                                   background-position: center;\
                                   background-repeat: no-repeat;\
                                   border: none;\
                                   outline: none;\
                                   border-radius: 5px;\
                                   text-align: left;\
                                   background-image: url(:/Image/icon_close_bright.svg);\
                               }\
                               QPushButton:hover { background-image: url(:/Image/icon_close_dark.svg); }\
                               QPushButton:pressed { background-image: url(:/Image/icon_close_dark.svg); }");
    this->layout()->addWidget(this->_topPanel);

    this->_separator->setFixedHeight(1);
    this->_separator->setStyleSheet("background-color: rgba(130, 130, 130, 130);");
    this->layout()->addWidget(this->_separator);

    this->_titleLabel->setText("Popup");
    QFont font;
    font.setWeight(QFont::Bold);
    font.setPointSize(14);
    this->_titleLabel->setFont(font);

    this->_closeButton->setFixedSize(30, 30);
    connect(this->_closeButton, &QPushButton::clicked, this, &Popup::closePopup);

    this->_topPanel->layout()->setContentsMargins(13, 9, 9, 9);
    this->_topPanel->layout()->addWidget(this->_titleLabel);
    this->_topPanel->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
    this->_topPanel->layout()->addWidget(this->_closeButton);

    this->layout()->addWidget(this->_centerWidget);
}

void Popup::SetTitleText(QString value)
{
    this->_titleLabel->setText(value);
}

void Popup::SetWidthOFFSET(double value)
{
    this->_widthOFFSET = value;
    update();
}

double Popup::GetWidthOFFSET()
{
    return this->_widthOFFSET;
}

void Popup::SetHeightOFFSET(double value)
{
    this->_heightOFFSET = value;
    update();
}

double Popup::GetHeightOFFSET()
{
    return this->_heightOFFSET;
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

void Popup::openAnimationFinished()
{
    this->_topPanel->show();
    this->_centerWidget->show();
    this->_separator->show();
}

void Popup::closePopup()
{
    emit closeButtonPressed();
}

void Popup::showEvent(QShowEvent *event)
{
    (void)event;

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

