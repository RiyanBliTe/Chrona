#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "UI_Components/LeftBorderButton.h"
#include "UI_Components/TasksMenuItem.h"
#include "UI_Components/TopMenuButton.h"
#include "UI_Components/ToogleButton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void machineButtonChangedFocus(LeftBorderButton*);
    void taskButtonChangedFocus(TasksMenuItem*);

private:
    void SetMemory();
    void SetupModules();

private:
    Ui::MainWindow *ui;

    LeftBorderButton *_SettingsButton;
    LeftBorderButton *_AddNewMachineButton;

    QVector<LeftBorderButton*> _machinesList;
    QVector<TasksMenuItem*> _tasksList;
    QVector<TopMenuButton*> _topButtons;
};
#endif // MAINWINDOW_H
