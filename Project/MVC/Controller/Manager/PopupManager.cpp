#include "PopupManager.h"

#include <QMouseEvent>

PopupManager::PopupManager(QWidget *parent)
    : QWidget{parent}
    , _shadowAnimation(nullptr)
    , _shadowOFFSET(0)
    , _needBackground(true)
    , _file(nullptr)
{
    SetMemory();
    SetupModules();
    hide();
}

PopupManager::~PopupManager()
{
    while (!this->_popupStack.empty())
    {
        Popup *popup = this->_popupStack.pop();
        if (popup != nullptr)
            delete popup;
    }
}

void PopupManager::SetMemory()
{
    if (this->_shadowAnimation == nullptr)
        this->_shadowAnimation = new QPropertyAnimation(this);
}

void PopupManager::SetupModules()
{
    this->_shadowAnimation->setTargetObject(this);
    this->_shadowAnimation->setDuration(180);
    this->_shadowAnimation->setPropertyName("_shadowOFFSET");
    connect(this->_shadowAnimation, &QPropertyAnimation::finished, this, &PopupManager::shadowAnimationFinished);
}

void PopupManager::PushPopup(PopupType value)
{
    Popup* popup = nullptr;
    switch (value)
    {
    case PopupManager::PopupType::SETTINGS:
        popup = new SettingsPopup(this);
        break;

    case PopupManager::PopupType::ADDMACHINE:
        popup = new AddComputerPopup(this);
        break;

    case PopupManager::PopupType::ADDTASK:
        popup = new AddTaskPopup(this);
        break;
    case PopupManager::PopupType::FILEINFO:
        popup = new FileInfoPopup(this, this->_file);
        break;
    case PopupManager::PopupType::DEPLOY:
        popup = new DeployTaskPopup(this);
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
        connect(popup, &Popup::popupClosed, this, &PopupManager::refreshStatus);
        connect(popup, &Popup::closeButtonPressed, this, &PopupManager::popupClosedByButton);
        this->_popupStack.push(popup);
    }
}

void PopupManager::PopPopup()
{
    this->_popupStack.top()->hide();
    Popup *popup = this->_popupStack.pop();
    if (popup != nullptr)
        delete popup;
}

Popup* PopupManager::TopPopup()
{
    if (!this->_popupStack.empty())
    {
        return this->_popupStack.top();
    }
    return nullptr;
}

void PopupManager::Update()
{
    for (auto it = this->_popupStack.begin(); it != this->_popupStack.end(); it++)
    {
        (*it)->setGeometry(width() / 2 - (*it)->width() / 2,
                           height() / 2 - (*it)->height() / 2,
                           (*it)->width(),
                           (*it)->height());
    }
}

void PopupManager::UsedFile(CustomFile *file)
{
    this->_file = file;
}

void PopupManager::SetShadowOFFSET(int value)
{
    this->_shadowOFFSET = value;
    update();
}

int PopupManager::GetShadowOFFSET()
{
    return this->_shadowOFFSET;
}

void PopupManager::shadowAnimationFinished()
{
    if (this->_shadowOFFSET == 0)
    {
        hide();
    }
}

void PopupManager::refreshStatus()
{
    if (this->_popupStack.empty())
    {
        this->StartHideAnimation();
    }
}

void PopupManager::popupClosedByButton()
{
    this->PopPopup();
    this->refreshStatus();
}

void PopupManager::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (!this->_popupStack.empty())
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
        else
        {
            this->StartHideAnimation();
        }
    }
}

void PopupManager::showEvent(QShowEvent *event)
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

void PopupManager::StartHideAnimation()
{
    if (this->_shadowAnimation->state() == QPropertyAnimation::Running)
    {
        this->_shadowAnimation->stop();
    }
    this->_shadowAnimation->setStartValue(130);
    this->_shadowAnimation->setEndValue(0);
    this->_shadowAnimation->start();
}

void PopupManager::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // draw background
    if (this->_needBackground)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0, 0, 0, this->_shadowOFFSET));
        painter.drawRect(QRect(0, 0, width(), height()));
    }
}
