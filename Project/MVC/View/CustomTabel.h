#ifndef CUSTOMTABEL_H
#define CUSTOMTABEL_H

#include <QWidget>
#include <QLineEdit>
#include <QFrame>
#include <QLabel>

class CustomTabel : public QWidget
{
    Q_OBJECT
public:
    explicit CustomTabel(QWidget *parent = nullptr);

    void AddLine(QString, QString, QString, QString, QString);
    void ChangeStatusOnTop(QString);

private:
    void paintEvent(QPaintEvent*) override;

private:
    struct StatisticLine
    {
        QLabel *who_launched;
        QFrame *indicator;
        QLabel *indicatorLabel;
        QLabel *who_created;
        QLabel *post_time;
        QLabel *start_time;
    };

    QList<std::pair<int, StatisticLine*>> _lines;
    int _index;
};

#endif // CUSTOMTABEL_H
