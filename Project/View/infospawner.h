#ifndef INFOSPAWNER_H
#define INFOSPAWNER_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QPaintEvent>
#include <QPainter>
#include <QShowEvent>
#include <QHideEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QList>

class QPropertyAnimation;

class InfoSpawner : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int _widthOFFSET READ GetWidthOFFSET WRITE SetWidthOFFSET)
    Q_PROPERTY(int _heightOFFSET READ GetHeightOFFSET WRITE SetHeightOFFSET)
    Q_PROPERTY(int _opacityOFFSET READ GetOpacityOFFSET WRITE SetOpacityOFFSET)
public:
    InfoSpawner(QWidget *parent = nullptr);
    ~InfoSpawner();

public:
    enum class SpawnerType
    {
        LEFT,
        TOP,
        BOTTOM,
        TOPRIGHT
    };

    void AddText(QString, bool isBold = false, bool isItalic = false);
    void SetType(SpawnerType);

protected:
    virtual void paintEvent(QPaintEvent*) override;
    virtual void showEvent(QShowEvent*) override;
    virtual void hideEvent(QHideEvent*) override;

private:
    void SetWidthOFFSET(int);
    void SetHeightOFFSET(int);
    void SetOpacityOFFSET(int);

    int GetWidthOFFSET();
    int GetHeightOFFSET();
    int GetOpacityOFFSET();

private:
    SpawnerType _type;

    QPropertyAnimation *_widthAnimation;
    QPropertyAnimation *_heightAnimation;
    QPropertyAnimation *_opacityAnimation;

    int _widthOFFSET;
    int _heightOFFSET;
    int _opacityOFFSET;

    QList<QLabel*> _labels;
};

#endif // INFOSPAWNER_H
