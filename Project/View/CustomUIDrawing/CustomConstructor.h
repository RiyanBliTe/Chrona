#ifndef CUSTOMCONSTRUCTOR_H
#define CUSTOMCONSTRUCTOR_H

#include <QWidget>
#include <QList>

#include "CustomContainer.h"

class CustomConstructor : public QWidget
{
    Q_OBJECT
public:
    explicit CustomConstructor(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent*) override;
    void contextMenuEvent(QContextMenuEvent*) override;

private slots:
    void AddNewPipeline();
    void RemoveContainer(CustomContainer*);

private:
    QList<CustomContainer*> _panels;
};

#endif // CUSTOMCONSTRUCTOR_H
