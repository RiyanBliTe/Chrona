#ifndef FILEINFOPOPUP_H
#define FILEINFOPOPUP_H

#include "Popup.h"

#include <QLineEdit>
#include <QComboBox>

class FileInfoPopup : public Popup
{
    Q_OBJECT
public:
    FileInfoPopup(QWidget *parent = nullptr);

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
    QComboBox *_runCodition;

    QPushButton *_browse;
    QPushButton *_save;
    QPushButton *_cancel;
};

#endif // FILEINFOPOPUP_H
