#include "StartupManager.h"
#include <QDebug>
#include "../../Controller/TaskController.h"
#include "../../Controller/Manager/SaveManager.h"
#include "../../../Window/ProgramWindow.h"

StartupManager::StartupManager(QObject *parent)
    : QObject{parent}
{

}

StartupManager::~StartupManager()
{

}

StartupManager& StartupManager::Instance()
{
    static StartupManager instance;
    return instance;
}

void StartupManager::Deploy(Task* task)
{
    CustomTimer *timer = new CustomTimer;
    timer->SetTrigerDateTime(task->GetStartDateTime());
    this->_deployedTasks.append(std::make_pair(timer, task));
    task->SetStatus(Task::TaskStatus::STARTWAIT);
    ProgramWindow::Instance().ChangeStatus(TaskController::Instance().GetTaskButtonByTask(task));
    TaskController::Instance().Update();
    QList<std::pair<Starter*, Pipeline*>> list;
    for (auto it = task->GetPipelines().begin(); it != task->GetPipelines().end(); it++)
    {
        list.append(std::make_pair(new Starter, *it));
    }
    this->_startList.append(std::make_pair(task, list));
    connect(timer, &CustomTimer::finishTriger, this, &StartupManager::CatchTimerFinish);
    timer->Start();
}

void StartupManager::CatchTimerFinish(CustomTimer *timer)
{
    // find task
    Task *task = nullptr;
    for (auto it = this->_deployedTasks.begin(); it != this->_deployedTasks.end(); it++)
    {
        if (it->first == timer)
        {
            task = it->second;
            break;
        }
    }

    // find task pipelines
    QList<std::pair<Starter*, Pipeline*>> *list = nullptr;
    for (auto it = this->_startList.begin(); it != this->_startList.end(); it++)
    {
        if (task != nullptr && it->first == task)
        {
            list = &it->second;
            break;
        }
    }

    // start pipelines
    if (list != nullptr && !list->isEmpty())
    {
        for (auto it = list->begin(); it != list->end(); it++)
        {
            Starter *starter = it->first;
            Pipeline *pipeline = it->second;

            task->SetStatus(Task::TaskStatus::RUNNING);
            ProgramWindow::Instance().ChangeStatus(TaskController::Instance().GetTaskButtonByTask(task));
            TaskController::Instance().Update();
            starter->SetTask(task);
            starter->SetPipeline(pipeline);
            connect(starter, &Starter::workFinished, this, &StartupManager::CatchStarterWorkFinished);
            starter->Start();
        }
    }
}

void StartupManager::CatchStarterWorkFinished(Starter *starter)
{
    for (auto it = this->_startList.begin(); it != this->_startList.end(); it++)
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            if (it2->first == starter)
            {
                delete starter;
                it2->first = nullptr;

                bool hasObject = false;
                it->first->SetStatus(Task::TaskStatus::SUCCESS);
                ProgramWindow::Instance().ChangeStatus(TaskController::Instance().GetTaskButtonByTask(it->first));
                for (auto it3 = it->second.begin(); it3 != it->second.end(); it3++)
                {
                    if (it3->first != nullptr)
                    {
                        hasObject = true;
                    }
                    if (!it3->second->IsFinished())
                    {
                        it->first->SetStatus(Task::TaskStatus::FAILED);
                        ProgramWindow::Instance().ChangeStatus(TaskController::Instance().GetTaskButtonByTask(it->first));
                    }
                }
                if (!hasObject)
                {
                    ProgramWindow::Instance().ShowSystemTrayMessage("Task: " + it->first->GetName(),
                                                                    "Finished. Result: " + (it->first->GetStatus() == Task::TaskStatus::FAILED ? QString("FAILED") : QString("SUCCESS")),
                                                                    it->first->GetStatus() == Task::TaskStatus::FAILED ? false : true);

                    for (auto removeTaskIterator = this->_deployedTasks.begin(); removeTaskIterator != this->_deployedTasks.end(); removeTaskIterator++)
                    {
                        if (removeTaskIterator->second == it->first)
                        {
                            this->_deployedTasks.erase(removeTaskIterator);
                            break;
                        }
                    }
                    it->second.clear();
                    this->_startList.erase(it);
                    TaskController::Instance().Update();
                    SaveManager::Instance().Save();
                }
                return;
            }
        }
    }
}
