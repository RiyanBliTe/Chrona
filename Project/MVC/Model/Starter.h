#ifndef STARTER_H
#define STARTER_H

#include <QObject>
#include <QProcess>
#include <QTimer>
#include <QFile>
#include "Task.h"

class Starter : public QObject
{
    Q_OBJECT
public:
    explicit Starter(QObject *parent = nullptr);
    ~Starter();

    void SetPipeline(Pipeline*);
    void Start();
    void SetTask(Task*);

signals:
    void workFinished(Starter*);

private slots:
    void OnErrorOccured(QProcess::ProcessError);
    void OnStateChanged(QProcess::ProcessState);
    void OnFinished(int, QProcess::ExitStatus);
    void OnReadyReadStandardError();
    void OnReadyReadStandardOutput();

private:
    Pipeline *_Pipeline;
    QProcess *_mainProcess;
    int _fileIndex;
    bool _hasError;
    QTimer *_timer;
    Task *_task;

    QFile *_file;
};

#endif // STARTER_H
