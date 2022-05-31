#include "FileContainer.h"

#include <QPainter>

FileContainer::FileContainer(QWidget *parent)
    : QWidget{parent}
    , _image(":/Image/file_idle.png")
    , _file(nullptr)
{
    setFixedSize(_image.size());
}

void FileContainer::GenerateImage(QString value)
{
    if (value != "")
        value.prepend('.');
    else
    {
        return;
    }
    QImage image(":/Image/file_type.png");
    QImage resultImage(image.width(), image.height(), QImage::Format_ARGB32);
    resultImage.fill(Qt::transparent);
    QPainter painter(&resultImage);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::white);
    painter.drawImage(image.rect(), image);

    QFont font;
    int textWidth = 0;
    int textHeight = 0;
    int i = 0;
    do
    {
        font.setPointSize(14 - i);
        QFontMetrics fontMetrix(font);
        textWidth = fontMetrix.horizontalAdvance(value);
        textHeight = fontMetrix.height();
        i++;
    } while(textWidth > 34);
    painter.setFont(font);
    painter.drawText(QPoint(26 - textWidth / 2, 72 + textHeight / 2), value);
    this->_image = resultImage;
}

void FileContainer::SetCustomFile(CustomFile *file)
{
    this->_file = file;
}

CustomFile* FileContainer::GetCustomFile()
{
    return this->_file;
}

void FileContainer::mouseDoubleClickEvent(QMouseEvent*)
{
    /*ProgramWindow::Instance().GetPopupController();
    ProgramWindow::Instance().GetPopupController()->setGeometry(0, 0, ProgramWindow::Instance().width(), ProgramWindow::Instance().height());
    ProgramWindow::Instance().GetPopupController()->raise();
    ProgramWindow::Instance().GetPopupController()->SetActiveFileInfo("file 1", "file path", "pre attr", "attr", 1);
    ProgramWindow::Instance().GetPopupController()->PushPopup(PopupController::PopupType::FILEINFO);
    /*Popup *popup = this->_PopupModule->TopPopup();
    if (popup != nullptr)
    {
        connect(popup, &AddTaskPopup::addTask, this, &ProgramWindow::AddTaskTriger);
    }
    ProgramWindow::Instance().GetPopupController()->show();*/
}

void FileContainer::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawImage(0, 0, this->_image);
}
