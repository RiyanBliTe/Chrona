#ifndef PROGRAMWINDOW_H
#define PROGRAMWINDOW_H

#include "../MVC/View/Button/ComputerButton.h"
#include "../MVC/View/Button/TaskButton.h"
#include "../MVC/Controller/Manager/PopupManager.h"
#include "../MVC/View/TaskView.h"

#include <QMainWindow>
#include <QStackedWidget>

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
    void GenerateTaskConstructor(TaskButton*);
    void AddPipelineByIndex(PipelineContainer*, int);

    void ShowBackButton();
    void HideBackButton();

protected:
    void resizeEvent(QResizeEvent*);

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

private:
    Ui::ProgramWindow *ui;

    QStackedWidget *_taskStackedWidget;
    QStackedWidget *_taskViewStackedWidget;
    QList<std::pair<QWidget*, int>> _tasksWidgetList;
    QList<std::pair<TaskView*, int>> _tasksViewList;

    ComputerButton *_settingsButton;
    ComputerButton *_addComputerButton;

    PopupManager *_popupManager;
};

#endif // PROGRAMWINDOW_H
