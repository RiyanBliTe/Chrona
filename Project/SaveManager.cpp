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
        //this->_TaskListFile->close();
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
    this->_TaskListFile->open(QIODevice::ReadWrite);
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
                COMPUTERS_MANAGER.LoadComputer(element);
            }
            element = element.nextSibling().toElement();
        }
    }
    COMPUTERS_MANAGER.LoadComputers();
}

