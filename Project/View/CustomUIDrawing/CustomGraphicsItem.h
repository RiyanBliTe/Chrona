#ifndef CUSTOMGRAPHICSITEM_H
#define CUSTOMGRAPHICSITEM_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QImage>

class CustomGraphicsItem : public QGraphicsPixmapItem
{
public:
    CustomGraphicsItem();

public:
    void SetFocused(bool);
    void GenerateImage(QString);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPixmap _mainImage;
    bool _isFocused;
};

#endif // CUSTOMGRAPHICSITEM_H
