#include "ComputersManager.h"
#include "ConnectionManager.h"
#include "../View/MainWindow.h"

#include <QDebug>

ComputersManager::ComputersManager()
{

}

ComputersManager::~ComputersManager()
{
    for (auto it = this->_computers.begin(); it != this->_computers.end(); it++)
    {
        if (*it != nullptr)
        {
            delete *it;
        }
    }
    this->_computers.clear();
}

ComputersManager& ComputersManager::Instance()
{
    static ComputersManager instance;
    return instance;
}

void ComputersManager::LoadComputer(QDomElement& document)
{
    // attributes
    Computer *computer = new Computer();
    computer->SetName(document.attribute("Name", ""));
    computer->SetIP(document.attribute("IP", ""));
    computer->SetMAC(document.attribute("MAC", ""));

    if (computer->GetMAC() == ConnectionManager::Instance().GetThisMachineMAC())
    {
        computer->SetIP(ConnectionManager::Instance().GetThisMachineIP());
        computer->SetIsThisComputer(true);
    }

    // tasks
    QDomElement taskElement = document.firstChild().toElement();
    while (!taskElement.isNull())
    {
        if (taskElement.tagName() == "Task")
        {
            Task *task = new Task();
            task->SetID(taskElement.attribute("ID", ""));
            task->SetName(taskElement.attribute("Name", ""));
            computer->AddTask(task);
        }
        taskElement = taskElement.nextSibling().toElement();
    }

    this->_computers.append(computer);
}

void ComputersManager::LoadComputers()
{
    bool hasThisComputer = false;
    for (auto it = this->_computers.begin(); it != this->_computers.end(); it++)
    {
        if ((*it)->IsThisComputer())
        {
            hasThisComputer = true;
        }
    }
    if (!hasThisComputer)
    {
        Computer *thisComuter = new Computer();
        thisComuter->SetName(ConnectionManager::Instance().GetThisMachineName());
        thisComuter->SetIP(ConnectionManager::Instance().GetThisMachineIP());
        thisComuter->SetMAC(ConnectionManager::Instance().GetThisMachineMAC());
        thisComuter->SetIsThisComputer(true);
        this->_computers.prepend(thisComuter);
    }

    MainWindow::Instance().LoadComputers(this->_computers);
}

const QList<Task*> ComputersManager::GetTasksByComputer(const Computer *value)
{
    for (auto it = this->_computers.begin(); it != this->_computers.end(); it++)
    {
        if ((*it) == value)
        {
            return (*it)->GetTasks();
        }
    }
    return QList<Task*>();
}

const QList<Computer*>& ComputersManager::GetComputers()
{
    return this->_computers;
}

void ComputersManager::AddComputer(Computer *computer)
{
    this->_computers.append(computer);
}
