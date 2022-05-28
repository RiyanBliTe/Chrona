#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <QHostAddress>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QSysInfo>

class NetworkController final
{
private:
    NetworkController();
    ~NetworkController();
    NetworkController(const NetworkController&) = delete;
    NetworkController& operator=(const NetworkController&) = delete;

public:
    static NetworkController &Instance();

    QString GetThisMachineName();
    QString GetThisMachineIP();
    QString GetThisMachineMAC();
    QString GetThisMachineUniqueID();
};

#endif // NETWORKCONTROLLER_H
