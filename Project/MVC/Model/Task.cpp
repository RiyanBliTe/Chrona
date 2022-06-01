#include "Task.h"
#include <QDebug>

Task::Task(QObject *parent)
    : QObject{parent}
    , _id("")
    , _name("")
{
    qDebug() << "[CREATED]" << this;
}

Task::~Task()
{
    qDebug() << "[DELETED]" << this;
    for (auto it = this->_pipelines.begin(); it != this->_pipelines.end(); it++)
    {
        delete *it;
    }
}

void Task::SetID(QString value)
{
    this->_id = value;
}

void Task::SetName(QString value)
{
    this->_name = value;
}

void Task::AddPipeline(Pipeline *pipeline)
{
    this->_pipelines.append(pipeline);
}

QString& Task::GetID()
{
    return this->_id;
}

QString& Task::GetName()
{
    return this->_name;
}

QList<Pipeline*>& Task::GetPipelines()
{
    return this->_pipelines;
}

bool Task::HasPipeline(Pipeline *pipeline)
{
    for (auto it = this->_pipelines.begin(); it != this->_pipelines.end(); it++)
    {
        if (*it == pipeline)
            return true;
    }
    return false;
}

void Task::RemovePipeline(Pipeline *pipeline)
{
    for (auto it = this->_pipelines.begin(); it != this->_pipelines.end(); it++)
    {
        if (*it == pipeline)
        {
            this->_pipelines.erase(it);
            delete pipeline;
            break;
        }
    }
}
