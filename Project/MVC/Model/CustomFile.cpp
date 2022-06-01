#include "CustomFile.h"
#include <QDebug>

CustomFile::CustomFile(QObject *parent)
    : QObject{parent}
    , _name("")
    , _path("")
    , _preRunArguments("")
    , _runArguments("")
    , indexType(0)
{
    qDebug() << "[CREATED]" << this;
}

CustomFile::~CustomFile()
{
    qDebug() << "[DELETED]" << this;
}

void CustomFile::SetName(QString value)
{
    this->_name = value;
}

void CustomFile::SetPath(QString value)
{
    this->_path = value;
}

void CustomFile::SetPreRunArguments(QString value)
{
    this->_preRunArguments = value;
}

void CustomFile::SetRunArguments(QString value)
{
    this->_runArguments = value;
}

void CustomFile::SetIndexType(int value)
{
    this->indexType = value;
}

QString& CustomFile::GetName()
{
    return this->_name;
}

QString& CustomFile::GetPath()
{
    return this->_path;
}

QString& CustomFile::GetPreRunArguments()
{
    return this->_preRunArguments;
}

QString& CustomFile::GetRunArguments()
{
    return this->_runArguments;
}

int CustomFile::GetIndexType()
{
    return this->indexType;
}
