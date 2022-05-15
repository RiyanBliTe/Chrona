#include "MainWindow.h"
#include "WelcomeWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WelcomeWindow welcomeWindow;
    MainWindow w;
    welcomeWindow.SetMainWindow(&w);
    welcomeWindow.show();
    return a.exec();
}
