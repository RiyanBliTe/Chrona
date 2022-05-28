#ifndef FILEINFOPANEL_H
#define FILEINFOPANEL_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class FileInfoPanel : public QWidget
{
    Q_OBJECT
public:
    explicit FileInfoPanel(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;
};

#endif // FILEINFOPANEL_H
