#ifndef CUSTOMCONTAINER_H
#define CUSTOMCONTAINER_H

#include "CustomFileItem.h"

#include <QWidget>
#include <QList>

class CustomContainer : public QWidget
{
    Q_OBJECT
public:
    explicit CustomContainer(QWidget *parent = nullptr);

public:

signals:
    void removeEmited(CustomContainer*);

private:
    void paintEvent(QPaintEvent*) override;
    void contextMenuEvent(QContextMenuEvent*) override;

private slots:
    void AddNewFile();
    void OpenFile();
    void OpenFiles();
    void RemovePipeline();

private:
    int _buttonRadius;
    QWidget *contentWidget;
    QList<CustomFileItem*> _files;
};

#endif // CUSTOMCONTAINER_H
