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

    QList<CustomFile*>& GetFiles();

private:
    QList<CustomFile*> _files;
};

#endif // PIPELINE_H
