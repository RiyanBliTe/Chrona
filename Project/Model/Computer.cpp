#include "Computer.h"

Computer::Computer()
    : _name("")
    , _ip("")
    , _mac("")
    , _isThisComputer(false)
{
    this->_tasks = new QList<Task*>();
}

Computer::~Computer()
{
    for (auto it = this->_tasks->begin(); it != this->_tasks->end(); it++)
    {
        if (*it != nullptr)
        {
            delete *it;
        }
    }
    this->_tasks->clear();
    delete this->_tasks;
}

void Computer::SetName(QString value)
{
    this->_name = value;
}

void Computer::SetIP(QString value)
{
    this->_ip = value;
}

void Computer::SetMAC(QString value)
{
    this->_mac = value;
}

void Computer::AddTask(Task *task)
{
    this->_tasks->append(task);
}

QString& Computer::GetName()
{
    return this->_name;
}

QString& Computer::GetIP()
{
    return this->_ip;
}

QString& Computer::GetMAC()
{
    return this->_mac;
}

const QList<Task*>* Computer::GetTasks()
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
