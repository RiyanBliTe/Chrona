#include <QApplication>

#include "Window/WelcomeWindow.h"

#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int fontRegularId = QFontDatabase::addApplicationFont(":/Font/Sen/Sen-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontRegularId).at(0);
    QFont applicationFont(fontFamily, 10);
    a.setFont(applicationFont);
    WelcomeWindow::Instance().show();
    return a.exec();
}
