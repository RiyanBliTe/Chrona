#include "Computer.h"

Computer::Computer()
    : _name("")
    , _ip("")
    , _isThisComputer(false)
{

}

Computer::~Computer()
{
    for (auto it = this->_tasks.begin(); it != this->_tasks.end(); it++)
    {
        if (*it != nullptr)
        {
            delete *it;
        }
    }
    this->_tasks.clear();
}

void Computer::SetName(QString value)
{
    this->_name = value;
}

void Computer::SetIP(QString value)
{
    this->_ip = value;
}

void Computer::AddTask(Task *task)
{
    this->_tasks.append(task);
}

const QString& Computer::GetName()
{
    return this->_name;
}

const QString& Computer::GetIP()
{
    return this->_ip;
}

QList<Task*>& Computer::GetTasks()
{
    return this->_tasks;
}

void Computer::SetIsThisComputer(bool value)
{
    this->_isThisComputer = value;
}

bool Computer::IsThisComputer()
{
    return this->_isThisComputer;
}
