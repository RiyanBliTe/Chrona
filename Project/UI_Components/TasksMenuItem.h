#ifndef TASKSMENUITEM_H
#define TASKSMENUITEM_H

#include <QWidget>

namespace Ui {
class TasksMenuItem;
}

class TasksMenuItem : public QWidget
{
    Q_OBJECT

public:
    enum MenuItemState
    {
        IDLE,
        RUNNING,
        FINISHED,
        FAILED
    };

public:
    explicit TasksMenuItem(QWidget *parent = nullptr);
    ~TasksMenuItem();

    void SetFocused(bool);

    void SetText(QString);
    void SetState(MenuItemState);

protected:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void SetupModules();
    void EnterUI();
    void LeaveUI();

signals:
    void focusChanged(TasksMenuItem*);

private:
    Ui::TasksMenuItem *ui;

    bool _isFocused;

    QString _enteredStyle;
    QString _leavedStyle;
    QString _pressedStyle;

    MenuItemState _buttonState;
};

#endif // TASKSMENUITEM_H
