#ifndef PIPELINE_H
#define PIPELINE_H

#include "CustomFile.h"

#include <QObject>

class Pipeline : public QObject
{
    Q_OBJECT
public:
    explicit Pipeline(QObject *parent = nullptr);
    ~Pipeline();

public:
    void AddFile(CustomFile*);
    void SetFinished(bool);

    QList<CustomFile*>& GetFiles();
    bool IsFinished();
    void Reset();

private:
    QList<CustomFile*> _files;
    bool isFinished;
};

#endif // PIPELINE_H
