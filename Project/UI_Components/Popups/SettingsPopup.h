#ifndef SETTINGSPOPUP_H
#define SETTINGSPOPUP_H

#include "../Abstraction/Popup.h"

class SettingsPopup : public Popup
{
    Q_OBJECT
public:
    SettingsPopup(QWidget *parent = nullptr);
};

#endif // SETTINGSPOPUP_H
