#include "NetworkController.h"

NetworkController::NetworkController()
{

}

NetworkController::~NetworkController()
{

}

NetworkController &NetworkController::Instance()
{
    static NetworkController instance;
    return instance;
}

QString NetworkController::GetThisMachineName()
{
    return QSysInfo::machineHostName();
}

QString NetworkController::GetThisMachineIP()
{
    QString localhostIP;
    QList<QHostAddress> hostList = QHostInfo::fromName(QHostInfo::localHostName()).addresses();
    foreach (const QHostAddress& address, hostList)
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address.isLoopback() == false)
        {
            localhostIP = address.toString();
        }
    }

    return localhostIP;
}

QString NetworkController::GetThisMachineMAC()
{
    QString localhostIP = "";
    QList<QHostAddress> hostList = QHostInfo::fromName(QHostInfo::localHostName()).addresses();
    foreach (const QHostAddress& address, hostList) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address.isLoopback() == false) {
            localhostIP = address.toString();
        }
    }
    QString localMacAddress = "";
    foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces())
    {
        foreach (const QNetworkAddressEntry& entry, networkInterface.addressEntries())
        {
            if (entry.ip().toString() == localhostIP)
            {
                localMacAddress = networkInterface.hardwareAddress();
                break;
            }
        }
    }

    return localMacAddress;
}

QString NetworkController::GetThisMachineUniqueID()
{
    return QSysInfo::machineUniqueId();
}
