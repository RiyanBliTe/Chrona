#ifndef ADDMACHINEPOPUP_H
#define ADDMACHINEPOPUP_H

#include "Popup.h"

class AddMachinePopup : public Popup
{
    Q_OBJECT
public:
    AddMachinePopup(QWidget *parent = nullptr);
    ~AddMachinePopup();
};

#endif // ADDMACHINEPOPUP_H
