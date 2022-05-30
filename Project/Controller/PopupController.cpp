#include "PopupController.h"

PopupController::PopupController(QWidget *parent)
    : QWidget{parent}
    , _shadowAnimation(nullptr)
    , _shadowOFFSET(0)
    , _needBackground(true)
{
    SetMemory();
    SetupModules();
}

PopupController::~PopupController()
{
    while (!this->_popupStack.empty())
    {
        Popup *popup = this->_popupStack.pop();
        if (popup != nullptr)
            delete popup;
    }
}

void PopupController::SetMemory()
{
    if (this->_shadowAnimation == nullptr)
        this->_shadowAnimation = new QPropertyAnimation(this);
}

void PopupController::SetupModules()
{
    this->_shadowAnimation->setTargetObject(this);
    this->_shadowAnimation->setDuration(180);
    this->_shadowAnimation->setPropertyName("_shadowOFFSET");
    connect(this->_shadowAnimation, &QPropertyAnimation::finished, this, &PopupController::shadowAnimationFinished);
}

void PopupController::PushPopup(PopupType value)
{
    Popup* popup = nullptr;
    switch (value)
    {
    case PopupController::PopupType::SETTINGS:
        popup = new SettingsPopup(this);
        break;

    case PopupController::PopupType::ADDMACHINE:
        popup = new AddMachinePopup(this);
        break;

    case PopupController::PopupType::ADDTASK:
        popup = new AddTaskPopup(this);
        break;
    case PopupController::PopupType::FILEINFO:
        popup = new FileInfoPopup(this);
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
        connect(popup, &Popup::popupClosed, this, &PopupController::refreshStatus);
        connect(popup, &Popup::closeButtonPressed, this, &PopupController::popupClosedByButton);
        this->_popupStack.push(popup);
    }
}

void PopupController::PopPopup()
{
    this->_popupStack.top()->hide();
    Popup *popup = this->_popupStack.pop();
    if (popup != nullptr)
        delete popup;
}

Popup* PopupController::TopPopup()
{
    if (!this->_popupStack.empty())
    {
        return this->_popupStack.top();
    }
    return nullptr;
}

void PopupController::Update()
{
    for (auto it = this->_popupStack.begin(); it != this->_popupStack.end(); it++)
    {
        (*it)->setGeometry(width() / 2 - (*it)->width() / 2,
                           height() / 2 - (*it)->height() / 2,
                           (*it)->width(),
                           (*it)->height());
    }
}

void PopupController::SetActiveFileInfo(QString file_name, QString file_path, QString preRun, QString runAttr, int index)
{
    this->activeFile.file_name = file_name;
    this->activeFile.file_path = file_path;
    this->activeFile.preAttr = preRun;
    this->activeFile.attr = runAttr;
    this->activeFile.index = index;
}

void PopupController::SetShadowOFFSET(int value)
{
    this->_shadowOFFSET = value;
    update();
}

int PopupController::GetShadowOFFSET()
{
    return this->_shadowOFFSET;
}

void PopupController::shadowAnimationFinished()
{
    if (this->_shadowOFFSET == 0)
    {
        hide();
    }
}

void PopupController::refreshStatus()
{
    if (this->_popupStack.empty())
    {
        this->StartHideAnimation();
    }
}

void PopupController::popupClosedByButton()
{
    this->PopPopup();
    this->refreshStatus();
}

void PopupController::mousePressEvent(QMouseEvent *event)
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

void PopupController::showEvent(QShowEvent *event)
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

void PopupController::StartHideAnimation()
{
    if (this->_shadowAnimation->state() == QPropertyAnimation::Running)
    {
        this->_shadowAnimation->stop();
    }
    this->_shadowAnimation->setStartValue(130);
    this->_shadowAnimation->setEndValue(0);
    this->_shadowAnimation->start();
}

void PopupController::paintEvent(QPaintEvent *event)
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

