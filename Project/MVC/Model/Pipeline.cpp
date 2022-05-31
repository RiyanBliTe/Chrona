#include "Pipeline.h"

Pipeline::Pipeline(QObject *parent)
    : QObject{parent}
{

}

void Pipeline::AddFile(CustomFile *file)
{
    this->_files.append(file);
}

QList<CustomFile*>& Pipeline::GetFiles()
{
    return this->_files;
}
