#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QResizeEvent>

#include "UI_Components/LeftBorderButton.h"
#include "UI_Components/TopMenuButton.h"
#include "UI_Components/ToogleButton.h"
#include "UI_Components/TaskButton.h"
#include "UI_Components/Popups/PopupModule.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void resizeEvent(QResizeEvent*) override;

private slots:
    void machineButtonChangedFocus(LeftBorderButton*);
    void settingsButtonClicked();
    void addMachineButtonClicked();
    void AddMachineTriger(QString, QString);

private:
    void SetMemory();
    void SetupModules();

private:
    Ui::MainWindow *ui;

    LeftBorderButton *_SettingsButton;
    LeftBorderButton *_AddNewMachineButton;

    PopupModule *_PopupModule;

    QVector<LeftBorderButton*> _machinesList;
    QVector<TaskButton*> _taskButtonsList;
    QVector<TopMenuButton*> _topButtons;
};
#endif // MAINWINDOW_H
