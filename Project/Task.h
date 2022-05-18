#ifndef TASK_H
#define TASK_H

#include <QString>

class Task
{
public:
    Task();

    void SetID(QString);
    void SetName(QString);

    const QString& GetID();
    const QString& GetName();

private:
    QString _id;
    QString _name;
};

#endif // TASK_H
