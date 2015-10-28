#include <iostream>

#include "MultiplayerManager.h"

#define PACKET_TYPES 1

MultiplayerManager::MultiplayerManager():
    isActive(false)
    , isHost(false)
    , udpSocket()
    , clientMap()
    , hostPort(7777)
    , hostIP("0.0.0.0")
    , struct_Character(-99,-99,0,0)
{
    std::cout<<"DEBUG: Multiplayer Manager Initialized"<<std::endl;
    udpSocket.setBlocking(false);
    udpSocket.bind(udpSocket.AnyPort);
}

void MultiplayerManager::startServer(const unsigned int port)
{
    std::cout<<"Server started on port: "<<port<<std::endl;

    isHost = true;
    isActive = true;

    //Usually 7777
    udpSocket.unbind();
    udpSocket.bind(port);
}

void MultiplayerManager::joinServer(std::string IP, unsigned short port)
{
    isHost = false;
    isActive = true;

    sf::IpAddress host = IP;
    int header = 77;
    sf::Packet clientPacket0;

    clientPacket0 << header;

    udpSocket.send(clientPacket0, host, port);

    hostIP = host;
    hostPort = port;
}


void MultiplayerManager::server_recievePackets()
{
    std::string stopChecking = "111.111.1.1";
    do
    {
        sf::IpAddress clientIP;
        unsigned short clientPort;

        sf::Packet clientPacket;

        udpSocket.receive(clientPacket, clientIP, clientPort);
        stopChecking = clientIP.toString();

        int header;
        clientPacket >> header;

        for(std::map<short unsigned int, sf::IpAddress>::iterator it = clientMap.begin(); it!=clientMap.end(); ++it)
        {
            sf::IpAddress clientListIP = it->second;
            unsigned short clientListPort = it->first;

            ///If on the list:
            if(clientIP == clientListIP && clientPort == clientListPort)
            {
                float f1, f2, f3;
                int i1;

                switch(header)
                {
                case 1:
                    // x coord, y coord, angle, step
                    clientPacket >> f1 >> f2 >>f3 >> i1;;
                    Struct_Character struct_c(f1,f2, f3, i1);

                    std::cout<<"PlayerStep: "<< i1 <<std::endl;
                    std::cout<<"Angle : "<< f3 <<std::endl;

                    struct_Character = struct_c;
                    break;
                }


            }
        }
        if(header == 77 && clientIP!="0.0.0.0")
        {
            clientMap[clientPort] = clientIP;
            std::cout<<"Player: "<<clientIP<<":"<<clientPort<<" Has joined the server"<<std::endl;
        }
    }
    while(stopChecking!="0.0.0.0");
}

void MultiplayerManager::client_recievePackets()
{
    std::string stopChecking = "111.111.1.1";
    do
    {
        sf::Packet serverPacket;

        sf::IpAddress hostIP_r;
        unsigned short hostPort_r;

        udpSocket.receive(serverPacket, hostIP_r, hostPort_r);
        stopChecking = hostIP_r.toString();

        int header;
        serverPacket >> header;

        ///If connected with host:
        if(hostIP_r == hostIP && hostPort_r == hostPort)
        {
            float f1, f2, f3;
            int i1;

            switch(header)
            {
            case 1:
                // x coord, y coord, angle, step
                serverPacket >> f1 >> f2 >> f3 >> i1;

                Struct_Character struct_c(f1,f2,f3,i1);
                struct_Character = struct_c;
                break;
            }

        }
    }
    while(stopChecking!="0.0.0.0");
}

void MultiplayerManager::server_sendPackets(sf::Vector2f playerCoordinates, float angleToMouse, int playerStep)
{
    unsigned int received = 0;
    char buffer[2];

    for(std::map<short unsigned int, sf::IpAddress>::iterator it = clientMap.begin(); it!=clientMap.end(); ++it)
    {
        sf::IpAddress clientIP = it->second;
        unsigned short clientPort = it->first;


        //Character
        sf::Packet serverPacket1;
        int header = 1;
        serverPacket1 << header << playerCoordinates.x << playerCoordinates.y << angleToMouse << playerStep;
        udpSocket.send(serverPacket1, clientIP, clientPort);
    }
}


void MultiplayerManager::client_sendPackets(sf::Vector2f playerCoordinates, float angleToMouse, int playerStep)
{
    int header;
    sf::Packet clientPacket1;

    //Character
    header = 1;
    clientPacket1 << header << playerCoordinates.x << playerCoordinates.y<< angleToMouse << playerStep;
    udpSocket.send(clientPacket1, hostIP, hostPort);
}

bool MultiplayerManager::isRunningServer()
{
    bool answer = (isActive == true && isHost == true)? true : false;
    return answer;
}

bool MultiplayerManager::isClient()
{
    bool answer = (isActive == true && isHost == false)? true : false;
    return answer;
}

Struct_Character MultiplayerManager::m_character()
{
    return struct_Character;
}

