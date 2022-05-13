#ifndef LEFTBORDERBUTTON_H
#define LEFTBORDERBUTTON_H

#include <QWidget>
#include <QPainter>
#include <math.h>
#include <QAbstractButton>
#include <QHBoxLayout>
#include <QPropertyAnimation>

#include "../Settings.h"

class QPropertyAnimation;

// *************************************************************
// Center Button class
// *************************************************************
class CenterButton : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(int _animationOFFSET READ GetAnimationOFFSET WRITE SetAnimationOFFSET)
public:
    CenterButton(QWidget *parent = nullptr);
    CenterButton(const CenterButton&);
    ~CenterButton();

    CenterButton& operator=(const CenterButton&);

    virtual QSize sizeHint() const override;

    void Hide();
    void Show();

    void Pin();
    void UnPin();

    void SetFocused(bool);
    bool IsFocused();

    void SetImage(QString);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void entered();
    void leaved();

private:
    void SetMemory();
    void SetupModules();

    void SetAnimationOFFSET(int);
    int GetAnimationOFFSET();

private:
    QPropertyAnimation *_resizeAnimation;

    int _animationOFFSET;
    int _pressShift;

    bool _isFocused;
    bool _hasImage;
    bool _isHiden;
    bool _isPinned;

    QString _selectedColor;

    QString _imagePath;

    static const int ICON_SIZE = 48;
};

// *************************************************************
// Border Rounded Rectangle class
// *************************************************************
class BorderRoundedRectungle : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int _widthOFFSET READ GetWidthOFFSET WRITE SetWidthOFFSET)
    Q_PROPERTY(int _heightOFFSET READ GetHeightOFFSET WRITE SetHeightOFFSET)
public:
    BorderRoundedRectungle(QWidget *parent = nullptr);
    ~BorderRoundedRectungle();

    void StartEnteredAnimation();
    void StartLeavedAnimation();
    void StartPressedAnimation();

    void SetFocused(bool);
    bool IsFocused();

    void SetDrawEnabled(bool);

    void Hide();
    void Show();

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void SetMemory();
    void SetupModules();

    void SetWidthOFFSET(int);
    int GetWidthOFFSET();
    void SetHeightOFFSET(int);
    int GetHeightOFFSET();

private slots:
    void LeaveAnimationFinished();

private:
    QPropertyAnimation *_widthAnimation;
    QPropertyAnimation *_heightAnimation;

    bool _needDraw;
    bool _animClock;
    bool _isFocused;
    bool _isHiden;

    int _widthOFFSET;
    int _heightOFFSET;

    static const int LEFT_PANEL_HEIGHT_MIN = 20;
    static const int LEFT_PANEL_HEIGHT_MAX = 40;
};

// *************************************************************
// Left Border Button class
// *************************************************************
class LeftBorderButton : public QWidget
{
    Q_OBJECT

public:
    LeftBorderButton(QWidget *parent = nullptr);
    ~LeftBorderButton();

    void SetFocused(bool);
    bool IsFocused();
    void SetLeftPanelEnabled(bool);
    void SetImage(QString);

private:
    void SetMemory();
    void SetupModules();

private slots:
    void PanelButtonEntered();
    void PanelButtonLeaved();
    void PanelButtonPressed();

signals:
    void focusChanged(LeftBorderButton*);

private:
    QHBoxLayout *_mainLayout;
    QWidget *_leftPanel;
    QWidget *_rightPanel;

    CenterButton *_rightPanelButton;
    BorderRoundedRectungle *_leftPanelRect;

    static const int WIDTH = 72;
    static const int HEIGHT = 50;
};

#endif // LEFTBORDERBUTTON_H
