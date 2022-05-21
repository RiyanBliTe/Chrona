#ifndef COMPUTERSMANAGER_H
#define COMPUTERSMANAGER_H

#include <QDomDocument>

#include "../Model/Computer.h"

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

    const QList<Task*>* GetTasksByComputer(const Computer*);
    const QList<Computer*>& GetComputers();

    void AddComputer(Computer*);

private:
    QList<Computer*> _computers;
};

#endif // COMPUTERSMANAGER_H
