#include "Constructor.h"
#include "../Controller/Manager/ColorManager.h"
#include "../Controller/PipelineController.h"
#include "../Controller/TaskController.h"

#include <QMenu>
#include <QDebug>
#include <QPainter>
#include <QVBoxLayout>
#include <QContextMenuEvent>
#include <QDebug>

Constructor::Constructor(QWidget *parent)
    : QWidget{parent}
{
    qDebug() << "[CREATED]" << this;
    setLayout(new QVBoxLayout);
    layout()->setContentsMargins(80, 10, 80, 10);
    layout()->setSpacing(35);
}

Constructor::~Constructor()
{
    qDebug() << "[DELETED]" << this;
}

void Constructor::AddNewPipeline()
{
    auto pair = PipelineController::Instance().CreateNewPipeline();
    PipelineContainer *pipeline = pair.second;
    TaskController::Instance().AddPipelineToActiveTask(pair.first);

    this->_panels.append(pipeline);
    layout()->addWidget(pipeline);
    connect(pipeline, &PipelineContainer::removeEmited, this, &Constructor::RemovePipeline);
    update();
}

void Constructor::RemovePipeline(PipelineContainer *container)
{
    container->hide();
    this->_panels.removeOne(container);
    TaskController::Instance().RemovePipeline(PipelineController::Instance().GetPipelineByView(container));
    update();
}

void Constructor::contextMenuEvent(QContextMenuEvent *event)
{
    const QPoint mousePos = event->pos();
    bool isOnItem = false;
    for (auto it = this->_panels.begin(); it != this->_panels.end(); it++)
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
        menu.addAction("Add new pipeline", this, SLOT(AddNewPipeline()));
        menu.exec(event->globalPos());
    }
}

void Constructor::AddPipeline(PipelineContainer *container)
{
    this->_panels.append(container);
    layout()->addWidget(container);
    connect(container, &PipelineContainer::removeEmited, this, &Constructor::RemovePipeline);
    update();
}

