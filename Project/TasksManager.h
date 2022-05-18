#ifndef TASKSMANAGER_H
#define TASKSMANAGER_H


class TasksManager final
{
private:
    TasksManager();
    ~TasksManager();
    TasksManager(const TasksManager&) = delete;
    TasksManager& operator=(const TasksManager&) = delete;

public:
    static TasksManager& Instance();
};

#define TASKS_MANAGER TasksManager::Instance()

#endif // TASKSMANAGER_H
