#ifndef CNOCKBUTTON_H
#define CNOCKBUTTON_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class CnockButton : public QWidget
{
    Q_OBJECT
public:
    explicit CnockButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;
};

#endif // CNOCKBUTTON_H
