#ifndef SERVER_H
#define SERVER_H

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>

//#include <Packet_Player.h>

class Server
{
public:
    Server():
        tick(0)
        , tickRate(64)
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

    unsigned int tickRate;
    unsigned int tick;
};

#endif // SERVER_H
