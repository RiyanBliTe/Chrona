#ifndef DEPLOYTASKPOPUP_H
#define DEPLOYTASKPOPUP_H

#include "Popup.h"
#include "../Button/SectionButton.h"

#include <QTimeEdit>
#include <QDateEdit>
#include <QPropertyAnimation>

class QPropertyAnimation;

class DeployTaskPopup : public Popup
{
    Q_OBJECT
    Q_PROPERTY(int heightOFFSET READ GetHeightOFFSET WRITE SetHeightOFFSET)
public:
    DeployTaskPopup(QWidget *parent = nullptr);
    ~DeployTaskPopup();

private:
    void SetMemory();
    void SetupModules();

    void SetHeightOFFSET(int);
    int GetHeightOFFSET();

private slots:
    void CancelClicked();
    void DeployClicked();
    void ChangedSelection(int);
    void AnimationFinished();

private:
    QPropertyAnimation *_animation;

    SectionButton *_sections;

    QTimeEdit *_timeEdit;
    QDateEdit *_dateEdit;

    QPushButton *_cancelButton;
    QPushButton *_deployButton;

    QWidget *_dateWidget;
    QWidget *_timeWidget;
    QWidget *_group2;

    int heightOFFSET;
};

#endif // DEPLOYTASKPOPUP_H
