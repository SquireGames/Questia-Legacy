#ifndef MULTIPLAYERMANAGER_H
#define MULTIPLAYERMANAGER_H

#include "MultiplayerManager/Struct_Character.h"

#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <iostream>
#include <map>

///TODO H/ Add Multiplayer component
class MultiplayerManager
{
public:
    MultiplayerManager();
    void startServer(unsigned int port);
    void joinServer(std::string IP, unsigned short port);

    void server_recievePackets();
    void client_recievePackets();

    void server_sendPackets(sf::Vector2f playerCoordinates, float angleToMouse, int playerStep);
    void client_sendPackets(sf::Vector2f playerCoordinates, float angleToMouse, int playerStep);

    Struct_Character m_character();
    Struct_Character struct_Character;

    bool isRunningServer();
    bool isClient();


private:
    bool isActive;
    bool isHost;

    sf::UdpSocket udpSocket;
    int numberOfClients;

    std::map <short unsigned int, sf::IpAddress> clientMap;

    sf::IpAddress hostIP;
    unsigned short hostPort;


};

#endif // MULTIPLAYERMANAGER_H
