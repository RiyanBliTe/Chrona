#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QResizeEvent>

#include "../Model/Computer.h"

#include "ComputerButton.h"
#include "TopMenuButton.h"
#include "ToogleButton.h"
#include "TaskButton.h"
#include "Popups/PopupModule.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow
{
    Q_OBJECT

private:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;

public:
    static MainWindow& Instance();

    void LoadComputers(const QList<Computer*>&);
    void LoadTasks(const QList<Task*>&);

protected:
    virtual void resizeEvent(QResizeEvent*) override;

private slots:
    void machineButtonChangedFocus(ComputerButton*);
    void settingsButtonClicked();
    void addMachineButtonClicked();
    void AddMachineTriger(QString, QString);
    void AddTaskTriger(QString, QString);

    void on_pushButton_2_clicked();

private:
    void SetMemory();
    void SetupModules();

private:
    Ui::MainWindow *ui;

    ComputerButton *_SettingsButton;
    ComputerButton *_AddNewMachineButton;

    PopupModule *_PopupModule;

    QVector<ComputerButton*> _machinesList;
    QVector<TaskButton*> _taskButtonsList;
    QVector<TopMenuButton*> _topButtons;
};

#define MAINWINDOW MainWindow::Instance()

#endif // MAINWINDOW_H