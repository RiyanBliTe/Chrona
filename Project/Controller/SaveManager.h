#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QString>
#include <QFile>

class SaveManager final
{
private:
    SaveManager();
    ~SaveManager();
    SaveManager(const SaveManager&) = delete;
    SaveManager& operator=(const SaveManager&) = delete;

public:
    static SaveManager& Instance();

    void Initialize();
    void Save();

private:
    QFile *_TaskListFile;
};

#define SAVE_MANAGER SaveManager::Instance()

#endif // SAVEMANAGER_H
