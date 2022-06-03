#ifndef STARTUPMANAGER_H
#define STARTUPMANAGER_H

#include "../../Model/Task.h"
#include "../../Model/CustomTimer.h"
#include "../../Model/Starter.h"

#include <QObject>

class StartupManager : public QObject
{
    Q_OBJECT
public:
    static StartupManager& Instance();

    void Deploy(Task*);

private:
    explicit StartupManager(QObject *parent = nullptr);
    StartupManager(const StartupManager&) = delete;
    StartupManager& operator=(const StartupManager&) = delete;
    ~StartupManager();

private slots:
    void CatchTimerFinish(CustomTimer*);
    void CatchStarterWorkFinished(Starter*);

private:
    QList<std::pair<CustomTimer*, Task*>> _deployedTasks;
    QList<std::pair<Task*, QList<std::pair<Starter*, Pipeline*>>>> _startList;
};

#endif // STARTUPMANAGER_H
