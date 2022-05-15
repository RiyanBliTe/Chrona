#ifndef POPUP_H
#define POPUP_H

#include <QWidget>
#include <QShowEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPropertyAnimation>

class QPropertyAnimation;

class Popup : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int _widthOFFSET READ GetWidthOFFSET WRITE SetWidthOFFSET)
    Q_PROPERTY(int _heightOFFSET READ GetHeightOFFSET WRITE SetHeightOFFSET)
    Q_PROPERTY(int _opacityOFFSET READ GetOpacityOFFSET WRITE SetOpacityOFFSET)
public:
    Popup(QWidget *parent = nullptr);
protected:
    virtual void paintEvent(QPaintEvent*) override;
    virtual void showEvent(QShowEvent*) override;

private:
    void SetWidthOFFSET(int);
    int GetWidthOFFSET();

    void SetHeightOFFSET(int);
    int GetHeightOFFSET();

    void SetOpacityOFFSET(int);
    int GetOpacityOFFSET();

    void SetMemory();
    void SetupModules();

private:
    QPropertyAnimation *_widthAnimation;
    QPropertyAnimation *_heightAnimation;
    QPropertyAnimation *_opacityAnimation;
    int _widthOFFSET;
    int _heightOFFSET;
    int _opacityOFFSET;
};

#endif // POPUP_H
