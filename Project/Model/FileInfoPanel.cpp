#include "FileInfoPanel.h"

FileInfoPanel::FileInfoPanel(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(200, 400);
}

void FileInfoPanel::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QColor("#fff"));
    painter.drawRoundedRect(rect(), 4, 4);
}
