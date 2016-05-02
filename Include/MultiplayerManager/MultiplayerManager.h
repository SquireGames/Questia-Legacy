#ifndef MULTIPLAYERMANAGER_H
#define MULTIPLAYERMANAGER_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <map>

#include "Server.h"

#include "Packet.h"
#include "Packet_Player.h"

class MultiplayerManager
{
public:
    MultiplayerManager(std::string _serverName):
        server(nullptr)
        , thread_client_main  (&MultiplayerManager::client_mainThread,  this)
        , thread_host_send    (&MultiplayerManager::host_sendThread,    this)
        , thread_host_recieve (&MultiplayerManager::host_recieveThread, this)
        , host_terminate     (false)
        , host_alive_send    (false)
        , host_alive_recieve (false)
        , isRunningServer    (false)
        , isKillingServer    (false)
        , tickRate(5) // no active thread at this point
    {

    }
    ~MultiplayerManager()
    {
        terminateHost(); // just to make sure
    }

///server
    void startHostingServer()
    {
        if(!isRunningServer)
        {
            server = new Server();

            thread_host_send   .launch();
            thread_host_recieve.launch();
            isRunningServer = true;

            host_aliveMutex.lock();
            host_alive_send =    true;
            host_alive_recieve = true;
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
    void joinServer()
    {

    }

///manager

    void update()
    {
        //send client information


        if(isRunningServer && isKillingServer)
        {
            host_aliveMutex.lock();
            if(!host_alive_send && !host_alive_recieve)
            {
                std::cout << "SERVER TERMINATED" << std::endl;
                isRunningServer = false;
                isKillingServer = false;

                //just to make sure, should already be dead
                thread_host_send.terminate();
                thread_host_recieve.terminate();

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
            host_tickChange = true;
            tickRate = _tickRate;
        }
        host_changeTickRateMutex.unlock();
    }


private:
    ///Threads
    //handles sending
    void host_sendThread()
    {
        std::cout << "host_sendThread() init" << std::endl;
        Server* svr = server; //saved to delete the server

        ///tick rate
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

            ///check for changes in tick rate
            host_changeTickRateMutex.lock();
            if(host_tickChange)
            {
                host_tickChange = false;
                threadTickRate = tickRate;
                timePerUpdate = sf::seconds(1.f/threadTickRate);
            }
            host_changeTickRateMutex.unlock();

            ///update
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

        ///death
        host_aliveMutex.lock();
        if(!host_alive_recieve)
        {
            delete svr;
            svr = nullptr;
        }
        host_alive_send = false;
        host_aliveMutex.unlock();
        std::cout << "host_sendThread() ded" << std::endl;
    }
    //handles receiving
    void host_recieveThread()
    {
        std::cout << "host_recieveThread() init" << std::endl;
        Server* svr = server; //saved to delete the server

        sf::UdpSocket tempSocket;
        sf::SocketSelector selector;

        host_terminateMutex.lock();
        while(!host_terminate)
        {
            host_terminateMutex.unlock();

            if(selector.wait(sf::Time(sf::milliseconds(sf::Int32(100)))))
            {
                if(selector.isReady(tempSocket))
                {

                }
            }

            host_terminateMutex.lock();
        }
        host_terminateMutex.unlock();


        ///death
        host_aliveMutex.lock();
        if(!host_alive_send)
        {
            delete svr;
            svr = nullptr;
        }
        host_alive_recieve = false;
        host_aliveMutex.unlock();
        std::cout << "host_recieveThread() ded" << std::endl;
    }
    // used to receive
    void client_mainThread()
    {

    }


    Server* server;

///server
//terminate
    sf::Mutex host_terminateMutex;
    bool      host_terminate;
//check if alive
    sf::Mutex host_aliveMutex;
    bool      host_alive_send;
    bool      host_alive_recieve;
//tick rate
    sf::Mutex host_changeTickRateMutex;
    bool      host_tickChange;
    float tickRate;


///threads
    sf::Thread thread_host_send;
    sf::Thread thread_host_recieve;
    sf::Thread thread_client_main;

///thread safe
    bool isRunningServer;
    bool isKillingServer;
};

#endif // MULTIPLAYERMANAGER_H
