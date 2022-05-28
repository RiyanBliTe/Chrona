QT       += core gui network xml svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Project/Controller/ColorController.cpp \
    Project/Controller/ComputersController.cpp \
    Project/Controller/NetworkController.cpp \
    Project/Controller/PopupController.cpp \
    Project/Controller/SaveController.cpp \
    Project/Model/Computer.cpp \
    Project/Model/FileInfoPanel.cpp \
    Project/Model/Task.cpp \
    Project/View/Buttons/CnockButton.cpp \
    Project/View/Buttons/ComputerButton.cpp \
    Project/View/Buttons/TaskButton.cpp \
    Project/View/CustomUIDrawing/CustomGraphicsItem.cpp \
    Project/View/CustomUIDrawing/CustomGraphicsScene.cpp \
    Project/View/CustomUIDrawing/CustomGraphicsView.cpp \
    Project/View/Popups/AddMachinePopup.cpp \
    Project/View/Popups/AddTaskPopup.cpp \
    Project/View/Popups/Popup.cpp \
    Project/View/Popups/SettingsPopup.cpp \
    Project/View/ProgramWindow.cpp \
    Project/View/WelcomeWindow.cpp \
    Project/main.cpp

HEADERS += \
    Project/Controller/ColorController.h \
    Project/Controller/ComputersController.h \
    Project/Controller/NetworkController.h \
    Project/Controller/PopupController.h \
    Project/Controller/SaveController.h \
    Project/Model/Computer.h \
    Project/Model/FileInfoPanel.h \
    Project/Model/Task.h \
    Project/View/Buttons/CnockButton.h \
    Project/View/Buttons/ComputerButton.h \
    Project/View/Buttons/TaskButton.h \
    Project/View/CustomUIDrawing/CustomGraphicsItem.h \
    Project/View/CustomUIDrawing/CustomGraphicsScene.h \
    Project/View/CustomUIDrawing/CustomGraphicsView.h \
    Project/View/Popups/AddMachinePopup.h \
    Project/View/Popups/AddTaskPopup.h \
    Project/View/Popups/Popup.h \
    Project/View/Popups/SettingsPopup.h \
    Project/View/ProgramWindow.h \
    Project/View/WelcomeWindow.h

FORMS += \
    Project/View/ProgramWindow.ui \
    Project/View/WelcomeWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Data/resources.qrc
