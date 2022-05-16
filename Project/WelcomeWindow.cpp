#include "WelcomeWindow.h"
#include "ui_WelcomeWindow.h"

#include <thread>

WelcomeWindow::WelcomeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWindow),
    _timer(nullptr),
    _mainWindow(nullptr)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    this->_timer = new QTimer(this);
    connect(this->_timer, &QTimer::timeout, this, &WelcomeWindow::timerOUT);
    this->_timer->start(1000);
}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

void WelcomeWindow::timerOUT()
{
    if (this->_mainWindow != nullptr)
        this->_mainWindow->show();
    this->close();
}

void WelcomeWindow::SetMainWindow(MainWindow *value)
{
    this->_mainWindow = value;
}
