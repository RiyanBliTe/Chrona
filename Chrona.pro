QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Project/MVC/Controller/ComputerController.cpp \
    Project/MVC/Controller/FileController.cpp \
    Project/MVC/Controller/Manager/ColorManager.cpp \
    Project/MVC/Controller/Manager/NetworkManager.cpp \
    Project/MVC/Controller/Manager/PopupManager.cpp \
    Project/MVC/Controller/Manager/SaveManager.cpp \
    Project/MVC/Controller/PipelineController.cpp \
    Project/MVC/Controller/TaskController.cpp \
    Project/MVC/Model/Computer.cpp \
    Project/MVC/Model/CustomFile.cpp \
    Project/MVC/Model/Pipeline.cpp \
    Project/MVC/Model/Task.cpp \
    Project/MVC/View/Button/ComputerButton.cpp \
    Project/MVC/View/Button/TaskButton.cpp \
    Project/MVC/View/Constructor.cpp \
    Project/MVC/View/Container/FileContainer.cpp \
    Project/MVC/View/Container/PipelineContainer.cpp \
    Project/MVC/View/Popup/AddComputerPopup.cpp \
    Project/MVC/View/Popup/AddTaskPopup.cpp \
    Project/MVC/View/Popup/FileInfoPopup.cpp \
    Project/MVC/View/Popup/Popup.cpp \
    Project/MVC/View/Popup/SettingsPopup.cpp \
    Project/MVC/View/TaskView.cpp \
    Project/Window/ProgramWindow.cpp \
    Project/Window/WelcomeWindow.cpp \
    Project/main.cpp

HEADERS += \
    Project/MVC/Controller/ComputerController.h \
    Project/MVC/Controller/FileController.h \
    Project/MVC/Controller/Manager/ColorManager.h \
    Project/MVC/Controller/Manager/NetworkManager.h \
    Project/MVC/Controller/Manager/PopupManager.h \
    Project/MVC/Controller/Manager/SaveManager.h \
    Project/MVC/Controller/PipelineController.h \
    Project/MVC/Controller/TaskController.h \
    Project/MVC/Model/Computer.h \
    Project/MVC/Model/CustomFile.h \
    Project/MVC/Model/Pipeline.h \
    Project/MVC/Model/Task.h \
    Project/MVC/View/Button/ComputerButton.h \
    Project/MVC/View/Button/TaskButton.h \
    Project/MVC/View/Constructor.h \
    Project/MVC/View/Container/FileContainer.h \
    Project/MVC/View/Container/PipelineContainer.h \
    Project/MVC/View/Popup/AddComputerPopup.h \
    Project/MVC/View/Popup/AddTaskPopup.h \
    Project/MVC/View/Popup/FileInfoPopup.h \
    Project/MVC/View/Popup/Popup.h \
    Project/MVC/View/Popup/SettingsPopup.h \
    Project/MVC/View/TaskView.h \
    Project/Window/ProgramWindow.h \
    Project/Window/WelcomeWindow.h

FORMS += \
    Project/Window/ProgramWindow.ui \
    Project/Window/WelcomeWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Data/resources.qrc
