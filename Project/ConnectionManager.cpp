#include "ConnectionManager.h"

#include <QHostAddress>
#include <QNetworkInterface>
#include <QHostInfo>

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
    QString ipString = "";
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
        {
             ipString = address.toString();
             break;
        }
    }

    return ipString;
}
