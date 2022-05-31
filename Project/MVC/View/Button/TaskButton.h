#ifndef TASKBUTTON_H
#define TASKBUTTON_H

#include "../../Model/Task.h"

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

class TaskButton : public QWidget
{
    Q_OBJECT
public:
    TaskButton(QWidget *parent = nullptr);
    ~TaskButton();

public:
    enum class TaskStatus
    {
        IDLE,
        RUNNING,
        SUCCESS,
        FAILED
    };

    void SetStatus(TaskStatus);
    TaskStatus GetStatus();

    void SetText(QString&);
    QString& GetText();

    void SetFocused(bool);
    bool IsFocused();

    void SetTask(Task*);
    Task* GetTask();

    void SetStackedIndex(int);
    int GetStackedIndex();

protected:
    virtual void enterEvent(QEvent*) override;
    virtual void leaveEvent(QEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;
    virtual void mouseMoveEvent(QMouseEvent*) override;
    virtual void paintEvent(QPaintEvent*) override;

signals:
    void clicked(TaskButton*);
    void closeClicked();

private:
    QString _mainBackgroundColor;
    QString _mainButtonColor;
    QString _textColor;
    QString _buttonText;

    TaskStatus _buttonStatus;

    bool _isPress;
    bool _isMouseInCloseButton;
    bool _isFocused;

    Task* _task;
    int _stackedIndex;
};

#endif // TASKBUTTON_H
