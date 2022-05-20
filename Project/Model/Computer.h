#ifndef COMPUTER_H
#define COMPUTER_H

#include <QList>
#include "Task.h"

class Computer
{
public:
    Computer();
    ~Computer();

public:
    void SetName(QString);
    void SetIP(QString);
    void SetMAC(QString);
    void AddTask(Task*);

    QString& GetName();
    QString& GetIP();
    QString& GetMAC();
    QList<Task*>& GetTasks();

    void SetIsThisComputer(bool);
    bool IsThisComputer();

private:
    QString _name;
    QString _ip;
    QString _mac;
    QList<Task*> _tasks;

    bool _isThisComputer;
};

#endif // COMPUTER_H
