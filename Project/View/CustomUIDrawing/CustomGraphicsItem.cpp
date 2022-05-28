#include "CustomGraphicsItem.h"
#include "../ProgramWindow.h"
#include <QGraphicsDropShadowEffect>

CustomGraphicsItem::CustomGraphicsItem()
    : QGraphicsPixmapItem()
    , _mainImage(":/images/Images/file_idle.png")
    , _isFocused(false)
{
    setFlag(QGraphicsItem::ItemIsMovable);
}

void CustomGraphicsItem::SetFocused(bool value)
{
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(6);
    effect->setOffset(0, 0);

    if (value)
    {
        effect->setColor(QColor(255, 255, 255));
    }
    else
    {
        effect->setColor(QColor(0, 0, 0));
    }
    setPixmap(this->_mainImage);
    setGraphicsEffect(effect);
}

void CustomGraphicsItem::GenerateImage(QString value)
{
    if (value != "")
        value.prepend('.');
    else
    {
        this->_mainImage = QPixmap(":/images/Images/file_idle.png");
        return;
    }
    QImage image(":/images/Images/file_type.png");
    QImage resultImage(image.width(), image.height(), QImage::Format_ARGB32);
    resultImage.fill(Qt::transparent);
    QPainter painter(&resultImage);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::white);
    painter.drawImage(image.rect(), image);

    QFont font;
    int textWidth = 0;
    int textHeight = 0;
    int i = 0;
    do
    {
        font.setPointSize(14 - i);
        QFontMetrics fontMetrix(font);
        textWidth = fontMetrix.horizontalAdvance(value);
        textHeight = fontMetrix.height();
        i++;
    } while(textWidth > 34);
    painter.setFont(font);
    painter.drawText(QPoint(26 - textWidth / 2, 72 + textHeight / 2), value);
    this->_mainImage = QPixmap::fromImage(resultImage);
}

void CustomGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mousePressEvent(event);
    ProgramWindow::Instance().GetConstructorGraphicsView()->GetTaskConstructorScene()->ItemFocusChanged(this);
}
