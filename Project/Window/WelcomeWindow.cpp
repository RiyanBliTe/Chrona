#include "WelcomeWindow.h"
#include "ui_WelcomeWindow.h"
#include <QTimer>

#include "../MVC/Controller/Manager/SaveManager.h"
#include "../MVC/Controller/TaskController.h"
#include "ProgramWindow.h"

QTimer *timer;
WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WelcomeWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlag(Qt::FramelessWindowHint);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &WelcomeWindow::timerTime);
    timer->start(3000);
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
    SaveManager::Instance().LoadProgramData();
    TaskController::Instance().AfterLoad();
    timer->stop();
}
