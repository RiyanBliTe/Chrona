#ifndef ADDCOMPUTERPOPUP_H
#define ADDCOMPUTERPOPUP_H

#include "Popup.h"

#include <QLineEdit>

class AddComputerPopup : public Popup
{
    Q_OBJECT
public:
    AddComputerPopup(QWidget *parent = nullptr);

private slots:
    void connectButtonPressed();
    void taskTextChanged();

private:
    void SetMemory();
    void SetupModules();

private:
    QLineEdit *_machineName;
    QLineEdit *_machineIP;
    QPushButton *_connectButton;
};

#endif // ADDCOMPUTERPOPUP_H
