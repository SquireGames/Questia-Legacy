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
        , tickRate(64)
        , resourceManager()
        , window()
        , timeManager(0,0)
        , lightManager(window, timeManager, resourceManager)
        , tileEngine(window, resourceManager)
        , entityManager(window, resourceManager, lightManager)
        , spawnManager(false, entityManager)
        , itemManager(window, resourceManager)
    {

    }
    ~Server();

    void update()
    {
        tick++;
    }

private:
    sf::UdpSocket udpSocket;
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

    unsigned int tickRate;
    unsigned int tick;
};

#endif // SERVER_H
