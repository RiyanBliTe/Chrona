#include "SaveManager.h"
#include "ComputersManager.h"

#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include <QDomDocument>

SaveManager::SaveManager()
    : _TaskListFile(nullptr)
{

}

SaveManager::~SaveManager()
{
    if (this->_TaskListFile != nullptr)
    {
        delete this->_TaskListFile;
    }
}

SaveManager& SaveManager::Instance()
{
    static SaveManager instance;
    return instance;
}

void SaveManager::Initialize()
{
    if (this->_TaskListFile == nullptr)
        this->_TaskListFile = new QFile("Data/TaskList.xml");

    if (!QFileInfo::exists("Data"))
    {
        QDir dir;
        dir.mkdir("Data");
    }
    this->_TaskListFile->open(QIODevice::ReadOnly | QFile::Text);
    if (!QFileInfo::exists("Data/TaskList.xml"))
    {
        this->_TaskListFile->write("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
    }

    QDomDocument document;
    document.setContent(this->_TaskListFile);
    this->_TaskListFile->close();

    if (document.documentElement().tagName() == "Computers")
    {
        QDomElement element = document.documentElement().firstChild().toElement();

        while (!element.isNull())
        {
            if (element.tagName() == "Computer")
            {
                ComputersManager::Instance().LoadComputer(element);
            }
            element = element.nextSibling().toElement();
        }
    }
    ComputersManager::Instance().LoadComputers();
}

void SaveManager::Save()
{
    if (this->_TaskListFile == nullptr)
        this->_TaskListFile = new QFile("Data/TaskList.xml");

    if (!QFileInfo::exists("Data"))
    {
        QDir dir;
        dir.mkdir("Data");
    }
    this->_TaskListFile->open(QFile::WriteOnly | QFile::Text);
    if (!QFileInfo::exists("Data/TaskList.xml"))
    {
        this->_TaskListFile->write("");
    }

    QTextStream xmlContent(this->_TaskListFile);
    QDomDocument document;
    QDomElement computersRoot = document.createElement("Computers");
    document.appendChild(computersRoot);

    for (auto computerIterator = ComputersManager::Instance().GetComputers().begin(); computerIterator != ComputersManager::Instance().GetComputers().end(); computerIterator++)
    {
        QDomElement computerElement = document.createElement("Computer");
        computerElement.setAttribute("Name", (*computerIterator)->GetName());
        computerElement.setAttribute("IP", (*computerIterator)->GetIP());
        computerElement.setAttribute("MAC", (*computerIterator)->GetMAC());
        for (auto taskIterator = (*computerIterator)->GetTasks()->begin(); taskIterator != (*computerIterator)->GetTasks()->end(); taskIterator++)
        {
            QDomElement taskElement = document.createElement("Task");
            taskElement.setAttribute("ID", (*taskIterator)->GetID());
            taskElement.setAttribute("Name", (*taskIterator)->GetName());
            computerElement.appendChild(taskElement);
        }
        computersRoot.appendChild(computerElement);
    }

    xmlContent << document.toString();
    this->_TaskListFile->close();
}
