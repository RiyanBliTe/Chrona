#ifndef POPUPCONTAINER_H
#define POPUPCONTAINER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QStack>
#include <QPropertyAnimation>
#include <QShowEvent>
#include <QHideEvent>

#include "Popup.h"
#include "SettingsPopup.h"
#include "AddMachinePopup.h"

class QPropertyAnimation;

class PopupModule : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int _shadowOFFSET READ GetShadowOFFSET WRITE SetShadowOFFSET)
public:
    PopupModule(QWidget *parent = nullptr);
    ~PopupModule();

public:
    enum class PopupType
    {
        SETTINGS,
        ADDMACHINE
    };

    void PushPopup(PopupType);
    void PopPopup();
    Popup* TopPopup();

    void Update();

private slots:
    void shadowAnimationFinished();
    void refreshStatus();
    void popupClosedByButton();

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
