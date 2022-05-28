#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QFileDialog>
#include <QResizeEvent>
#include "CustomGraphicsScene.h"

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    CustomGraphicsView(QWidget *parent = nullptr);

public:
    CustomGraphicsScene* GetTaskConstructorScene();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void CreateNewFile();
    void OpenFile();

private:
    CustomGraphicsScene *_CustomGraphicsScene;
    QPoint _createdFilePosition;
    //FileInfoPanel *_FileInfoPanel;
    //CnockButton *_CnockButton;
};

#endif // CUSTOMGRAPHICSVIEW_H
