#include "SettingsPopup.h"

SettingsPopup::SettingsPopup(QWidget *parent)
    : Popup{parent}
{
    setFixedSize(600, 640);
    SetTitleText("Settings");
}

SettingsPopup::~SettingsPopup()
{}
