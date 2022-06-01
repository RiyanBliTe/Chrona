#ifndef TASKVIEW_H
#define TASKVIEW_H

#include "Constructor.h"

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>

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

private slots:
    void GoToEditClicked();

private:
    QStackedWidget *_stacked;

    QWidget *_taskManage;
    Constructor *_constructor;
    QPushButton *_goToEditButton;
    QLabel *_taskName;
};

#endif // TASKVIEW_H
