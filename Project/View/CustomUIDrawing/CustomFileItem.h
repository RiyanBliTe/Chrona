#ifndef CUSTOMFILEITEM_H
#define CUSTOMFILEITEM_H

#include <QWidget>
#include <QImage>

class CustomFileItem : public QWidget
{
    Q_OBJECT
public:
    explicit CustomFileItem(QWidget *parent = nullptr);

public:
    void GenerateImage(QString);

private:
    void paintEvent(QPaintEvent*) override;
    void mouseDoubleClickEvent(QMouseEvent*) override;

private:
    QImage _image;
};

#endif // CUSTOMFILEITEM_H
