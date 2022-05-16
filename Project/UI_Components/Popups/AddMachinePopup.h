#ifndef ADDMACHINEPOPUP_H
#define ADDMACHINEPOPUP_H

#include "Popup.h"

#include <QLineEdit>

class AddMachinePopup : public Popup
{
    Q_OBJECT
public:
    AddMachinePopup(QWidget *parent = nullptr);
    virtual ~AddMachinePopup();

private slots:
    void connectButtonPressed();

private:
    void SetMemory();
    void SetupModules();

private:
    QLineEdit *_machineName;
    QLineEdit *_machineIP;
    QPushButton *_connectButton;
};

#endif // ADDMACHINEPOPUP_H
