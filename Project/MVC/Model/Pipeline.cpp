#include "Pipeline.h"

Pipeline::Pipeline(QObject *parent)
    : QObject{parent}
    , isFinished(true)
{}

Pipeline::~Pipeline()
{
    for (auto it = this->_files.begin(); it != this->_files.end(); it++)
    {
        delete *it;
    }
}

void Pipeline::AddFile(CustomFile *file)
{
    this->_files.append(file);
}

void Pipeline::SetFinished(bool value)
{
    this->isFinished = value;
}

QList<CustomFile*>& Pipeline::GetFiles()
{
    return this->_files;
}

bool Pipeline::IsFinished()
{
    return this->isFinished;
}

void Pipeline::Reset()
{
    this->isFinished = true;
}
