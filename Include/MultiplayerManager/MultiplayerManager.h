#ifndef MULTIPLAYERMANAGER_H
#define MULTIPLAYERMANAGER_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <map>

#include "Server.h"

static sf::Mutex terminateMutex;
static bool terminateServer;

//server init
static void hostThreadInit(int ip)
{
    Server server;

    sf::Time timePerUpdate = sf::seconds(1.f/1.f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    sf::Lock mutexLock(terminateMutex);
    terminateMutex.lock();
    while(!terminateServer)
    {
        terminateMutex.unlock();

        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > timePerUpdate)
        {
            timeSinceLastUpdate -= timePerUpdate;
            server.update();
        }

        sf::sleep(timePerUpdate/10.f);

        terminateMutex.lock();
    }
    terminateMutex.unlock();
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
            terminateMutex.lock();
            terminateServer = false;
            terminateMutex.unlock();

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
            terminateMutex.lock();
            terminateServer = true;
            terminateMutex.unlock();
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

    sf::Thread* serverHostThread;

    bool isHostingServer;
    bool isRunningServer;
};

#endif // MULTIPLAYERMANAGER_H
