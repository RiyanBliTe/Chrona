#ifndef COMPUTER_H
#define COMPUTER_H

#include "Task.h"

#include <QObject>

class Computer : public QObject
{
    Q_OBJECT
public:
    explicit Computer(QObject *parent = nullptr);

public:
    void SetName(QString);
    void SetIP(QString);
    void SetMAC(QString);
    void SetUniqueID(QString);
    void SetIsThisComputer(bool);
    void AddTask(Task*);

    QString& GetName();
    QString& GetIP();
    QString& GetMAC();
    QString& GetUniqueID();
    QList<Task*>& GetTasks();
    bool IsThisComputer();

private:
    QString _name;
    QString _ip;
    QString _mac;
    QString _uniqueID;

    bool _isThisComputer;

    QList<Task*> _tasks;
};

#endif // COMPUTER_H
