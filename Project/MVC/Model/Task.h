#ifndef TASK_H
#define TASK_H

#include "Pipeline.h"

#include <QObject>
#include <QTime>

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = nullptr);
    ~Task();

public:
    void SetID(QString);
    void SetName(QString);
    void AddPipeline(Pipeline*);

    QString& GetID();
    QString& GetName();
    QList<Pipeline*>& GetPipelines();

    bool HasPipeline(Pipeline*);
    void RemovePipeline(Pipeline*);

private:
    QString _id;
    QString _name;

    QTime _launchTime;

    QList<Pipeline*> _pipelines;
};

#endif // TASK_H
