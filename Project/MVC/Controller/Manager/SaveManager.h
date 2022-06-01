#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QObject>

class SaveManager : public QObject
{
    Q_OBJECT
public:
    static SaveManager& Instance();

    void LoadProgramData();
    void Save();

private:
    explicit SaveManager(QObject *parent = nullptr);
    SaveManager(const SaveManager&) = delete;
    SaveManager& operator=(const SaveManager&) = delete;
    ~SaveManager();
};

#endif // SAVEMANAGER_H
