#ifndef FILEINFOPOPUP_H
#define FILEINFOPOPUP_H

#include "Popup.h"

#include "../../Model/CustomFile.h"
#include "../Button/SectionButton.h"

#include <QLineEdit>
#include <QComboBox>

class FileInfoPopup : public Popup
{
    Q_OBJECT
public:
    FileInfoPopup(QWidget *parent = nullptr, CustomFile *_file = nullptr);
    ~FileInfoPopup();

private slots:
    void CancelClicked();
    void SaveClicked();
    void BrowseClicked();

    void SetMemory();
    void SetupModules();

private:
    QLineEdit *_filename;
    QLineEdit *_filePath;
    QLineEdit *_preRunArguments;
    QLineEdit *_runArguments;
    SectionButton *_runCodition;

    QPushButton *_browse;
    QPushButton *_save;
    QPushButton *_cancel;

    CustomFile *_file;
};

#endif // FILEINFOPOPUP_H
