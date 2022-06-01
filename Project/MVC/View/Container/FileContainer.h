#ifndef FILECONTAINER_H
#define FILECONTAINER_H

#include "../../Model/CustomFile.h"

#include <QWidget>

class FileContainer : public QWidget
{
    Q_OBJECT
public:
    explicit FileContainer(QWidget *parent = nullptr);
    ~FileContainer();

public:
    void GenerateImage(QString);

    void SetCustomFile(CustomFile*);
    CustomFile* GetCustomFile();

private:
    void paintEvent(QPaintEvent*) override;
    void mouseDoubleClickEvent(QMouseEvent*) override;

private:
    QImage _image;

    CustomFile *_file;
};

#endif // FILECONTAINER_H
