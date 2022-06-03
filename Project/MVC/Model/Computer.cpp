#include "Computer.h"

Computer::Computer(QObject *parent)
    : QObject{parent}
    , _name("")
    , _ip("")
    , _mac("")
    , _uniqueID("")
    , _isThisComputer(false)
{}

Computer::~Computer()
{
    for (auto it = this->_tasks.begin(); it != this->_tasks.end(); it++)
    {
        delete *it;
    }
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

void Computer::SetUniqueID(QString value)
{
    this->_uniqueID = value;
}

void Computer::SetIsThisComputer(bool value)
{
    this->_isThisComputer = value;
}

void Computer::AddTask(Task *task)
{
    this->_tasks.append(task);
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

QString& Computer::GetUniqueID()
{
    return this->_uniqueID;
}

bool Computer::IsThisComputer()
{
    return this->_isThisComputer;
}

QList<Task*>& Computer::GetTasks()
{
    return this->_tasks;
}
