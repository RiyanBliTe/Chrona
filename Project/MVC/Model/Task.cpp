#include "Task.h"

Task::Task(QObject *parent)
    : QObject{parent}
    , _id("")
    , _name("")
{}

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
