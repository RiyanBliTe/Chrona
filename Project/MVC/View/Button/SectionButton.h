#ifndef SECTIONBUTTON_H
#define SECTIONBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QList>
#include <QPropertyAnimation>
#include <math.h>

class QPropertyAnimation;

class SectionButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int _selectedOffset READ getSelectedOffset WRITE setSelectedOffset)
public:
    explicit SectionButton(QWidget *parent = nullptr);
    ~SectionButton();

    int createSection(QString, int position = -1);
    void setSelected(int);
    void setFontFamily(QString);
    int GetActiveSection();

protected:
    void paintEvent(QPaintEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void resizeEvent(QResizeEvent *event) override;

    int getSelectedOffset();
    void setSelectedOffset(int value);

signals:
    void selectionChanged(int id);

private:
    struct SectionItem
    {
        int id;
        int x;
        int y;
        int width;
        int height;
        QString text;
        bool isSelected;
    };

    QList<SectionItem> _sections;
    QPropertyAnimation* _animation;
    int _selectedOffset;
    int _activeSection;

    QString _fontFamily;
};

#endif // SECTIONBUTTON_H
