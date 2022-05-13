#ifndef TOPMENUBUTTON_H
#define TOPMENUBUTTON_H

#include <QWidget>
#include <QMouseEvent>
#include <QEnterEvent>
#include <QPaintEvent>
#include <QEvent>
#include <QPainter>

class TopMenuButton : public QWidget
{
    Q_OBJECT
public:
    explicit TopMenuButton(QWidget *parent = nullptr);

public:
    void SetText(QString);

protected:
    virtual void enterEvent(QEnterEvent*) override;
    virtual void leaveEvent(QEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;

    virtual void paintEvent(QPaintEvent*) override;

signals:
    void clicked();

private:
    QString _on_idle_event_color;
    QString _on_enter_event_color;
    QString _on_press_event_color;

    QString _mainColor;

    QString _buttonText;

    bool _isPressed;
};

#endif // TOPMENUBUTTON_H
