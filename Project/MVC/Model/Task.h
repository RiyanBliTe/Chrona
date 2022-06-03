#ifndef TASK_H
#define TASK_H

#include "Pipeline.h"

#include <QObject>
#include <QTime>
#include <QDateTime>

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = nullptr);
    ~Task();

public:
    enum class TaskStatus
    {
        IDLE,
        RUNNING,
        SUCCESS,
        FAILED,
        STARTWAIT
    };

    struct StatisticLineData
    {
        QString who_launched;
        QString indicatorLabel;
        QString who_created;
        QString post_time;
        QString start_time;
    };

    void SetID(QString);
    void SetName(QString);
    void AddPipeline(Pipeline*);
    void SetStartDateTime(QDateTime);
    void SetStatus(TaskStatus);
    void AddHistoryLine(StatisticLineData*, bool isActive = false);

    QString& GetID();
    QString& GetName();
    QList<Pipeline*>& GetPipelines();
    QDateTime& GetStartDateTime();
    TaskStatus GetStatus();
    QList<std::pair<bool, StatisticLineData*>>& GetHistoryLine();
    StatisticLineData* GetTopHistory();

    bool HasPipeline(Pipeline*);
    void RemovePipeline(Pipeline*);

    void Reset();

private:
    QString _id;
    QString _name;

    QTime _launchTime;

    QList<Pipeline*> _pipelines;
    QList<std::pair<bool, StatisticLineData*>> _history;

    QDateTime _startDateTime;

    TaskStatus _status;
};

#endif // TASK_H
