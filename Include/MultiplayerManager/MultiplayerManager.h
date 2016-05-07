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
        , client_terminate   (false)
        , host_alive_send    (false)
        , host_alive_recieve (false)
        , client_alive       (false)
        , isRunningServer    (false)
        , isRunningClient    (false)
        , isKillingServer    (false)
        , isKillingClient    (false)
        , tickRate(5) // no active thread at this point
    {

    }
    ~MultiplayerManager()
    {
        // just to make sure
        terminateHost();
        terminateClient();
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
        if(!isRunningClient)
        {
            thread_client_main.launch();
            isRunningClient = true;

            client_aliveMutex.lock();
            client_alive = true;
            client_aliveMutex.unlock();
        }
    }
    void terminateClient()
    {
        if(isRunningClient)
        {
            client_terminateMutex.lock();
            client_terminate = true;
            client_terminateMutex.unlock();
            isKillingClient = true;
        }
    }

///manager

    void update()
    {
        //send client information
        //...

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
        if(isRunningClient && isKillingClient)
        {
            client_aliveMutex.lock();
            if(!client_alive)
            {
                std::cout << "CLIENT TERMINATED" << std::endl;
                isRunningClient = false;
                isKillingClient = false;

                //just to make sure
                thread_client_main.terminate();

                //just in case, should be safe
                client_terminate = false;
            }
            client_aliveMutex.unlock();
        }
    }
    bool isServerDead()
    {
        return !isRunningServer;
    }
    bool isClientDead()
    {
        return !isRunningClient;
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
        sf::Time timePerUpdate = sf::seconds(1.f/144.f);
        sf::Time timePerSend   = sf::seconds(1.f/threadTickRate);
        sf::Clock clock_update;
        sf::Clock clock_send;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;
        sf::Time timeSinceLastSend = sf::Time::Zero;

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
                if(threadTickRate > 144.f)
                {
                    threadTickRate = 144.f;
                }
                timePerSend = sf::seconds(1.f/threadTickRate);
            }
            host_changeTickRateMutex.unlock();



            ///update
            sf::Time elapsedTime_update = clock_update.restart();
            timeSinceLastUpdate += elapsedTime_update;
            while (timeSinceLastUpdate > timePerUpdate)
            {
                timeSinceLastUpdate -= timePerUpdate;
                svr->update();
            }


            ///send
            sf::Time elapsedTime_send = clock_send.restart();
            timeSinceLastSend += elapsedTime_send;
            while (timeSinceLastSend > timePerSend)
            {
                timeSinceLastSend -= timePerSend;
                svr->send();
            }

            sf::sleep(sf::Time(sf::milliseconds(sf::Int32(4))));

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
        unsigned short tempPort = 7777;
        tempSocket.bind(tempPort);

        sf::SocketSelector selector;

        host_terminateMutex.lock();
        while(!host_terminate)
        {
            host_terminateMutex.unlock();

            if(selector.wait(sf::Time(sf::milliseconds(sf::Int32(100)))))
            {
                if(selector.isReady(tempSocket))
                {
                    std::string item1;
                    int item2;


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
        std::cout << "client_mainThread() init" << std::endl;

        sf::UdpSocket tempSocket;
        unsigned short tempPort = 8002;
        tempSocket.bind(tempPort);

        sf::SocketSelector selector;
        selector.add(tempSocket);

        client_terminateMutex.lock();

        while(!client_terminate)
        {
            client_terminateMutex.unlock();
            if(selector.wait(sf::Time(sf::milliseconds(sf::Int32(100)))))
            {
                if(selector.isReady(tempSocket))
                {
                    unsigned short tempPort2 = 8001;
                    sf::IpAddress tempIP = sf::IpAddress::getLocalAddress();

                    sf::Packet packet;
                    tempSocket.receive(packet,tempIP, tempPort2);

                    int header;
                    packet >> header;
                    switch (header)
                    {
                    case pkt::Header::player:
                    {
                        std::cout << "player" << std::endl;
                        Packet_Player player;
                        packet >> player;
                        std::cout << "playerID:" << player.playerID << std::endl;
                        std::cout << "playerNumber:" << player.packetNumber << std::endl;
                        std::cout << "playerCoords:" << player.coords_x << "," << player.coords_y << std::endl;
                    }
                    break;
                    case pkt::Header::playerContainer:
                    {
                        std::cout << "player container" << std::endl;
                    }
                    break;
                    case pkt::Header::entity:
                        std::cout << "entity" << std::endl;
                        break;
                    }


                    //packet >> item1 >> item2;
                    //std::cout << item1 << item2 << std::endl;
                }
            }
            client_terminateMutex.lock();
        }
        client_terminateMutex.unlock();

        ///death
        client_aliveMutex.lock();
        client_alive = false;
        client_aliveMutex.unlock();
        std::cout << "client_mainThread() ded" << std::endl;
    }


///server
    Server* server;
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
    float     tickRate;

//threads
    sf::Thread thread_host_send;
    sf::Thread thread_host_recieve;

//thread safe
    bool isRunningServer;
    bool isKillingServer;


///client
//terminate
    sf::Mutex   client_terminateMutex;
    bool        client_terminate;
//check if alive
    sf::Mutex   client_aliveMutex;
    bool        client_alive;

//threads
    sf::Thread thread_client_main;

//thread safe
    bool isRunningClient;
    bool isKillingClient;
};

#endif // MULTIPLAYERMANAGER_H
