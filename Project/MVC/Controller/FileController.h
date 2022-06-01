#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include "../Model/CustomFile.h"
#include "../View/Container/FileContainer.h"

#include <QObject>
#include <QDomDocument>
#include <QDomElement>

class FileController : public QObject
{
    Q_OBJECT
public:
    static FileController& Instance();

    std::pair<CustomFile*, FileContainer*> LoadFile(QDomElement&);
    std::pair<CustomFile*, FileContainer*> CreateNewFile();
    CustomFile* GetFileByView(FileContainer*);

private:
    explicit FileController(QObject *parent = nullptr);
    FileController(const FileController&) = delete;
    FileController& operator=(const FileController&) = delete;
    ~FileController();

private:
    QList<std::pair<CustomFile*, FileContainer*>> _files;
};

#endif // FILECONTROLLER_H
