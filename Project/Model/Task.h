#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QTime>

class Task
{
public:
    Task();
    ~Task();

    void SetID(QString);
    void SetName(QString);

    QString& GetID();
    QString& GetName();

private:
    QString _id;
    QString _name;

    QString _preRunArguments;
    QString _afterRunArguments;
    QTime _launchTime;
};

#endif // TASK_H
