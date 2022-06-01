#include "Pipeline.h"
#include <QDebug>

Pipeline::Pipeline(QObject *parent)
    : QObject{parent}
{
    qDebug() << "[CREATED]" << this;
}

Pipeline::~Pipeline()
{
    qDebug() << "[DELETED]" << this;
    for (auto it = this->_files.begin(); it != this->_files.end(); it++)
    {
        delete *it;
    }
}

void Pipeline::AddFile(CustomFile *file)
{
    this->_files.append(file);
}

QList<CustomFile*>& Pipeline::GetFiles()
{
    return this->_files;
}
