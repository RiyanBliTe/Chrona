#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "CustomGraphicsItem.h"

class CustomGraphicsScene : public QGraphicsScene
{
public:
    CustomGraphicsScene();

public:
    void ItemFocusChanged(CustomGraphicsItem*);
    void AddNewItem(CustomGraphicsItem*, QPoint);

private:
    QList<CustomGraphicsItem*> *_items;
};

#endif // CUSTOMGRAPHICSSCENE_H
