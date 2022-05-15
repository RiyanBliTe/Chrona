#ifndef POPUPCONTAINER_H
#define POPUPCONTAINER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QStack>
#include <QPropertyAnimation>
#include <QShowEvent>
#include <QHideEvent>

#include "Abstraction/Popup.h"
#include "Popups/SettingsPopup.h"

class QPropertyAnimation;

class PopupContainer : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int _shadowOFFSET READ GetShadowOFFSET WRITE SetShadowOFFSET)
public:
    PopupContainer(QWidget *parent = nullptr);

public:
    enum class PopupType
    {
        NONE,
        SETTINGS
    };

    void PushPopup(PopupType);
    void PopPopup();

    void Update();

private slots:
    void shadowAnimationFinished();

protected:
    virtual void paintEvent(QPaintEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void showEvent(QShowEvent*) override;

private:
    void SetShadowOFFSET(int);
    int GetShadowOFFSET();

    void SetMemory();
    void SetupModules();

    void StartHideAnimation();

private:
    QPropertyAnimation *_shadowAnimation;
    int _shadowOFFSET;

    QStack<Popup*> _popupStack;

    bool _needBackground;
};

#endif // POPUPCONTAINER_H
