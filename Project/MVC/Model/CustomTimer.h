#ifndef CUSTOMTIMER_H
#define CUSTOMTIMER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

class CustomTimer : public QObject
{
    Q_OBJECT
public:
    explicit CustomTimer(QObject *parent = nullptr);
    ~CustomTimer();

public:
    void SetTrigerDateTime(QDateTime);
    void Start();

signals:
    void finishTriger(CustomTimer*);

private:
    void ChekDateTimeValid();

private:
    QTimer *_timer;
    QDateTime _dateTime;
};

#endif // CUSTOMTIMER_H
