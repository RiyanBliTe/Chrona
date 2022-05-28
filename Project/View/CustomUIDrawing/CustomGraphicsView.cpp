#include "CustomGraphicsView.h"
#include <QDebug>
#include "../ProgramWindow.h"
#include <QMenu>
#include <QFileDialog>
#include <QFileInfo>

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView{parent}
{
    this->_CustomGraphicsScene = new CustomGraphicsScene();
    setScene(this->_CustomGraphicsScene);
    setBackgroundBrush(QBrush(QColor(ColorController::Instance().GetRightPanelColor())));
    setFrameShape(Shape::NoFrame);
}

CustomGraphicsScene* CustomGraphicsView::GetTaskConstructorScene()
{
    return this->_CustomGraphicsScene;
}

void CustomGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    this->_createdFilePosition = event->pos();
    QMenu menu(this);
    menu.addAction("New File", this, SLOT(CreateNewFile()));
    menu.addAction("Open File", this, SLOT(OpenFile()));

    menu.exec(event->globalPos());
}

void CustomGraphicsView::resizeEvent(QResizeEvent *event)
{
    scene()->setSceneRect(0, 0, event->size().width(), event->size().height());
    QGraphicsView::resizeEvent(event);
}

void CustomGraphicsView::CreateNewFile()
{
    CustomGraphicsItem *item = new CustomGraphicsItem;
    this->_CustomGraphicsScene->AddNewItem(item, this->_createdFilePosition);
}

void CustomGraphicsView::OpenFile()
{
    QString filePath = QFileDialog::getOpenFileName(0, "Open File", "", "");
    QFileInfo fileInfo(filePath);
    CustomGraphicsItem *item = new CustomGraphicsItem;
    item->GenerateImage(fileInfo.suffix());
    this->_CustomGraphicsScene->AddNewItem(item, this->_createdFilePosition);
}
