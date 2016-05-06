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
        , entityManager(window, resourceManager, lightManager)
        , spawnManager(false, entityManager)
        , itemManager(window, resourceManager)
        , udpSocket()
        , udpPort(7777)
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

        sf::Packet testPacket;
        testPacket << "tick: " << tick;

        sf::IpAddress tempIP("192.168.2.6");
        unsigned short tempPort = 7776;

        udpSocket.send(testPacket, tempIP, tempPort);
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
