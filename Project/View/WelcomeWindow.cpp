#include "WelcomeWindow.h"
#include "ui_WelcomeWindow.h"

WelcomeWindow::WelcomeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WelcomeWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

WelcomeWindow &WelcomeWindow::Instance()
{
    static WelcomeWindow instance;
    return instance;
}
