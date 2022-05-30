#ifndef FILEINFOPOPUP_H
#define FILEINFOPOPUP_H

#include "Popup.h"

#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>

class FileInfoPopup : public Popup
{
public:
    FileInfoPopup(QWidget *parent = nullptr, QString file_name = "", QString file_path = "", QString preAttr = "", QString attr = "", int index = 0);
    ~FileInfoPopup();

private slots:
    void CancelClicked();
    void SaveClicked();
    void BrowseClicked();

private:
    struct FileInfo
    {
        QString file_name;
        QString file_path;
        QString preAttr;
        QString attr;
        int index;
    };

private:
    QLineEdit *_filename;
    QLineEdit *_filePath;
    QLineEdit *_preRunArguments;
    QLineEdit *_runArguments;
    QComboBox *_runCodition;

    QPushButton *_browse;
    QPushButton *_save;
    QPushButton *_cancel;

    FileInfo _fileInfo;
};

#endif // FILEINFOPOPUP_H
