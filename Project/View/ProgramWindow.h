#ifndef PROGRAMWINDOW_H
#define PROGRAMWINDOW_H

#include <QMainWindow>

#include "Buttons/ComputerButton.h"
#include "Buttons/TaskButton.h"
#include "../Model/Task.h"
#include "../Model/Computer.h"
#include "../Controller/PopupController.h"
#include "CustomUIDrawing/CustomConstructor.h"

namespace Ui {
class ProgramWindow;
}

class ProgramWindow final : public QMainWindow
{
    Q_OBJECT

private:
    ProgramWindow(QWidget *parent = nullptr);
    ~ProgramWindow();
    ProgramWindow(const ProgramWindow&) = delete;
    ProgramWindow& operator=(const ProgramWindow&) = delete;

public:
    static ProgramWindow &Instance();

    void LoadComputersListToForm(const QList<std::pair<Computer*, ComputerButton*>>*);
    void LoadTasksListToForm(const QList<std::pair<Task*, TaskButton*>>*);
    void AddCompterToTorm(ComputerButton*);
    void ChangeComputerData(QString, QString);
    PopupController* GetPopupController();

protected:
    virtual void resizeEvent(QResizeEvent* event) override;
    virtual void closeEvent(QCloseEvent *event) override;

private slots:
    void SettingsButtonClicked(ComputerButton*);
    void AddMachineButtonClicked(ComputerButton*);
    void AddTaskButtonClicked();
    void AddTaskTriger(QString, QString);
    void AddMachineTriger(QString, QString);
    void GoToTheEditMode();
    void FromEditModeToInfo();

    void on_SaveButton_clicked();

private:
    void ClearLayout(QLayout* layout);

private:
    Ui::ProgramWindow *ui;

    ComputerButton *_SettingsButton;
    ComputerButton *_AddNewMachineButton;
    PopupController *_PopupModule;

    CustomConstructor *_CustomConstructor;
};

#endif // PROGRAMWINDOW_H
