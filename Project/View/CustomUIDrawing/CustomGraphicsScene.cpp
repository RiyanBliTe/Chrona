#include "CustomGraphicsScene.h"

CustomGraphicsScene::CustomGraphicsScene()
    : QGraphicsScene()
{
    _items = new QList<CustomGraphicsItem*>();
}

void CustomGraphicsScene::ItemFocusChanged(CustomGraphicsItem *item)
{
    for (auto it = this->_items->begin(); it != this->_items->end(); it++)
    {
        if (*it != item)
        {
            (*it)->SetFocused(false);
            (*it)->setZValue(-1);
        }
        else
        {
            (*it)->SetFocused(true);
            (*it)->setZValue(0);
        }
    }
}

void CustomGraphicsScene::AddNewItem(CustomGraphicsItem *item, QPoint position)
{
    for (auto it = this->_items->begin(); it != this->_items->end(); it++)
    {
        (*it)->SetFocused(false);
        (*it)->setZValue(-1);
    }
    addItem(item);
    this->_items->append(item);
    position.setX(position.x() - item->boundingRect().size().width() / 2);
    position.setY(position.y() - item->boundingRect().size().height() / 2);
    item->setPos(position);
    item->SetFocused(true);
    item->setZValue(1);
}
