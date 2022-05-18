#include "TasksManager.h"

TasksManager::TasksManager()
{

}

TasksManager::~TasksManager()
{

}

TasksManager& TasksManager::Instance()
{
    static TasksManager instance;
    return instance;
}
