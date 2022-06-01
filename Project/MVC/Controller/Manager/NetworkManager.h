#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    static NetworkManager& Instance();

    QString GetThisMachineName();
    QString GetThisMachineIP();
    QString GetThisMachineMAC();
    QString GetThisMachineUniqueID();

private:
    explicit NetworkManager(QObject *parent = nullptr);
    NetworkManager(const NetworkManager&) = delete;
    NetworkManager& operator=(const NetworkManager&) = delete;
    ~NetworkManager();
};

#endif // NETWORKMANAGER_H
