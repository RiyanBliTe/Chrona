#ifndef TOOGLEBUTTON_H
#define TOOGLEBUTTON_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPropertyAnimation>

class QPropertyAnimation;

class ToogleButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int _sliserOFFSET READ GetSliserOFFSET WRITE SetSliserOFFSET)
public:
    explicit ToogleButton(QWidget *parent = nullptr);
    ~ToogleButton();

public:
    enum class StatusType
    {
        ON,
        OFF
    };

    StatusType GetStatus();
    void SetStatus(StatusType);

    void SetMemory();
    void SetupModules();

protected:
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void paintEvent(QPaintEvent*) override;

signals:
    void clicked();

private:
    void SetSliserOFFSET(int);
    int GetSliserOFFSET();

private:
    QPropertyAnimation *_animation;

    QString _on_background_color_off;
    QString _on_background_color_on;
    QString _on_sliser_color_off;
    QString _on_sliser_color_on;
    QString _mainBackgroundColor;
    QString _mainSliserColor;

    StatusType _status;

    int _sliserOFFSET;
};

#endif // TOOGLEBUTTON_H
