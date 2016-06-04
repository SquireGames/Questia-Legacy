#ifndef SERVER_H
#define SERVER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <queue>

#include "Packet.h"
#include "Packet_Player.h"
#include "Packet_Init.h"
#include "Packet_Entity.h"

#include "TimeManager/TimeManager.h"
#include "LightManager/LightManager.h"
#include "TileEngine/TileEngine.h"
#include "EntityManager/EntityManager.h"
#include "EntityManager/SpawnManager.h"
#include "CharacterManager/CharacterManager.h"
#include "ItemManager/ItemManager.h"

#include "ResourceManager.h"

enum class ClientStage {disconnected = 0, connected = 1, choosingCharacter = 2, active = 3};

struct Client
{
    Client(int _clientID, sf::TcpSocket* _tcpSocket, sf::IpAddress _ip):
        clientID(_clientID)
        , tcpSocket_send(nullptr)
        , tcpSocket_receieve(nullptr)
        , ip(_ip)
        , clientStage(ClientStage::disconnected)
    {
        if(_tcpSocket->getRemotePort() == 8005)
        {
            tcpSocket_send = _tcpSocket;
        }
        else if(_tcpSocket->getRemotePort() == 8006)
        {
            tcpSocket_receieve = _tcpSocket;
        }
    }
    bool addSocket(sf::TcpSocket* _tcpSocket)
    {
        if(_tcpSocket != nullptr)
        {
            if(_tcpSocket->getRemotePort() == 8005)
            {
                tcpSocket_send = _tcpSocket;
            }
            else if(_tcpSocket->getRemotePort() == 8006)
            {
                tcpSocket_receieve = _tcpSocket;
            }
            if(tcpSocket_send != nullptr && tcpSocket_receieve != nullptr)
            {
                return true;
            }
        }
        return false;
    }

    int clientID;
    sf::TcpSocket* tcpSocket_receieve;
    sf::TcpSocket* tcpSocket_send;
    sf::IpAddress ip;
    ClientStage clientStage;

    //client connects -> client sends login info -> server returns character list -> client sends character choice -> server initiates character and starts sending info
};

struct Map
{
    Map():
        resourceManager()
        , window()
        , timeManager(0,0)
        , lightManager(window, timeManager, resourceManager)
        , tileEngine(window, resourceManager)
        , entityManager(EntityManager::ManagerType::server, window, resourceManager, lightManager)
        , spawnManager(false, entityManager)
        , itemManager(window, resourceManager)
    {}

    //inactive
    ResourceManager resourceManager;
    sf::RenderWindow window;

    TimeManager timeManager;
    LightManager lightManager;
    TileEngine tileEngine;
    EntityManager entityManager;
    SpawnManager spawnManager;
    ItemManager itemManager;
};

class Server
{
public:
    Server();
    ~Server();

    ///send thread
    void update();
    void send();
    ///receive thread
    void receive();

private:
    ///server
    void checkClient(); //used for joining stages,

    ///clients
    std::vector <Client*> clientVector;
    int clientCount;

    ///send
    sf::UdpSocket udpSocket_send;
    sf::TcpSocket tcpSocket;

    ///receive
    sf::UdpSocket udpSocket_receive;
    sf::SocketSelector selector;
    sf::TcpListener listener;

    ///data
    //player packet
    sf::Mutex playerDataMutex;
    std::vector <Packet_Player> playerData_received;
    std::queue  <Packet_Player> playerData_queue;
    //entityManager
    sf::Mutex entityManagerMutex;

    ///game
    std::vector <Map*> mapVector;

    ///login
    std::vector <std::pair <std::string, std::string> > registeredClients;

    unsigned int tick;
};

#endif // SERVER_H
