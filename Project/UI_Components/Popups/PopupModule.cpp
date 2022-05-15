#include "PopupModule.h"

PopupModule::PopupModule(QWidget *parent)
    : QWidget{parent}
    , _shadowAnimation(nullptr)
    , _shadowOFFSET(0)
    , _needBackground(true)
{
    SetMemory();
    SetupModules();
}

PopupModule::~PopupModule()
{
    while (!this->_popupStack.empty())
    {
        Popup *popup = this->_popupStack.pop();
        if (popup != nullptr)
            delete popup;
    }
}

void PopupModule::SetMemory()
{
    if (this->_shadowAnimation == nullptr)
        this->_shadowAnimation = new QPropertyAnimation(this);
}

void PopupModule::SetupModules()
{
    this->_shadowAnimation->setTargetObject(this);
    this->_shadowAnimation->setDuration(180);
    this->_shadowAnimation->setPropertyName("_shadowOFFSET");
    connect(this->_shadowAnimation, &QPropertyAnimation::finished, this, &PopupModule::shadowAnimationFinished);
}

void PopupModule::PushPopup(PopupType value)
{
    Popup* popup = nullptr;
    switch (value)
    {
    case PopupModule::PopupType::SETTINGS:
        popup = new SettingsPopup(this);
        break;

    case PopupModule::PopupType::ADDMACHINE:
        popup = new AddMachinePopup(this);
        break;
    }

    if (popup != nullptr)
    {
        popup->setGeometry(width() / 2 - popup->width() / 2,
                           height() / 2 - popup->height() / 2,
                           popup->width(),
                           popup->height());
        popup->raise();
        popup->show();
        connect(popup, &Popup::popupClosed, this, &PopupModule::refreshStatus);
        this->_popupStack.push(popup);
    }
}

void PopupModule::PopPopup()
{
    this->_popupStack.top()->hide();
    Popup *popup = this->_popupStack.pop();
    if (popup != nullptr)
        delete popup;
}

void PopupModule::Update()
{
    for (auto it = this->_popupStack.begin(); it != this->_popupStack.end(); it++)
    {
        (*it)->setGeometry(width() / 2 - (*it)->width() / 2,
                           height() / 2 - (*it)->height() / 2,
                           (*it)->width(),
                           (*it)->height());
    }
}

void PopupModule::SetShadowOFFSET(int value)
{
    this->_shadowOFFSET = value;
    update();
}

int PopupModule::GetShadowOFFSET()
{
    return this->_shadowOFFSET;
}

void PopupModule::shadowAnimationFinished()
{
    if (this->_shadowOFFSET == 0)
    {
        hide();
    }
}

void PopupModule::refreshStatus()
{
    if (this->_popupStack.empty())
    {
        this->StartHideAnimation();
    }
}

void PopupModule::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        Popup* popup = this->_popupStack.top();
        if (!(event->pos().x() >= width() / 2 - popup->width() / 2 &&
              event->pos().x() <= width() / 2 - popup->width() / 2 + popup->width() &&
              event->pos().y() >= height() / 2 - popup->height() / 2 &&
              event->pos().y() <= height() / 2 - popup->height() / 2 + popup->height()))
        {
            popup->hide();
            Popup *popup = this->_popupStack.pop();
            if (popup != nullptr)
                delete popup;

            if (this->_popupStack.empty())
            {
                this->StartHideAnimation();
            }
        }
    }
}

void PopupModule::showEvent(QShowEvent *event)
{
    (void)event;

    if (this->_shadowAnimation->state() == QPropertyAnimation::Running)
    {
        this->_shadowAnimation->stop();
    }
    this->_shadowAnimation->setStartValue(0);
    this->_shadowAnimation->setEndValue(130);
    this->_shadowAnimation->start();
}

void PopupModule::StartHideAnimation()
{
    if (this->_shadowAnimation->state() == QPropertyAnimation::Running)
    {
        this->_shadowAnimation->stop();
    }
    this->_shadowAnimation->setStartValue(130);
    this->_shadowAnimation->setEndValue(0);
    this->_shadowAnimation->start();
}

void PopupModule::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // draw background
    if (this->_needBackground)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(10, 12, 16, this->_shadowOFFSET));
        painter.drawRect(QRect(0, 0, width(), height()));
    }
}