void Constructor::paintEvent(QPaintEvent*)
{
    int sphereRadius = 15;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(QColor(ColorManager::Instance().GetRightPanelColor()));
    painter.drawRect(rect());

    painter.setPen(QPen(QColor("#589E85"), 2));
    painter.setBrush(QColor("#202225"));

    QPoint leftSphereCenterRight(sphereRadius * 2, height() / 2);
    QPoint rightSphereCenterLeft(width() - sphereRadius * 2, height() / 2);
    for (auto it = this->_panels.begin(); it != this->_panels.end(); it++)
    {
        QPoint itemLeftCenter((*it)->x(), (*it)->y() + (*it)->height() / 2);
        QPoint itemRightCenter((*it)->x() + (*it)->width(), (*it)->y() + (*it)->height() / 2);
        int widthToItem = (*it)->x() - (leftSphereCenterRight.x());
        int halfWidth = widthToItem / 2;
        int fourthWidth = halfWidth / 2;


        // top
        if ((*it)->y() + (*it)->height() / 2 < leftSphereCenterRight.y() - widthToItem)
        {
            // left side
            painter.drawLine(leftSphereCenterRight,
                             QPoint(leftSphereCenterRight.x() + fourthWidth, leftSphereCenterRight.y()));
            painter.drawArc(QRect(leftSphereCenterRight.x(),
                                  leftSphereCenterRight.y() - halfWidth,
                                  halfWidth,
                                  halfWidth),
                            270 * 16,
                            90 * 16);
            painter.drawLine(leftSphereCenterRight.x() + halfWidth,
                             leftSphereCenterRight.y() - fourthWidth,
                             itemLeftCenter.x() - halfWidth,
                             itemLeftCenter.y() + fourthWidth);
            painter.drawArc(QRect(itemLeftCenter.x() - halfWidth,
                                  itemLeftCenter.y(),
                                  halfWidth,
                                  halfWidth),
                            90 * 16,
                            90 * 16);
            painter.drawLine(itemLeftCenter.x() - fourthWidth,
                             itemLeftCenter.y(),
                             itemLeftCenter.x(),
                             itemLeftCenter.y());

            // right side
            painter.drawLine(itemRightCenter,
                             QPoint(itemRightCenter.x() + fourthWidth, itemRightCenter.y()));
            painter.drawArc(QRect(itemRightCenter.x(),
                                  itemRightCenter.y(),
                                  halfWidth,
                                  halfWidth),
                            0,
                            90 * 16);
            painter.drawLine(itemRightCenter.x() + halfWidth,
                             itemRightCenter.y() + fourthWidth,
                             rightSphereCenterLeft.x() - halfWidth,
                             rightSphereCenterLeft.y() - fourthWidth);
            painter.drawArc(QRect(rightSphereCenterLeft.x() - halfWidth,
                                  rightSphereCenterLeft.y() - halfWidth,
                                  halfWidth,
                                  halfWidth),
                            180 * 16,
                            90 * 16);
            painter.drawLine(rightSphereCenterLeft.x() - fourthWidth,
                             rightSphereCenterLeft.y(),
                             rightSphereCenterLeft.x(),
                             rightSphereCenterLeft.y());
        }
        // bottom
        else if ((*it)->y() + (*it)->height() / 2 > leftSphereCenterRight.y() + widthToItem)
        {
            // left side
            painter.drawLine(leftSphereCenterRight,
                             QPoint(leftSphereCenterRight.x() + fourthWidth, leftSphereCenterRight.y()));
            painter.drawArc(QRect(leftSphereCenterRight.x(),
                                  leftSphereCenterRight.y(),
                                  halfWidth,
                                  halfWidth),
                            0,
                            90 * 16);
            painter.drawLine(leftSphereCenterRight.x() + halfWidth,
                             leftSphereCenterRight.y() + fourthWidth,
                             itemLeftCenter.x() - halfWidth,
                             itemLeftCenter.y() - fourthWidth);
            painter.drawArc(QRect(itemLeftCenter.x() - halfWidth,
                                  itemLeftCenter.y() - halfWidth,
                                  halfWidth,
                                  halfWidth),
                            180 * 16,
                            90 * 16);
            painter.drawLine(itemLeftCenter.x() - fourthWidth,
                             itemLeftCenter.y(),
                             itemLeftCenter.x(),
                             itemLeftCenter.y());

            // right side
            painter.drawLine(itemRightCenter,
                             QPoint(itemRightCenter.x() + fourthWidth, itemRightCenter.y()));
            painter.drawArc(QRect(itemRightCenter.x(),
                                  itemRightCenter.y() - halfWidth,
                                  halfWidth,
                                  halfWidth),
                            270 * 16,
                            90 * 16);
            painter.drawLine(itemRightCenter.x() + halfWidth,
                             itemRightCenter.y() - fourthWidth,
                             rightSphereCenterLeft.x() - halfWidth,
                             rightSphereCenterLeft.y() + fourthWidth);
            painter.drawArc(QRect(rightSphereCenterLeft.x() - halfWidth,
                                  rightSphereCenterLeft.y(),
                                  halfWidth,
                                  halfWidth),
                            90 * 16,
                            90 * 16);
            painter.drawLine(rightSphereCenterLeft.x() - fourthWidth,
                             rightSphereCenterLeft.y(),
                             rightSphereCenterLeft.x(),
                             rightSphereCenterLeft.y());
        }
        // center
        else
        {
            painter.drawLine(leftSphereCenterRight, itemLeftCenter);
            painter.drawLine(itemRightCenter, rightSphereCenterLeft);
        }
    }

    painter.setPen(this->_panels.isEmpty() ? Qt::NoPen : QPen(QColor("#589E85"), 2));
    painter.setBrush(QColor("#202225"));
    painter.drawEllipse(QRect(3, height() / 2 - sphereRadius, sphereRadius * 2, sphereRadius * 2));
    painter.drawEllipse(QRect(width() - sphereRadius * 2 - 1, height() / 2 - sphereRadius, sphereRadius * 2, sphereRadius * 2));
    painter.setPen(QPen(QColor("#F9F8EB"), 1));
    painter.drawText(QPoint(0, height() / 2 - sphereRadius - 10), "Begin");
    painter.drawText(QPoint(width() - sphereRadius * 2 + 2, height() / 2 - sphereRadius - 10), "End");

    if (this->_panels.isEmpty())
    {
        painter.setPen(QPen(QColor(ColorManager::Instance().GetLeftPanelColor()), 1));
        QFont font;
        font.setPointSize(26);
        font.setBold(true);
        QFontMetrics fontMetrix(font);
        int textWidth = fontMetrix.horizontalAdvance("Right click to add new pipeline");
        int textHeight = fontMetrix.height();
        painter.setFont(font);
        painter.drawText(QPoint(width() / 2 - textWidth / 2, height() / 2 + textHeight / 5), "Right click to add new pipeline");
    }
}
