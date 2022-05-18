#include "MainWindow.h"
#include "WelcomeWindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // setup default font
    int fontRegularId = QFontDatabase::addApplicationFont(":/fonts/Fonts/Sen/Sen-Regular.ttf");
    int fontBoldId = QFontDatabase::addApplicationFont(":/fonts/Fonts/Sen/Sen-Bold.ttf");
    int fontExtraBoldId = QFontDatabase::addApplicationFont(":/fonts/Fonts/Sen/Sen-ExtraBold.ttf");
    Settings::GetInstance().SetSenFontIds(fontRegularId, fontBoldId, fontExtraBoldId);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontRegularId).at(0);
    QFont applicationFont(fontFamily, 10);
    a.setFont(applicationFont);

    WelcomeWindow::Instance().SetMainWindow(&MainWindow::Instance());
    WelcomeWindow::Instance().show();
    return a.exec();
}
