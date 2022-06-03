#ifndef POPUPMANAGER_H
#define POPUPMANAGER_H

#include "../../View/Popup/Popup.h"
#include "../../View/Popup/SettingsPopup.h"
#include "../../View/Popup/AddComputerPopup.h"
#include "../../View/Popup/AddTaskPopup.h"
#include "../../View/Popup/FileInfoPopup.h"
#include "../../View/Popup/DeployTaskPopup.h"

#include "../../Model/CustomFile.h"

#include <QWidget>
#include <QStack>
#include <QPropertyAnimation>

class QPropertyAnimation;

class PopupManager : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int _shadowOFFSET READ GetShadowOFFSET WRITE SetShadowOFFSET)
public:
    explicit PopupManager(QWidget *parent = nullptr);
    ~PopupManager();

public:
    enum class PopupType
    {
        SETTINGS,
        ADDMACHINE,
        ADDTASK,
        FILEINFO,
        DEPLOY
    };

    void PushPopup(PopupType);
    void PopPopup();
    Popup* TopPopup();

    void Update();
    void UsedFile(CustomFile*);

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

    CustomFile *_file;
};

#endif // POPUPMANAGER_H
