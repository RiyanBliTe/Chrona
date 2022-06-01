#include "SaveManager.h"
#include "../ComputerController.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDomDocument>
#include <QDebug>

SaveManager::SaveManager(QObject *parent)
    : QObject{parent}
{
    qDebug() << "[CREATED]" << this;
}

SaveManager::~SaveManager()
{
    qDebug() << "[DELETED]" << this;
}

SaveManager& SaveManager::Instance()
{
    static SaveManager instance;
    return instance;
}

void SaveManager::LoadProgramData()
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
        taskListFile.write("");

    document.setContent(&taskListFile);
    taskListFile.close();

    if (document.documentElement().tagName() == "Computers")
    {
        QDomElement element = document.documentElement().firstChild().toElement();

        while (!element.isNull())
        {
            if (element.tagName() == "Computer")
            {
                ComputerController::Instance().LoadComputer(element);
            }
            element = element.nextSibling().toElement();
        }
    }

    if (!ComputerController::Instance().IsValid())
    {
        Save();
        ComputerController::Instance().Clean();
        LoadProgramData();
    }
}

void SaveManager::Save()
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

    const QList<std::pair<Computer*, ComputerButton*>> &computers = ComputerController::Instance().GetComputers();
    for (auto computerIterator = computers.begin(); computerIterator != computers.end(); computerIterator++)
    {
        QDomElement computerElement = document.createElement("Computer");
        computerElement.setAttribute("Name", computerIterator->first->GetName());
        computerElement.setAttribute("IP", computerIterator->first->GetIP());
        computerElement.setAttribute("MAC", computerIterator->first->GetMAC());
        computerElement.setAttribute("UniqueID", computerIterator->first->GetUniqueID());

        const QList<Task*> &tasks = computerIterator->first->GetTasks();
        for (auto taskIterator = tasks.begin(); taskIterator != tasks.end(); taskIterator++)
        {
            QDomElement taskElement = document.createElement("Task");
            taskElement.setAttribute("ID", (*taskIterator)->GetID());
            taskElement.setAttribute("Name", (*taskIterator)->GetName());

            const QList<Pipeline*> &pipelines = (*taskIterator)->GetPipelines();
            for (auto pipelineIterator = pipelines.begin(); pipelineIterator != pipelines.end(); pipelineIterator++)
            {
                QDomElement pipelineElement = document.createElement("Pipeline");

                const QList<CustomFile*> &files = (*pipelineIterator)->GetFiles();
                for (auto fileIterator = files.begin(); fileIterator != files.end(); fileIterator++)
                {
                    QDomElement fileElement = document.createElement("File");
                    fileElement.setAttribute("Name", (*fileIterator)->GetName());
                    fileElement.setAttribute("Path", (*fileIterator)->GetPath());
                    fileElement.setAttribute("PreRun", (*fileIterator)->GetPreRunArguments());
                    fileElement.setAttribute("Run", (*fileIterator)->GetRunArguments());
                    fileElement.setAttribute("Type", (*fileIterator)->GetIndexType());

                    pipelineElement.appendChild(fileElement);
                }
                taskElement.appendChild(pipelineElement);
            }
            computerElement.appendChild(taskElement);
        }
        computersRoot.appendChild(computerElement);
    }

    xmlContent << document.toString();
    taskListFile.close();
}

