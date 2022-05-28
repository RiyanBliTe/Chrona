#ifndef POPUPCONTROLLER_H
#define POPUPCONTROLLER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QStack>
#include <QPropertyAnimation>
#include <QShowEvent>
#include <QHideEvent>

#include "../View/Popups/Popup.h"
#include "../View/Popups/SettingsPopup.h"
#include "../View/Popups/AddMachinePopup.h"
#include "../View/Popups/AddTaskPopup.h"

class QPropertyAnimation;

class PopupController : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int _shadowOFFSET READ GetShadowOFFSET WRITE SetShadowOFFSET)
public:
    PopupController(QWidget *parent = nullptr);
    ~PopupController();

public:
    enum class PopupType
    {
        SETTINGS,
        ADDMACHINE,
        ADDTASK
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

#endif // POPUPCONTROLLER_H
