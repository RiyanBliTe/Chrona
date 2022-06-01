#include "PipelineController.h"
#include "FileController.h"
#include <QDebug>

PipelineController::PipelineController(QObject *parent)
    : QObject{parent}
{
    qDebug() << "[CREATED]" << this;
}

PipelineController::~PipelineController()
{
    qDebug() << "[DELETED]" << this;
}

PipelineController& PipelineController::Instance()
{
    static PipelineController instance;
    return instance;
}

std::pair<Pipeline*, PipelineContainer*> PipelineController::LoadPipeline(QDomElement &element)
{
    // attributes
    Pipeline *pipeline = new Pipeline;

    // pipeline container
    PipelineContainer *pipelineContainer = new PipelineContainer;
    pipelineContainer->SetPipeline(pipeline);

    QDomElement fileElement = element.firstChild().toElement();
    while (!fileElement.isNull())
    {
        std::pair<CustomFile*, FileContainer*> pair = FileController::Instance().LoadFile(fileElement);
        pipeline->AddFile(pair.first);
        pipelineContainer->AddFile(pair.second);
        fileElement = fileElement.nextSibling().toElement();
    }

    this->_pipelines.append(std::make_pair(pipeline, pipelineContainer));
    return std::make_pair(pipeline, pipelineContainer);
}

std::pair<Pipeline*, PipelineContainer*> PipelineController::CreateNewPipeline()
{
    Pipeline *pipeline = new Pipeline;

    PipelineContainer *pipelineContainer = new PipelineContainer;
    pipelineContainer->SetPipeline(pipeline);

    this->_pipelines.append(std::make_pair(pipeline, pipelineContainer));
    return std::make_pair(pipeline, pipelineContainer);
}

void PipelineController::AddFileToPipeline(PipelineContainer *container, CustomFile *file)
{
    for (auto it = this->_pipelines.begin(); it != this->_pipelines.end(); it++)
    {
        if (it->second == container)
        {
            it->first->AddFile(file);
        }
    }
}

Pipeline* PipelineController::GetPipelineByView(PipelineContainer *view)
{
    for (auto it = this->_pipelines.begin(); it != this->_pipelines.end(); it++)
    {
        if (it->second == view)
        {
            return it->first;
        }
    }
    return nullptr;
}
