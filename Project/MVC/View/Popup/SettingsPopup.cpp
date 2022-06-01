#include "SettingsPopup.h"
#include <QDebug>

SettingsPopup::SettingsPopup(QWidget *parent)
    : Popup{parent}
{
    qDebug() << "[CREATED]" << this;
    setFixedSize(600, 640);
    SetTitleText("Settings");
}

SettingsPopup::~SettingsPopup()
{
    qDebug() << "[DELETED]" << this;
}
