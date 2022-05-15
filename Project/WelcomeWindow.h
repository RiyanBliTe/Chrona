#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QWidget>
#include "MainWindow.h"
#include <QTimer>

namespace Ui {
class WelcomeWindow;
}

class WelcomeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow();

private slots:
    void timerOUT();

public:
    void SetMainWindow(MainWindow*);

private:
    Ui::WelcomeWindow *ui;

    QTimer *_timer;
    MainWindow *_mainWindow;
};

#endif // WELCOMEWINDOW_H
