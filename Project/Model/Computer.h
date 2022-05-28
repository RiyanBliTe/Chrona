#ifndef COMPUTER_H
#define COMPUTER_H

#include <QList>
#include "Task.h"

class Computer
{
public:
    Computer();
    ~Computer();

public:
    void SetName(QString);
    void SetIP(QString);
    void SetMAC(QString);
    void SetUniqueID(QString);
    void SetIsThisComputer(bool);

    QString& GetName();
    QString& GetIP();
    QString& GetMAC();
    QString& GetUniqueID();
    bool IsThisComputer();

private:
    QString _name;
    QString _ip;
    QString _mac;
    QString _uniqueID;

    bool _isThisComputer;
};

#endif // COMPUTER_H
