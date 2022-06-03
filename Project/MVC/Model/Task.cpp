#include "Task.h"
#include <QDebug>

Task::Task(QObject *parent)
    : QObject{parent}
    , _id("")
    , _name("")
    , _status(Task::TaskStatus::IDLE)
{}

Task::~Task()
{
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

void Task::SetStartDateTime(QDateTime dateTime)
{
    this->_startDateTime = dateTime;
}

void Task::SetStatus(TaskStatus status)
{
    this->_status = status;

    if (!this->_history.isEmpty())
    {
        for (auto it = this->_history.begin(); it != this->_history.end(); it++)
        {
            if (it->first)
            {
                if (status == Task::TaskStatus::IDLE)
                {
                    it->second->indicatorLabel = "Idle";
                }
                else if (status == Task::TaskStatus::STARTWAIT)
                {
                    it->second->indicatorLabel = "Wait";
                }
                else if (status == Task::TaskStatus::RUNNING)
                {
                    it->second->indicatorLabel = "Working";
                }
                else if (status == Task::TaskStatus::SUCCESS)
                {
                    it->second->indicatorLabel = "Success";
                }
                else if (status == Task::TaskStatus::FAILED)
                {
                    it->second->indicatorLabel = "Failed";
                }
            }
        }
    }
}

void Task::AddHistoryLine(Task::StatisticLineData* value, bool active)
{
    if (!active)
        this->_history.prepend(std::make_pair(active, value));
    else
    {
        for (auto it = this->_history.begin(); it != this->_history.end(); it++)
        {
            it->first = false;
        }
        this->_history.prepend(std::make_pair(active, value));
    }
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

QDateTime& Task::GetStartDateTime()
{
    return this->_startDateTime;
}

Task::TaskStatus Task::GetStatus()
{
    return this->_status;
}

QList<std::pair<bool, Task::StatisticLineData*>>& Task::GetHistoryLine()
{
    return this->_history;
}

Task::StatisticLineData* Task::GetTopHistory()
{
    if (!this->_history.isEmpty())
    {
        for (auto it = this->_history.begin(); it != this->_history.end(); it++)
        {
            if (it->first)
                return it->second;
        }
    }

    return nullptr;
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

void Task::Reset()
{
    this->_status = Task::TaskStatus::IDLE;
}
