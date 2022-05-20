#ifndef POPUP_H
#define POPUP_H

#include <QWidget>
#include <QShowEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>

#include "../../Settings.h"

class QPropertyAnimation;

class Popup : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double _widthOFFSET READ GetWidthOFFSET WRITE SetWidthOFFSET)
    Q_PROPERTY(double _heightOFFSET READ GetHeightOFFSET WRITE SetHeightOFFSET)
    Q_PROPERTY(int _opacityOFFSET READ GetOpacityOFFSET WRITE SetOpacityOFFSET)
public:
    Popup(QWidget *parent = nullptr);
    virtual ~Popup();

signals:
    void popupClosed();
    void closeButtonPressed();
    void connectedSucces(QString, QString);
    void addTask(QString, QString);

protected:
    virtual void paintEvent(QPaintEvent*) override;
    virtual void showEvent(QShowEvent*) override;

private slots:
    void openAnimationFinished();

protected slots:
    void closePopup();

private:
    void SetWidthOFFSET(double);
    double GetWidthOFFSET();

    void SetHeightOFFSET(double);
    double GetHeightOFFSET();

    void SetOpacityOFFSET(int);
    int GetOpacityOFFSET();

    void SetMemory();
    void SetupModules();

protected:
    void SetTitleText(QString);

private:
    // animation
    QPropertyAnimation *_widthAnimation;
    QPropertyAnimation *_heightAnimation;
    QPropertyAnimation *_opacityAnimation;
    double _widthOFFSET;
    double _heightOFFSET;
    int _opacityOFFSET;

    // content
    QWidget *_topPanel;
    QPushButton *_closeButton;
    QLabel *_titleLabel;
    QWidget *_separator;

protected:
    QWidget *_centerWidget;
};

#endif // POPUP_H
