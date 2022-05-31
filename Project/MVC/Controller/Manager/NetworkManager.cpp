#include "NetworkManager.h"

#include <QHostAddress>
#include <QHostInfo>
#include <QNetworkInterface>

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}
{}

NetworkManager& NetworkManager::Instance()
{
    static NetworkManager instance;
    return instance;
}

QString NetworkManager::GetThisMachineName()
{
    return QSysInfo::machineHostName();
}

QString NetworkManager::GetThisMachineIP()
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

QString NetworkManager::GetThisMachineMAC()
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

QString NetworkManager::GetThisMachineUniqueID()
{
    return QSysInfo::machineUniqueId();
}
