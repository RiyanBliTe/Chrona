#include "Task.h"

Task::Task()
    : _id("")
    , _name("")
{

}

void Task::SetID(QString value)
{
    this->_id = value;
}

void Task::SetName(QString value)
{
    this->_name = value;
}

const QString& Task::GetID()
{
    return this->_id;
}

const QString& Task::GetName()
{
    return this->_name;
}
