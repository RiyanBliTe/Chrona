#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class WelcomeWindow;
}

class WelcomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    static WelcomeWindow& Instance();

private:
    explicit WelcomeWindow(QWidget *parent = nullptr);
    WelcomeWindow(const WelcomeWindow&) = delete;
    WelcomeWindow& operator=(const WelcomeWindow&) = delete;
    ~WelcomeWindow();

private slots:
    void timerTime();

private:
    Ui::WelcomeWindow *ui;
};

#endif // WELCOMEWINDOW_H
