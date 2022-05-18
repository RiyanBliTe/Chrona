#ifndef COMPUTERSMANAGER_H
#define COMPUTERSMANAGER_H

#include <QDomDocument>

#include "Computer.h"

class ComputersManager final
{
private:
    ComputersManager();
    ~ComputersManager();
    ComputersManager(const ComputersManager&) = delete;
    ComputersManager& operator=(const ComputersManager&) = delete;

public:
    static ComputersManager& Instance();

    void LoadComputer(QDomElement& document);
    void LoadComputers();

    const QList<Task*> GetTasksByComputer(const Computer*);

private:
    QList<Computer*> _computers;
};

#define COMPUTERS_MANAGER ComputersManager::Instance()

#endif // COMPUTERSMANAGER_H
