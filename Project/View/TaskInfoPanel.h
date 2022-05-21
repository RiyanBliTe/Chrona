#ifndef TASKINFOPANEL_H
#define TASKINFOPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

class TaskInfoPanel : public QWidget
{
    Q_OBJECT
public:
    TaskInfoPanel(QWidget *parent = nullptr);
    ~TaskInfoPanel();

private:
    void SetMemory();
    void SetupModules();

private:
    QWidget *_headerWidget;
    QWidget *_contentWidget;

    // header
    QLabel *_taskName;
    QPushButton *_goToEditMode;
};

#endif // TASKINFOPANEL_H
