#ifndef MULTIPLAYERMANAGER_H
#define MULTIPLAYERMANAGER_H

#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <iostream>
#include <map>

class MultiplayerManager
{
public:
    MultiplayerManager(std::string _serverName)
    {
        serverName = _serverName;
    }
    ~MultiplayerManager()
    {
        //make sure to delete thread safely
    }

    void startMultiplayer(bool isServerHost);

    void sendServerData();

private:
    std::string serverName;
};

#endif // MULTIPLAYERMANAGER_H
