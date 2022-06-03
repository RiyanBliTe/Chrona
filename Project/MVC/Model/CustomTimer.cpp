#include "CustomTimer.h"
#include <QDebug>
CustomTimer::CustomTimer(QObject *parent)
    : QObject{parent}
{
    this->_timer = new QTimer(this);
    this->_timer->setInterval(1000);
    this->_timer->setSingleShot(false);
    connect(this->_timer, &QTimer::timeout, this, &CustomTimer::ChekDateTimeValid);
}

CustomTimer::~CustomTimer()
{
    delete this->_timer;
}

void CustomTimer::SetTrigerDateTime(QDateTime dateTime)
{
    this->_dateTime = dateTime;
}

void CustomTimer::Start()
{
    this->_timer->start();
}

void CustomTimer::ChekDateTimeValid()
{
    if (QDateTime::currentDateTime().toTime_t() == this->_dateTime.toTime_t() - 20)
    {
        this->_timer->stop();
        emit finishTriger(this);
    }
}
