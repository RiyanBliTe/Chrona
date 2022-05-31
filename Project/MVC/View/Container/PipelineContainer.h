#ifndef PIPELINECONTAINER_H
#define PIPELINECONTAINER_H

#include "FileContainer.h"
#include "../../Model/Pipeline.h"

#include <QWidget>

class PipelineContainer : public QWidget
{
    Q_OBJECT
public:
    explicit PipelineContainer(QWidget *parent = nullptr);

public:
    void AddFile(FileContainer*);

    void SetPipeline(Pipeline*);
    Pipeline* GetPipeline();

signals:
    void removeEmited(PipelineContainer*);

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
    QList<FileContainer*> _files;
    Pipeline *_pipeline;
};

#endif // PIPELINECONTAINER_H
