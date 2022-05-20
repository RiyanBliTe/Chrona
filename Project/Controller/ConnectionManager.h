#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QString>

class ConnectionManager final
{
private:
    ConnectionManager();
    ~ConnectionManager();
    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;

public:
    static ConnectionManager& Instance();

    QString GetThisMachineName();
    QString GetThisMachineIP();
    QString GetThisMachineMAC();
};

#define CONNECTION_MANAGER ConnectionManager::Instance()

#endif // CONNECTIONMANAGER_H
