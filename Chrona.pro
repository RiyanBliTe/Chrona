QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Project/UI_Components/Popups/AddMachinePopup.cpp \
    Project/UI_Components/Popups/Popup.cpp \
    Project/UI_Components/BlockSwitchButton.cpp \
    Project/UI_Components/LeftBorderButton.cpp \
    Project/UI_Components/Popups/PopupModule.cpp \
    Project/UI_Components/Popups/SettingsPopup.cpp \
    Project/UI_Components/TaskButton.cpp \
    Project/UI_Components/ToogleButton.cpp \
    Project/UI_Components/TopMenuButton.cpp \
    Project/WelcomeWindow.cpp \
    Project/main.cpp \
    Project/MainWindow.cpp

HEADERS += \
    Project/Settings.h \
    Project/UI_Components/Popups/AddMachinePopup.h \
    Project/UI_Components/Popups/Popup.h \
    Project/UI_Components/BlockSwitchButton.h \
    Project/UI_Components/LeftBorderButton.h \
    Project/MainWindow.h \
    Project/UI_Components/Popups/PopupModule.h \
    Project/UI_Components/Popups/SettingsPopup.h \
    Project/UI_Components/TaskButton.h \
    Project/UI_Components/ToogleButton.h \
    Project/UI_Components/TopMenuButton.h \
    Project/WelcomeWindow.h

FORMS += \
    Project/MainWindow.ui \
    Project/WelcomeWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Data/resources.qrc
