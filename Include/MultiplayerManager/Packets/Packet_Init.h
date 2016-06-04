#ifndef PACKET_INIT_H
#define PACKET_INIT_H

#include <string>
#include <SFML/Network.hpp>
#include "Packet.h"

enum class pktInitCommands {error = 0, server_info = 1};

struct Packet_Init
{
    Packet_Init();
    ~Packet_Init();
};

//{ client login
struct Packet_Init_Login
{
    Packet_Init_Login(std::string _username, std::string _password):
        username(_username)
        , password(_password)
    {}
    Packet_Init_Login(){}
    //will be encrypted later
    std::string username;
    std::string password;
};

static sf::Packet& operator << (sf::Packet& packet, const Packet_Init_Login& player)
{
    packet << static_cast <sf::Int32> (pkt::Header::playerLogin);
    packet << player.username;
    packet << player.password;
    return packet;
}

static sf::Packet& operator >> (sf::Packet& packet, Packet_Init_Login& player)
{
    packet >> player.username;
    packet >> player.password;
    return packet;
}
//}

//{ server response
struct Packet_Init_SvrResp
{
    Packet_Init_SvrResp(bool _response):
        response(_response)
    {}
    Packet_Init_SvrResp() {}
    bool response;
};

static sf::Packet& operator << (sf::Packet& packet, const Packet_Init_SvrResp& player)
{
    packet << static_cast <sf::Int32> (pkt::Header::svrResp);
    packet << player.response;
    return packet;
}

static sf::Packet& operator >> (sf::Packet& packet, Packet_Init_SvrResp& player)
{
    packet >> player.response;
    return packet;
}
//}

#endif // PACKET_INIT_H
