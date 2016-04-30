#ifndef MULTIPLAYERMANAGER_H
#define MULTIPLAYERMANAGER_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <map>

#include "Server.h"

class MultiplayerManager
{
public:
    MultiplayerManager(std::string _serverName):
        server(nullptr)
        , thread_client_main(&MultiplayerManager::client_mainThread, this)
        , thread_host_main  (&MultiplayerManager::host_mainThread,   this)
        , thread_host_tcp   (&MultiplayerManager::host_udpThread,    this)
        , host_terminate  (false)
        , host_alive_main (false)
        , host_alive_tcp  (false)
        , isRunningServer (false)
        , isKillingServer (false)
        , tickRate(5) // no active thread at this point
    {

    }
    ~MultiplayerManager()
    {
        terminateHost(); // just to make sure
    }

    ///Server

    //main thread, handles tcp
    void host_mainThread()
    {
        Server* svr = server; //saved to delete the server

        std::cout << "host_mainThread() init" << std::endl;

        host_changeTickRateMutex.lock();
        float threadTickRate = tickRate;
        host_changeTickRateMutex.unlock();

        sf::Time timePerUpdate = sf::seconds(1.f/threadTickRate);
        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;

        host_terminateMutex.lock();
        while(!host_terminate)
        {
            host_terminateMutex.unlock();

            //check for changes in tick rate
            host_changeTickRateMutex.lock();
            if(host_tickChange_tcp)
            {
                host_tickChange_tcp = false;
                threadTickRate = tickRate;
                timePerUpdate = sf::seconds(1.f/threadTickRate);
            }
            host_changeTickRateMutex.unlock();

            //update
            sf::Time elapsedTime = clock.restart();
            timeSinceLastUpdate += elapsedTime;
            while (timeSinceLastUpdate > timePerUpdate)
            {
                timeSinceLastUpdate -= timePerUpdate;
                svr->update();
                std::cout << "tick" << std::endl;
            }
            sf::sleep(timePerUpdate/10.f);

            host_terminateMutex.lock();
        }
        host_terminateMutex.unlock();

        ///death of tcp
        host_aliveMutex.lock();
        if(!host_alive_tcp)
        {
            delete svr;
        }
        host_alive_main = false;
        host_aliveMutex.unlock();
        std::cout << "host_mainThread() ded" << std::endl;
    }
    //secondary thread, handles udp
    void host_udpThread()
    {
        Server* svr = server; //saved to delete the server

        std::cout << "host_udpThread init" << std::endl;

        host_changeTickRateMutex.lock();
        float threadTickRate = tickRate;
        host_changeTickRateMutex.unlock();

        sf::Time timePerUpdate = sf::seconds(1.f/threadTickRate);
        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;

        host_terminateMutex.lock();
        while(!host_terminate)
        {
            host_terminateMutex.unlock();

            //check for changes in tick rate
            host_changeTickRateMutex.lock();
            if(host_tickChange_udp)
            {
                host_tickChange_udp = false;
                threadTickRate = tickRate;
                timePerUpdate = sf::seconds(1.f/threadTickRate);
            }
            host_changeTickRateMutex.unlock();

            //update
            sf::Time elapsedTime = clock.restart();
            timeSinceLastUpdate += elapsedTime;
            while (timeSinceLastUpdate > timePerUpdate)
            {
                timeSinceLastUpdate -= timePerUpdate;
                svr->update();
                std::cout << "tick" << std::endl;
            }
            sf::sleep(timePerUpdate/10.f);

            host_terminateMutex.lock();
        }
        host_terminateMutex.unlock();

        ///death of udp
        host_aliveMutex.lock();
        if(!host_alive_main)
        {
            delete svr;
        }
        host_alive_tcp = false;
        host_aliveMutex.unlock();
        std::cout << "host_udpThread ded" << std::endl;
    }
    void startHostingServer()
    {
        if(!isRunningServer)
        {
            if(!server) //server is a pointer, checking if it exists
            {
                server = new Server();
            }

            thread_host_main.launch();
            thread_host_tcp .launch();
            isRunningServer = true;

            host_aliveMutex.lock();
            host_alive_main = true;
            host_alive_tcp =  true;
            host_aliveMutex.unlock();
        }
    }
    void terminateHost()
    {
        if(isRunningServer)
        {
            host_terminateMutex.lock();
            host_terminate = true;
            host_terminateMutex.unlock();
            isKillingServer = true;
        }
    }

    ///client

    void client_mainThread()
    {

    }
    void joinServer()
    {
        if(isRunningServer)
        {

        }
    }

    ///manager

    void update()
    {
        if(isRunningServer && isKillingServer)
        {
            host_aliveMutex.lock();
            if(!host_alive_main && !host_alive_tcp)
            {
                std::cout << "SERVER TERMINATED" << std::endl;
                isRunningServer = false;
                isKillingServer = false;

                //just to make sure, should already be dead
                thread_host_main.terminate();
                thread_host_tcp.terminate();

                //threads are dead, should be safe
                host_terminate = false;
            }
            host_aliveMutex.unlock();
        }
    }
    bool isServerDead()
    {
        return !isRunningServer;
    }
    void host_changeTickRate(float _tickRate)
    {
        host_changeTickRateMutex.lock();
        if(_tickRate != tickRate)
        {
            host_tickChange_tcp = true;
            host_tickChange_udp = true;
            tickRate = _tickRate;
        }
        host_changeTickRateMutex.unlock();
    }


private:
    Server* server;

///server
//terminate
    sf::Mutex host_terminateMutex;
    bool      host_terminate;
//check if alive
    sf::Mutex host_aliveMutex;
    bool      host_alive_main;
    bool      host_alive_tcp;
//tick rate
    sf::Mutex host_changeTickRateMutex;
    bool      host_tickChange_udp;
    bool      host_tickChange_tcp;
    float tickRate;


///threads
    sf::Thread thread_host_main;
    sf::Thread thread_host_tcp;
    sf::Thread thread_client_main;

///thread safe
    bool isRunningServer;
    bool isKillingServer;
};

#endif // MULTIPLAYERMANAGER_H
