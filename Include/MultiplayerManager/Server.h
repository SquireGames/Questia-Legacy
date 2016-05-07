#ifndef SERVER_H
#define SERVER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

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
        , udpSocket()
        , udpPort(8001)
    {
        udpSocket.bind(udpPort);

    }
    ~Server();

    void update()
    {
        entityManager.update(tileEngine, sf::Vector2f (0,0), sf::Vector2f (0,0), 0.f);
    }

    void send()
    {
        tick++;

        Packet_Player packetObj(tick, std::make_pair(4.5f, 2.1f),7);
        sf::Packet testPacket;
        testPacket << packetObj;

        sf::IpAddress tempIP = sf::IpAddress::getLocalAddress();
        unsigned short tempPort = 8002;

        udpSocket.send(testPacket, tempIP, tempPort);
    }
    void get()
    {

    }

private:
    sf::UdpSocket udpSocket;
    unsigned short udpPort;
    sf::TcpSocket tcpSocket;


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
