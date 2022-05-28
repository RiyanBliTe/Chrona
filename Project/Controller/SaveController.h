#ifndef SAVECONTROLLER_H
#define SAVECONTROLLER_H

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDomDocument>
#include <QTextStream>

class SaveController final
{
private:
    SaveController();
    ~SaveController();
    SaveController(const SaveController&) = delete;
    SaveController& operator=(const SaveController&) = delete;

public:
    static SaveController &Instance();

    void LoadProgramData();
    void Save();
};

#endif // SAVECONTROLLER_H
