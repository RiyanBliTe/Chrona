#include "WelcomeWindow.h"
#include "ui_WelcomeWindow.h"
#include <QTimer>

#include "../MVC/Controller/Manager/SaveManager.h"
#include "ProgramWindow.h"

#include <QDebug>

WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WelcomeWindow)
{
    ui->setupUi(this);
    SaveManager::Instance().LoadProgramData();
    ProgramWindow::Instance().hide();
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlag(Qt::FramelessWindowHint);

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &WelcomeWindow::timerTime);
    timer->start(4000);
}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

WelcomeWindow& WelcomeWindow::Instance()
{
    static WelcomeWindow instance;
    return instance;
}

void WelcomeWindow::timerTime()
{
    this->hide();
    ProgramWindow::Instance().show();
}
