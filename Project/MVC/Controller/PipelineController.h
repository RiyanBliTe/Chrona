#ifndef PIPELINECONTROLLER_H
#define PIPELINECONTROLLER_H

#include "../Model/Pipeline.h"
#include "../View/Container/PipelineContainer.h"

#include <QObject>
#include <QDomDocument>
#include <QDomElement>

class PipelineController : public QObject
{
    Q_OBJECT
public:
    static PipelineController& Instance();

    std::pair<Pipeline*, PipelineContainer*> LoadPipeline(QDomElement&);
    std::pair<Pipeline*, PipelineContainer*> CreateNewPipeline();
    void AddFileToPipeline(PipelineContainer*, CustomFile*);
    Pipeline* GetPipelineByView(PipelineContainer*);

private:
    explicit PipelineController(QObject *parent = nullptr);
    PipelineController(const PipelineController&) = delete;
    PipelineController& operator=(const PipelineController&) = delete;
    ~PipelineController();

private:
    QList<std::pair<Pipeline*, PipelineContainer*>> _pipelines;
};

#endif // PIPELINECONTROLLER_H
