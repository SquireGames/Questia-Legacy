#ifndef MULTIPLAYERMANAGER_H
#define MULTIPLAYERMANAGER_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <map>
#include <functional> // std::bind

#include "Server.h"

struct SharedVariables
{
    bool terminate;
};
static SharedVariables sharedVariables;

//server init
static void hostThreadInit(int ip)
{
    Server server;

    sf::Time timePerUpdate = sf::seconds(1.f/1.f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(true)
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > timePerUpdate)
        {
            timeSinceLastUpdate -= timePerUpdate;
            server.update();
        }

        if(sharedVariables.terminate)
        {

        }

        sf::sleep(timePerUpdate/10.f);
    }
}

class MultiplayerManager
{
public:
    MultiplayerManager(std::string _serverName):
        isHostingServer (false)
        , isRunningServer (false)
    {
        serverName = _serverName;
    }
    ~MultiplayerManager()
    {

    }

    void startHostingServer()
    {
        if(!isHostingServer && !isRunningServer)
        {
            serverHostThread = new sf::Thread(&hostThreadInit, 5);
            serverHostThread->launch();

            isHostingServer = true;
            isRunningServer = true;
        }
    }

    void terminateHost()
    {
        if(isRunningServer)
        {

        }
    }

    void joinServer()
    {
        if(!isHostingServer && !isRunningServer)
        {

        }
    }

    // general server info from host
    void getServerInfo()
    {
        //mutex
    }

private:
    std::string serverName;

    bool isHostingServer;
    bool isRunningServer;

    sf::Thread* serverHostThread;
};

#endif // MULTIPLAYERMANAGER_H
