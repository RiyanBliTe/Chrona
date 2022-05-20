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

private:
    WelcomeWindow(QWidget *parent = nullptr);
    WelcomeWindow(const WelcomeWindow&) = delete;
    WelcomeWindow& operator=(const WelcomeWindow&) = delete;
    ~WelcomeWindow();

private slots:
    void timerOUT();

public:
    static WelcomeWindow& Instance();

    void SetMainWindow(MainWindow*);

private:
    Ui::WelcomeWindow *ui;

    QTimer *_timer;
    MainWindow *_mainWindow;
};

#define WELCOME_WINDOW WelcomeWindow::Instance()

#endif // WELCOMEWINDOW_H
