#include "TaskView.h"
#include "../../Window/ProgramWindow.h"
#include "../Controller/Manager/ColorManager.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QDebug>

TaskView::TaskView(QWidget *parent)
    : QWidget{parent}
{
    qDebug() << "[CREATED]" << this;
    this->_stacked = new QStackedWidget;

    this->_taskManage = new QWidget;
    this->_constructor = new Constructor;
    this->_stacked->addWidget(this->_taskManage);
    QScrollArea *area = new QScrollArea;
    QWidget *widg = new QWidget;
    widg->setLayout(new QVBoxLayout);
    widg->layout()->setContentsMargins(0, 0, 0, 0);
    widg->layout()->addWidget(area);
    widg->setObjectName("widg");
    widg->setStyleSheet("#widg { background-color: "+ ColorManager::Instance().GetRightPanelColor() +" } ");
    area->setWidget(this->_constructor);
    area->setWidgetResizable(true);
    area->setFrameShape(QFrame::NoFrame);
    area->setObjectName("area");
    area->setStyleSheet("#area { background-color: "+ ColorManager::Instance().GetRightPanelColor() +" } ");
    this->_stacked->addWidget(widg);

    this->_taskManage->setLayout(new QVBoxLayout);
    this->_taskManage->layout()->setContentsMargins(0, 0, 0, 0);
    this->_goToEditButton = new QPushButton("Edit Mode");
    this->_goToEditButton->setFixedHeight(35);
    this->_goToEditButton->setFixedWidth(120);
    this->_taskName = new QLabel("Task");
    this->_taskName->setStyleSheet("color: rgb(243, 243, 243);");
    QWidget *topWidget = new QWidget;
    topWidget->setLayout(new QHBoxLayout);
    topWidget->setFixedHeight(40);
    topWidget->layout()->setContentsMargins(10, 3, 5, 2);
    topWidget->layout()->addWidget(this->_taskName);
    topWidget->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    topWidget->layout()->addWidget(this->_goToEditButton);
    QWidget *centerWidget = new QWidget;
    this->_taskManage->layout()->addWidget(topWidget);
    this->_taskManage->layout()->addWidget(centerWidget);
    this->_stacked->setCurrentIndex(0);

    this->_goToEditButton->setStyleSheet("QPushButton\
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
                                         }");
    connect(this->_goToEditButton, &QPushButton::clicked, this, &TaskView::GoToEditClicked);

    this->setLayout(new QVBoxLayout);
    this->layout()->setContentsMargins(9, 9, 9, 9);
    this->layout()->addWidget(this->_stacked);
}

TaskView::~TaskView()
{
    qDebug() << "[DELETED]" << this;
}

void TaskView::GoToManage()
{
    this->_stacked->setCurrentIndex(0);
    ProgramWindow::Instance().HideBackButton();
}

void TaskView::GoToEdit()
{
    this->_stacked->setCurrentIndex(1);
    ProgramWindow::Instance().ShowBackButton();
}

void TaskView::GoToEditClicked()
{
    ProgramWindow::Instance().ShowBackButton();
    this->_stacked->setCurrentIndex(1);
}

void TaskView::AddPpipeline(PipelineContainer *container)
{
    this->_constructor->AddPipeline(container);
}

void TaskView::CheckButtonState()
{
    if (this->_stacked->currentIndex() == 0)
    {
        ProgramWindow::Instance().HideBackButton();
    }
    else
    {
        ProgramWindow::Instance().ShowBackButton();
    }
}
