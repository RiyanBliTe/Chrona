#ifndef ADDTASKPOPUP_H
#define ADDTASKPOPUP_H

#include "Popup.h"

#include <QLineEdit>

class AddTaskPopup : public Popup
{
    Q_OBJECT
public:
    AddTaskPopup(QWidget *parent = nullptr);
    ~AddTaskPopup();

private slots:
    void addButtonPressed();
    void taskTextChanged();

private:
    void SetMemory();
    void SetupModules();

private:
    QLineEdit *_taskName;
    QPushButton *_addButton;
};

#endif // ADDTASKPOPUP_H
