#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class WelcomeWindow;
}

class WelcomeWindow final : public QMainWindow
{
    Q_OBJECT

private:
    WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow();
    WelcomeWindow(const WelcomeWindow&) = delete;
    WelcomeWindow& operator=(const WelcomeWindow&) = delete;

public:
    static WelcomeWindow &Instance();

private:
    Ui::WelcomeWindow *ui;
};

#endif // WELCOMEWINDOW_H
