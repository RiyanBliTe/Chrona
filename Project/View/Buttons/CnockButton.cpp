#include "CnockButton.h"

CnockButton::CnockButton(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(200, 40);
}

void CnockButton::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QColor("#fff"));
    painter.drawRoundedRect(rect(), 4, 4);
}
