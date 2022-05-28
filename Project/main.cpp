#include <QApplication>
#include <QFontDatabase>

#include "View/WelcomeWindow.h"
#include "View/ProgramWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int fontRegularId = QFontDatabase::addApplicationFont(":/fonts/Fonts/Sen/Sen-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontRegularId).at(0);
    QFont applicationFont(fontFamily, 10);
    a.setFont(applicationFont);
    //WelcomeWindow::Instance().show();
    ProgramWindow::Instance().show();
    return a.exec();
}
