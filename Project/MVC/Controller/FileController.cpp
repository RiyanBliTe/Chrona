#include "FileController.h"

#include <QFileInfo>

FileController::FileController(QObject *parent)
    : QObject{parent}
{

}

FileController& FileController::Instance()
{
    static FileController instance;
    return instance;
}

std::pair<CustomFile*, FileContainer*> FileController::LoadFile(QDomElement &element)
{
    // attrinbutes
    CustomFile *file = new CustomFile;
    file->SetName(element.attribute("Name", ""));
    file->SetPath(element.attribute("Path", ""));
    file->SetPreRunArguments(element.attribute("PreRun", ""));
    file->SetRunArguments(element.attribute("Run", ""));
    file->SetIndexType(std::atoi(element.attribute("Type", "0").toStdString().c_str()));

    // file widget
    FileContainer *container = new FileContainer;
    QFileInfo fileInfo(file->GetPath());
    container->GenerateImage(fileInfo.suffix());
    container->SetCustomFile(file);

    this->_files.append(std::make_pair(file, container));
    return std::make_pair(file, container);
}

std::pair<CustomFile*, FileContainer*> FileController::CreateNewFile()
{
    CustomFile *file = new CustomFile;
    FileContainer *container = new FileContainer;
    container->SetCustomFile(file);
    this->_files.append(std::make_pair(file, container));
    return std::make_pair(file, container);
}
