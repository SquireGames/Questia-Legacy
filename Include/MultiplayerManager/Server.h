#ifndef SERVER_H
#define SERVER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <queue>

#include "Packet_Player.h"

#include "TimeManager/TimeManager.h"
#include "LightManager/LightManager.h"
#include "TileEngine/TileEngine.h"
#include "EntityManager/EntityManager.h"
#include "EntityManager/SpawnManager.h"
#include "CharacterManager/CharacterManager.h"
#include "ItemManager/ItemManager.h"

#include "ResourceManager.h"

class Server
{
public:
    Server():
        tick(0)
        , resourceManager()
        , window()
        , timeManager(0,0)
        , lightManager(window, timeManager, resourceManager)
        , tileEngine(window, resourceManager)
        , entityManager(EntityManager::ManagerType::server, window, resourceManager, lightManager)
        , spawnManager(false, entityManager)
        , itemManager(window, resourceManager)
        , udpSocket_send()
        , selector()
    {
        ///send
        udpSocket_send   .bind(8000);

        ///receive
        udpSocket_receive.bind(8001);
        selector.add(udpSocket_receive);

        ///entityManager
        entityManager.createPlayer("test",
                                   sf::Vector2f(20*32,20*32),
                                   100, 100,
                                   100, 100,
                                   100, 100);
    }
    ~Server();

    ///send thread
    void update()
    {
        std::vector <Packet_Player> playerData;

        playerDataMutex.lock();
        playerData = playerData_received;
        playerData_received.clear();
        playerDataMutex.unlock();

        std::sort(playerData.begin(), playerData.end());

        for(int it = 0; it != playerData.size(); it++)
        {
            playerData_queue.push(playerData[it]);
        }

        while(!playerData_queue.empty())
        {
            //std::cout << "Packet: " << playerData_queue.front().packetNumber << ", Coords: (" << playerData_queue.front().coords_x << ", " << playerData_queue.front().coords_y << ")" << std::endl;
            entityManagerMutex.lock();
            entityManager.setPlayerCoordinates(sf::Vector2f(playerData_queue.front().coords_x, playerData_queue.front().coords_y));
            entityManagerMutex.unlock();
            playerData_queue.pop();
        }

        entityManager.update(tileEngine, sf::Vector2f (0,0), sf::Vector2f (0,0), 0.f);
    }
    void send()
    {
        tick++;

        entityManagerMutex.lock();
        float coords_x = entityManager.getPlayerCoordinates().x;
        float coords_y = entityManager.getPlayerCoordinates().y;
        entityManagerMutex.unlock();

        Packet_Player packetObj(tick, -1, std::make_pair(coords_x, coords_y));
        sf::Packet testPacket;
        testPacket << packetObj;

        sf::IpAddress tempIP = sf::IpAddress::getLocalAddress();
        unsigned short tempPort = 8003;

        udpSocket_send.send(testPacket, tempIP, tempPort);
    }

    ///receive thread
    void receive()
    {
        if(selector.wait(sf::Time(sf::milliseconds(sf::Int32(100)))))
        {
            if(selector.isReady(udpSocket_receive))
            {
                unsigned short tempPort2 = 8002;
                sf::IpAddress tempIP = sf::IpAddress::getLocalAddress();

                sf::Packet packet;
                udpSocket_receive.receive(packet,tempIP, tempPort2);

                //std::cout << ">>>>>SERVER<<<<<" << std::endl;

                int header;
                packet >> header;
                switch (header)
                {
                case pkt::Header::player:
                {
                    //std::cout << "player" << std::endl;
                    Packet_Player player;
                    packet >> player;
                    //std::cout << "playerID:" << player.playerID << std::endl;
                    //std::cout << "playerNumber:" << player.packetNumber << std::endl;
                    //std::cout << "playerCoords:" << player.coords_x << "," << player.coords_y << std::endl;

                    playerDataMutex.lock();
                    playerData_received.push_back(player);
                    playerDataMutex.unlock();
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

               //std::cout << "<<<<<SERVER>>>>>" << std::endl;
            }
        }
    }

private:
    ///send
    sf::UdpSocket udpSocket_send;
    sf::TcpSocket tcpSocket;

    ///receive
    sf::UdpSocket udpSocket_receive;
    sf::SocketSelector selector;

    ///data
    //player packet
    sf::Mutex playerDataMutex;
    std::vector <Packet_Player> playerData_received;
    std::queue  <Packet_Player> playerData_queue;
    //entityManager
    sf::Mutex entityManagerMutex;


    //modules
    TimeManager timeManager;
    LightManager lightManager;
    TileEngine tileEngine; //for AI collision
    EntityManager entityManager;
    SpawnManager spawnManager;
    ItemManager itemManager;

    //inactive
    ResourceManager resourceManager;
    sf::RenderWindow window;

    unsigned int tick;
};

#endif // SERVER_H
