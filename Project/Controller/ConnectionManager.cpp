#include "ConnectionManager.h"

#include <QHostAddress>
#include <QNetworkInterface>
#include <QHostInfo>

#include <iostream>

ConnectionManager::ConnectionManager()
{

}

ConnectionManager::~ConnectionManager()
{

}

ConnectionManager& ConnectionManager::Instance()
{
    static ConnectionManager instance;
    return instance;
}

QString ConnectionManager::GetThisMachineName()
{
    return QSysInfo::machineHostName();
}

QString ConnectionManager::GetThisMachineIP()
{
    QString localhostIP;
    QList<QHostAddress> hostList = QHostInfo::fromName(QHostInfo::localHostName()).addresses();
    foreach (const QHostAddress& address, hostList) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address.isLoopback() == false) {
             localhostIP = address.toString();
        }
    }

    return localhostIP;
}

QString ConnectionManager::GetThisMachineMAC()
{
    QString localhostIP = "";
    QList<QHostAddress> hostList = QHostInfo::fromName(QHostInfo::localHostName()).addresses();
    foreach (const QHostAddress& address, hostList) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address.isLoopback() == false) {
             localhostIP = address.toString();
        }
    }
    QString localMacAddress = "";
    foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces()) {
        foreach (const QNetworkAddressEntry& entry, networkInterface.addressEntries()) {
            if (entry.ip().toString() == localhostIP) {
                localMacAddress = networkInterface.hardwareAddress();
                break;
            }
        }
    }

    return localMacAddress;
}
