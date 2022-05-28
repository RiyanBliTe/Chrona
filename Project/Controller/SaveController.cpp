#include "SaveController.h"
#include "ComputersController.h"
#include "NetworkController.h"

SaveController::SaveController()
{

}

SaveController::~SaveController()
{

}

SaveController &SaveController::Instance()
{
    static SaveController instance;
    return instance;
}

void SaveController::LoadProgramData()
{
    QFile taskListFile("Data/TaskList.xml");

    if (!QFileInfo::exists("Data"))
    {
        QDir dir;
        dir.mkdir("Data");
    }
    QDomDocument document;
    taskListFile.open(QIODevice::ReadWrite | QFile::Text);
    if (!QFileInfo::exists("Data/TaskList.xml"))
    {
        taskListFile.write("");
    }

    document.setContent(&taskListFile);
    taskListFile.close();




    if (document.documentElement().tagName() == "Computers")
    {
        QDomElement element = document.documentElement().firstChild().toElement();

        while (!element.isNull())
        {
            if (element.tagName() == "Computer")
            {
                ComputersController::Instance().LoadComputer(element);
            }
            element = element.nextSibling().toElement();
        }
    }




    ComputersController::Instance().CheckValidInfo();
}

void SaveController::Save()
{
    QFile taskListFile("Data/TaskList.xml");

    if (!QFileInfo::exists("Data"))
    {
        QDir dir;
        dir.mkdir("Data");
    }
    taskListFile.open(QFile::WriteOnly | QFile::Text);
    if (!QFileInfo::exists("Data/TaskList.xml"))
    {
        taskListFile.write("");
    }

    QTextStream xmlContent(&taskListFile);
    QDomDocument document;
    QDomElement computersRoot = document.createElement("Computers");
    document.appendChild(computersRoot);

    const QList<std::pair<Computer*, QList<std::pair<Task*, TaskButton*>>*>> *computers = ComputersController::Instance().GetTasks();
    for (auto computerIterator = computers->begin(); computerIterator != computers->end(); computerIterator++)
    {
        QDomElement computerElement = document.createElement("Computer");
        computerElement.setAttribute("Name", computerIterator->first->GetName());
        computerElement.setAttribute("IP", computerIterator->first->GetIP());
        computerElement.setAttribute("MAC", computerIterator->first->GetMAC());
        computerElement.setAttribute("UniqueID", computerIterator->first->GetUniqueID());
        const QList<std::pair<Task*, TaskButton*>> *tasks = computerIterator->second;
        for (auto taskIterator = tasks->begin(); taskIterator != tasks->end(); taskIterator++)
        {
            QDomElement taskElement = document.createElement("Task");
            taskElement.setAttribute("ID", taskIterator->first->GetID());
            taskElement.setAttribute("Name", taskIterator->first->GetName());
            computerElement.appendChild(taskElement);
        }
        computersRoot.appendChild(computerElement);
    }

    xmlContent << document.toString();
    taskListFile.close();
}
