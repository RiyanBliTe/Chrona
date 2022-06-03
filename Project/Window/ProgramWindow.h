#ifndef PROGRAMWINDOW_H
#define PROGRAMWINDOW_H

#include "../MVC/View/Button/ComputerButton.h"
#include "../MVC/View/Button/TaskButton.h"
#include "../MVC/Controller/Manager/PopupManager.h"
#include "../MVC/View/TaskView.h"

#include <QMenu>
#include <QMainWindow>
#include <QStackedWidget>
#include <QSystemTrayIcon>

namespace Ui {
class ProgramWindow;
}

class ProgramWindow : public QMainWindow
{
    Q_OBJECT

public:
    static ProgramWindow& Instance();

    void AddComputerButton(ComputerButton*);
    void AddTaskByIndex(int, TaskButton*);
    void SetActiveTaskWidget(int);
    void SetActiveTaskViewWidget(int);
    void AddHistoryToTaskButton(TaskButton*, Task::StatisticLineData*);
    void ChangeStatus(TaskButton*);
    void GenerateTaskConstructor(TaskButton*);
    void AddPipelineByIndex(PipelineContainer*, int);
    void SetComputerInfo(QString, QString);

    void ShowBackButton();
    void HideBackButton();
    void ShowFilePopup(FileContainer*);
    PopupManager* GetPopupManager();
    void ShowSystemTrayMessage(QString, QString, bool);

protected:
    void resizeEvent(QResizeEvent*);
    void closeEvent(QCloseEvent*);

private:
    explicit ProgramWindow(QWidget *parent = nullptr);
    ProgramWindow(const ProgramWindow&) = delete;
    ProgramWindow& operator=(const ProgramWindow&) = delete;
    ~ProgramWindow();

private:
    void SetupView();
    int GenerateTaskWidget();
    int GenerateTaskViewWidget();

private slots:
    void AddTaskButtonClicked();
    void SettingsButtonClicked(ComputerButton *button);
    void AddComputerClicked(ComputerButton *button);
    void AddTaskTriger(QString, QString);
    void AddComputerTriger(QString, QString);
    void SaveButtonClicked();
    void BackButtonClicked();
    void DeployButtonClicked();
    void TrayMenuClose();

private:
    Ui::ProgramWindow *ui;

    QStackedWidget *_taskStackedWidget;
    QStackedWidget *_taskViewStackedWidget;
    QList<std::pair<QWidget*, int>> _tasksWidgetList;
    QList<std::pair<TaskView*, int>> _tasksViewList;

    ComputerButton *_settingsButton;
    ComputerButton *_addComputerButton;

    PopupManager *_popupManager;

    QSystemTrayIcon *_systemTrayIcon;
    QMenu *_trayMenu;
    bool _needToClose;
};

#endif // PROGRAMWINDOW_H
