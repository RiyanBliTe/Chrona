#ifndef TASKVIEW_H
#define TASKVIEW_H

#include "Constructor.h"
#include "CustomTabel.h"
#include "../Model/Task.h"

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QLineEdit>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>

class TaskView : public QWidget
{
    Q_OBJECT
public:
    explicit TaskView(QWidget *parent = nullptr);
    ~TaskView();

public:
    void GoToManage();
    void GoToEdit();

    void AddPpipeline(PipelineContainer*);
    void CheckButtonState();

    void AddHistory(Task::StatisticLineData*);
    void ChangeStatus(QString);

private slots:
    void GoToEditClicked();

private:
    QStackedWidget *_stacked;

    QWidget *_taskManage;
    Constructor *_constructor;
    QPushButton *_goToEditButton;
    QLabel *_taskName;
    CustomTabel *_tabel;

    QGridLayout *_tableLayout;
};

#endif // TASKVIEW_H
