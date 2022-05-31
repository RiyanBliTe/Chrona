#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include "Container/PipelineContainer.h"

#include <QWidget>
#include <QList>

class Constructor : public QWidget
{
    Q_OBJECT
public:
    explicit Constructor(QWidget *parent = nullptr);

public:
    void AddPipeline(PipelineContainer*);

private:
    void paintEvent(QPaintEvent*) override;
    void contextMenuEvent(QContextMenuEvent*) override;

private slots:
    void AddNewPipeline();
    void RemovePipeline(PipelineContainer*);

private:
    QList<PipelineContainer*> _panels;
};

#endif // CONSTRUCTOR_H
