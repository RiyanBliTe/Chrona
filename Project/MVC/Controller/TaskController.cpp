#include "TaskController.h"
#include "PipelineController.h"
#include "../../Window/ProgramWindow.h"
#include <QDebug>

TaskController::TaskController(QObject *parent)
    : QObject{parent}
{}

TaskController::~TaskController()
{}

TaskController& TaskController::Instance()
{
    static TaskController instance;
    return instance;
}

void TaskController::Update()
{
    for (auto it = this->_tasks.begin(); it != this->_tasks.end(); it++)
    {
        it->second->SetStatus(it->first->GetStatus());
        it->second->update();
    }
}

TaskButton* TaskController::GetTaskButtonByTask(Task *task)
{
    for (auto it = this->_tasks.begin(); it != this->_tasks.end(); it++)
    {
        if (it->first == task)
            return it->second;
    }
}

QList<std::pair<Task*, TaskButton*>> &TaskController::GetTaskList()
{
    return this->_tasks;
}

std::pair<Task*, TaskButton*> TaskController::LoadTask(QDomElement &element)
{
    // attributes
    Task *task = new Task;
    task->SetName(element.attribute("Name", ""));
    task->SetID(element.attribute("ID", ""));
    bool runStat = element.attribute("RunStatus", 0).toInt();
    task->SetStatus(!runStat ? Task::TaskStatus::FAILED : Task::TaskStatus::SUCCESS);

    // task button
    TaskButton *taskButton = new TaskButton;
    taskButton->SetText(task->GetName());
    taskButton->SetTask(task);
    taskButton->SetStatus(task->GetStatus());
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
        if (pipelineElement.tagName() == "Pipeline")
        {
            std::pair<Pipeline*, PipelineContainer*> pair = PipelineController::Instance().LoadPipeline(pipelineElement);
            task->AddPipeline(pair.first);
            ProgramWindow::Instance().AddPipelineByIndex(pair.second, taskButton->GetStackedIndex());
            pipelineElement = pipelineElement.nextSibling().toElement();
        }
        else if (pipelineElement.tagName() == "HistoryResult")
        {
            Task::StatisticLineData* data = new Task::StatisticLineData;
            data->who_launched = pipelineElement.attribute("LaunchedBy", "");
            data->indicatorLabel = pipelineElement.attribute("Status", "Success");
            data->who_created = pipelineElement.attribute("Creator", "");
            data->post_time = pipelineElement.attribute("DelpoyTime", "");
            data->start_time = pipelineElement.attribute("StartTime", "");
            task->AddHistoryLine(data);
            //ProgramWindow::Instance().AddHistoryToTaskButton(taskButton, data);
            pipelineElement = pipelineElement.nextSibling().toElement();
        }
    }

    this->_tasks.append(std::make_pair(task, taskButton));
    return std::make_pair(task, taskButton);
}

void TaskController::AfterLoad()
{
    for (auto it = this->_tasks.begin(); it != this->_tasks.end(); it++)
    {
        for (auto it2 = it->first->GetHistoryLine().cbegin(); it2 != it->first->GetHistoryLine().cend(); it2++)
        {
            ProgramWindow::Instance().AddHistoryToTaskButton(it->second, it2->second);
        }
    }
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
