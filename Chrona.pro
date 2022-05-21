QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Project/Model/Computer.cpp \
    Project/Controller/ComputersManager.cpp \
    Project/Controller/ConnectionManager.cpp \
    Project/Controller/SaveManager.cpp \
    Project/Model/Task.cpp \
    Project/View/ComputerButton.cpp \
    Project/View/Popups/AddMachinePopup.cpp \
    Project/View/Popups/AddTaskPopup.cpp \
    Project/View/Popups/Popup.cpp \
    Project/View/Popups/PopupModule.cpp \
    Project/View/Popups/SettingsPopup.cpp \
    Project/View/TaskButton.cpp \
    Project/View/TaskInfoPanel.cpp \
    Project/View/ToogleButton.cpp \
    Project/View/TopMenuButton.cpp \
    Project/View/WelcomeWindow.cpp \
    Project/main.cpp \
    Project/View/MainWindow.cpp

HEADERS += \
    Project/Model/Computer.h \
    Project/Controller/ComputersManager.h \
    Project/Controller/ConnectionManager.h \
    Project/Controller/SaveManager.h \
    Project/Settings.h \
    Project/Model/Task.h \
    Project/View/ComputerButton.h \
    Project/View/Popups/AddMachinePopup.h \
    Project/View/Popups/AddTaskPopup.h \
    Project/View/Popups/Popup.h \
    Project/View/MainWindow.h \
    Project/View/Popups/PopupModule.h \
    Project/View/Popups/SettingsPopup.h \
    Project/View/TaskButton.h \
    Project/View/TaskInfoPanel.h \
    Project/View/ToogleButton.h \
    Project/View/TopMenuButton.h \
    Project/View/WelcomeWindow.h

FORMS += \
    Project/View/MainWindow.ui \
    Project/View/WelcomeWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Data/resources.qrc
