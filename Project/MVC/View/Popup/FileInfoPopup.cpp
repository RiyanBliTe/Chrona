#include "FileInfoPopup.h"

#include <QVBoxLayout>
#include <QFileDialog>

FileInfoPopup::FileInfoPopup(QWidget *parent)
    : Popup{parent}
    , _filename(nullptr)
    , _filePath(nullptr)
    , _preRunArguments(nullptr)
    , _runArguments(nullptr)
    , _runCodition(nullptr)
    , _browse(nullptr)
    , _save(nullptr)
    , _cancel(nullptr)
{
    SetMemory();
    SetupModules();
}

void FileInfoPopup::SetMemory()
{
    if (this->_filename == nullptr)
        this->_filename = new QLineEdit;
    if (this->_filePath == nullptr)
        this->_filePath = new QLineEdit;
    if (this->_preRunArguments == nullptr)
        this->_preRunArguments = new QLineEdit;
    if (this->_runArguments == nullptr)
        this->_runArguments = new QLineEdit;
    if (this->_runCodition == nullptr)
        this->_runCodition = new QComboBox;
    if (this->_browse == nullptr)
        this->_browse = new QPushButton;
    if (this->_save == nullptr)
        this->_save = new QPushButton;
    if (this->_cancel == nullptr)
        this->_cancel = new QPushButton;
}

void FileInfoPopup::SetupModules()
{
    _centerWidget->setLayout(new QVBoxLayout);

    QLabel *namelabel = new QLabel("FILE NAME");
    QFont font;
    font.setPointSize(10);
    namelabel->setFont(font);
    _centerWidget->layout()->addWidget(namelabel);
    this->_filename->setFixedHeight(40);
    this->_filename->setEnabled(false);
    _centerWidget->layout()->addWidget(this->_filename);

    QLabel *pathlabel = new QLabel("FILE PATH");
    pathlabel->setFont(font);
    _centerWidget->layout()->addWidget(pathlabel);
    QWidget *group = new QWidget;
    group->setLayout(new QHBoxLayout);
    group->layout()->setContentsMargins(0, 0, 0, 0);
    group->setFixedHeight(40);
    this->_filePath->setFixedHeight(40);
    group->layout()->addWidget(this->_filePath);
    this->_browse->setFixedHeight(40);
    this->_browse->setText("Browse");
    this->_browse->setFixedWidth(80);
    group->layout()->addWidget(this->_browse);
    _centerWidget->layout()->addWidget(group);

    QLabel *preRunLabel = new QLabel("PRE_RUN ARGIMENTS");
    preRunLabel->setFont(font);
    _centerWidget->layout()->addWidget(preRunLabel);
    this->_preRunArguments->setFixedHeight(40);
    _centerWidget->layout()->addWidget(this->_preRunArguments);

    QLabel *runLabel = new QLabel("RUN ARGIMENTS");
    runLabel->setFont(font);
    _centerWidget->layout()->addWidget(runLabel);
    this->_runArguments->setFixedHeight(40);
    _centerWidget->layout()->addWidget(this->_runArguments);

    QLabel *conditionLabel = new QLabel("RUN CONDITION");
    conditionLabel->setFont(font);
    _centerWidget->layout()->addWidget(conditionLabel);
    this->_runCodition->setFixedHeight(40);
    _centerWidget->layout()->addWidget(this->_runCodition);

    this->_runCodition->setFixedHeight(40);
    this->_runCodition->addItems({"After previous", "If previous success", "If previous failed"});
    _centerWidget->layout()->addWidget(this->_runCodition);

    QWidget *group2 = new QWidget;
    group2->setLayout(new QHBoxLayout);
    group2->layout()->setContentsMargins(0, 0, 0, 0);
    group2->setFixedHeight(40);
    this->_cancel->setFixedHeight(40);
    this->_cancel->setText("Cancel");
    this->_cancel->setObjectName("FileInfoCancelButton");
    group2->layout()->addWidget(this->_cancel);
    this->_save->setFixedHeight(40);
    this->_save->setText("Save");
    group2->layout()->addWidget(this->_save);

    _centerWidget->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    _centerWidget->layout()->addWidget(group2);

    //_filename->setText(_fileInfo.file_name);
    //_filePath->setText(_fileInfo.file_path);
    //_preRunArguments->setText(_fileInfo.preAttr);
    //_runArguments->setText(_fileInfo.attr);

    _centerWidget->setStyleSheet("\
    QLineEdit\
    {\
        border-radius: 4px;\
        background-color: rgb(227, 229, 232);\
        color: rgb(46, 51, 56);\
        padding-left: 10px;\
        padding-right: 10px;\
    }\
    QLineEdit:hover \
    {\
        background-color: rgb(221, 223, 226);\
    }\
    QLineEdit:focus \
    {\
        background-color: rgb(215, 220, 226);\
    }\
    QPushButton\
    {\
        border-radius: 4px;\
        background-color: rgb(118, 179, 157);\
        color: rgb(253, 253, 253);\
    }\
    QPushButton:hover \
    {\
        background-color: rgb(95, 167, 144);\
    }\
    QPushButton:pressed \
    {\
        background-color: rgb(88, 158, 133);\
    }\
    #FileInfoCancelButton \
    {\
        border-radius: 4px;\
        background-color: rgb(227, 229, 232);\
        color: rgb(17, 17, 17);\
    }\
    #FileInfoCancelButton:hover \
    {\
        background-color: rgb(221, 223, 226);\
    }\
    #FileInfoCancelButton:pressed \
    {\
        background-color: rgb(215, 220, 226);\
    }");
}

void FileInfoPopup::CancelClicked()
{

}

void FileInfoPopup::SaveClicked()
{
    emit closeButtonPressed();
}

void FileInfoPopup::BrowseClicked()
{
    QString filePath = QFileDialog::getOpenFileName(0, "Open File", "", "");
    if (filePath != "")
    {

    }
}
