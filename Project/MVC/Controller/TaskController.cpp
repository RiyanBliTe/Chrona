#include "TaskController.h"
#include "PipelineController.h"
#include "../../Window/ProgramWindow.h"
#include <QDebug>

TaskController::TaskController(QObject *parent)
    : QObject{parent}
{
    qDebug() << "[CREATED]" << this;
}

TaskController::~TaskController()
{
    qDebug() << "[DELETED]" << this;
}

TaskController& TaskController::Instance()
{
    static TaskController instance;
    return instance;
}

std::pair<Task*, TaskButton*> TaskController::LoadTask(QDomElement &element)
{
    // attributes
    Task *task = new Task;
    task->SetName(element.attribute("Name", ""));
    task->SetID(element.attribute("ID", ""));

    // task button
    TaskButton *taskButton = new TaskButton;
    taskButton->SetText(task->GetName());
    taskButton->SetTask(task);
    static bool isFirst = true;
    if (isFirst)
    {
        taskButton->SetFocused(true);
        isFirst = false;
    }
    connect(taskButton, &TaskButton::clicked, this, &TaskController::TaskButtonClicked);
    ProgramWindow::Instance().GenerateTaskConstructor(taskButton);

    QDomElement pipelineElement = element.firstChild().toElement();
    while (!pipelineElement.isNull())
    {
        std::pair<Pipeline*, PipelineContainer*> pair = PipelineController::Instance().LoadPipeline(pipelineElement);
        task->AddPipeline(pair.first);
        ProgramWindow::Instance().AddPipelineByIndex(pair.second, taskButton->GetStackedIndex());
        pipelineElement = pipelineElement.nextSibling().toElement();
    }

    this->_tasks.append(std::make_pair(task, taskButton));
    return std::make_pair(task, taskButton);
}

TaskButton* TaskController::AddTask(Task *task)
{
    TaskButton *taskButton = new TaskButton;
    taskButton->SetText(task->GetName());
    taskButton->SetTask(task);
    for (auto it = this->_tasks.begin(); it != this->_tasks.end(); it++)
    {
        it->second->SetFocused(false);
    }
    taskButton->SetFocused(true);
    connect(taskButton, &TaskButton::clicked, this, &TaskController::TaskButtonClicked);

    ProgramWindow::Instance().SetActiveTaskViewWidget(taskButton->GetStackedIndex());

    this->_tasks.append(std::make_pair(task, taskButton));
    return taskButton;
}

TaskButton* TaskController::GetActiveTaskButton()
{
    for (auto it = this->_tasks.begin(); it != this->_tasks.end(); it++)
    {
        if (it->second->IsFocused())
        {
            return it->second;
        }
    }

    return nullptr;
}

void TaskController::TaskButtonClicked(TaskButton *button)
{
    for (auto it = this->_tasks.begin(); it != this->_tasks.end(); it++)
    {
        if (it->second != button)
        {
            it->second->SetFocused(false);
        }
        else
        {
            ProgramWindow::Instance().SetActiveTaskViewWidget(it->second->GetStackedIndex());
        }
    }
}

void TaskController::AddPipelineToActiveTask(Pipeline *pipeline)
{
    for (auto it = this->_tasks.begin(); it != this->_tasks.end(); it++)
    {
        if (it->second->IsFocused())
        {
            it->first->AddPipeline(pipeline);
        }
    }
}

void TaskController::RemovePipeline(Pipeline *pipeline)
{
    for (auto it = this->_tasks.begin(); it != this->_tasks.end(); it++)
    {
        if (it->first->HasPipeline(pipeline))
        {
            it->first->RemovePipeline(pipeline);
        }
    }
}
