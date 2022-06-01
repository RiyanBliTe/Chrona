#include "WelcomeWindow.h"
#include "ui_WelcomeWindow.h"
#include <QTimer>

#include "../MVC/Controller/Manager/SaveManager.h"
#include "ProgramWindow.h"

#include <QDebug>
QTimer *timer;
WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WelcomeWindow)
{
    qDebug() << "[CREATED]" << this;
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlag(Qt::FramelessWindowHint);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &WelcomeWindow::timerTime);
    timer->start(4000);
}

WelcomeWindow::~WelcomeWindow()
{
    qDebug() << "[DELETED]" << this;
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
    timer->stop();
}
