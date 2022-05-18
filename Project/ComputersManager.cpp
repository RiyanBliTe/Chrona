#include "ComputersManager.h"
#include "TasksManager.h"
#include "ConnectionManager.h"
#include "MainWindow.h"

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

    if (computer->GetIP() == CONNECTION_MANAGER.GetThisMachineIP())
    {
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
    MAINWINDOW.LoadComputers(this->_computers);
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
}
