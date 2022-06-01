#include "PipelineContainer.h"
#include "FileContainer.h"
#include "../../Controller/Manager/ColorManager.h"
#include "../../Controller/FileController.h"
#include "../../Controller/PipelineController.h"

#include <QDebug>
#include <QMenu>
#include <QPainter>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QContextMenuEvent>

PipelineContainer::PipelineContainer(QWidget *parent)
    : QWidget{parent}
    , _buttonRadius(9)
    , _pipeline(nullptr)
{
    qDebug() << "[CREATED]" << this;
    setFixedHeight(120);
    setLayout(new QHBoxLayout);
    layout()->setContentsMargins(0, 0, 0, 0);
    contentWidget = new QWidget;
    layout()->addWidget(contentWidget);
    layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    contentWidget->setLayout(new QHBoxLayout);
    contentWidget->layout()->setContentsMargins(25, 9, 25, 9);
    contentWidget->layout()->setSpacing(35);
}

PipelineContainer::~PipelineContainer()
{
    qDebug() << "[DELETED]" << this;
}

void PipelineContainer::AddFile(FileContainer *item)
{
    _files.append(item);
    contentWidget->layout()->addWidget(item);
    update();
}

void PipelineContainer::SetPipeline(Pipeline *pipeline)
{
    this->_pipeline = pipeline;
}

Pipeline* PipelineContainer::GetPipeline()
{
    return this->_pipeline;
}

void PipelineContainer::AddNewFile()
{
    auto pair = FileController::Instance().CreateNewFile();
    FileContainer *item = pair.second;
    PipelineController::Instance().AddFileToPipeline(this, pair.first);
    _files.append(item);
    contentWidget->layout()->addWidget(item);
    update();
}

void PipelineContainer::OpenFile()
{
    QString filePath = QFileDialog::getOpenFileName(0, "Open File", "", "");
    if (filePath != "")
    {
        QFileInfo fileInfo(filePath);
        auto pair = FileController::Instance().CreateNewFile();
        FileContainer *item = pair.second;
        PipelineController::Instance().AddFileToPipeline(this, pair.first);
        pair.first->SetName(fileInfo.fileName());
        pair.first->SetPath(filePath);
        item->GenerateImage(fileInfo.suffix());
        _files.append(item);
        contentWidget->layout()->addWidget(item);
    }
}

void PipelineContainer::OpenFiles()
{
    QStringList filePaths = QFileDialog::getOpenFileNames(0, "Open File", "", "");
    if (filePaths.size())
    {
        for (int i = 0; i < filePaths.size(); i++)
        {
            QFileInfo fileInfo(filePaths.at(i));
            auto pair = FileController::Instance().CreateNewFile();
            FileContainer *item = pair.second;
            PipelineController::Instance().AddFileToPipeline(this, pair.first);
            pair.first->SetName(fileInfo.fileName());
            pair.first->SetPath(filePaths.at(i));
            item->GenerateImage(fileInfo.suffix());
            _files.append(item);
            contentWidget->layout()->addWidget(item);
         }
    }
}

void PipelineContainer::RemovePipeline()
{
    emit removeEmited(this);
}

void PipelineContainer::contextMenuEvent(QContextMenuEvent *event)
{
    const QPoint mousePos = event->pos();
    bool isOnItem = false;
    for (auto it = this->_files.begin(); it != this->_files.end(); it++)
    {
        if (mousePos.x() >= (*it)->x() && mousePos.x() <= (*it)->x() + (*it)->width() &&
            mousePos.y() >= (*it)->y() && mousePos.y() <= (*it)->y() + (*it)->height())
        {
            isOnItem = true;
            break;
        }
    }
    if (!isOnItem)
    {
        QMenu menu(this);
        menu.addAction("Add New File", this, SLOT(AddNewFile()));
        menu.addSeparator();
        menu.addAction("Open File", this, SLOT(OpenFile()));
        menu.addAction("Open Files...", this, SLOT(OpenFiles()));
        menu.addSeparator();
        menu.addAction("Remove Pipeline", this, SLOT(RemovePipeline()));
        menu.exec(event->globalPos());
    }
}

void PipelineContainer::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor(this->_files.isEmpty() ? "#111111" : "#589E85"), 1));
    painter.setBrush(QColor(ColorManager::Instance().GetCenterPanelColor()));
    painter.drawRoundedRect(QRectF(4, 0, width() - 8, height()), 9, 9);

    painter.setBrush(QColor("#589E85"));
    painter.drawEllipse(0, height() / 2 - 4, 8, 8);
    painter.drawEllipse(width() - 8, height() / 2 - 4, 8, 8);

    QPoint prevPoint(8, height() / 2);
    for (auto it = this->_files.begin(); it != this->_files.end(); it++)
    {
        painter.drawLine(prevPoint, QPoint((*it)->x() - 4, (*it)->y() + (*it)->height() / 2));
        painter.drawEllipse(QRect((*it)->x() - 4, (*it)->y() + (*it)->height() / 2 - 4, 8, 8));
        painter.drawEllipse(QRect((*it)->x() + (*it)->width() - 4, (*it)->y() + (*it)->height() / 2 - 4, 8, 8));
        prevPoint.setX((*it)->x() + (*it)->width() + 4);
        prevPoint.setY((*it)->y() + (*it)->height() / 2);
    }
    if (!this->_files.isEmpty())
        painter.drawLine(prevPoint, QPoint(width() - 8, height() / 2));
}