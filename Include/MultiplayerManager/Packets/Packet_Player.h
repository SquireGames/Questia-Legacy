#ifndef PACKET_PLAYER_H
#define PACKET_PLAYER_H

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "Packet.h"

struct pkt
{
    //packet
    enum Header { other = 0, player = 1, playerContainer = 2, entity = 3, entityContainer = 4};

    //entities
    enum Direction {none = 0, up = 1, upRight = 2, right = 3, downRight = 4, down = 5, downLeft = 6, left = 7, upLeft = 8};
};

//{ Packet_Player
struct Packet_Player : public Packet
{
    Packet_Player(int _packetNumber, std::pair <float, float> coordinates, int _playerID):
        packetNumber(static_cast <sf::Int32> (_packetNumber))
        , coords_x(static_cast <sf::Int32> (coordinates.first))
        , coords_y(static_cast <sf::Int32> (coordinates.second))
        , playerID(static_cast <sf::Int32> (_playerID))
    {}
    Packet_Player(std::pair <float, float> coordinates, int _playerID):
        coords_x(static_cast <sf::Int32> (coordinates.first))
        , coords_y(static_cast <sf::Int32> (coordinates.second))
        , playerID(static_cast <sf::Int32> (_playerID))
    {}
    Packet_Player()
    {}
    ~Packet_Player();

    ///Variables
    sf::Int32 packetNumber; // to make sure to organize them in the right order
    sf::Int32 playerID;
    sf::Int32 coords_x;
    sf::Int32 coords_y;
#define BYTES_PLAYER 20 //4*4 bytes + 4 bytes(header)
};

static sf::Packet& operator << (sf::Packet& packet, const Packet_Player& player)
{
    packet << static_cast <sf::Int32> (pkt::Header::player);
    packet << player.packetNumber;

    packet << player.playerID;
    packet << player.coords_x;
    packet << player.coords_y;

    return packet;
}

static sf::Packet& operator >> (sf::Packet& packet, Packet_Player& player)
{
    packet >> player.packetNumber;

    packet >> player.playerID;
    packet >> player.coords_x;
    packet >> player.coords_y;

    return packet;
}
//}


//{PacketContainer_Player

struct PacketContainer_Player : public Packet
{
    PacketContainer_Player(int _packetNumber):
        byteCount(0)
        , packetNumber(static_cast <sf::Int32> (_packetNumber))
    {}
    ~PacketContainer_Player() {}

    ///Variables
    sf::Int32 packetNumber;

    bool add(const Packet_Player& player)
    {
        int bytes_container = BYTES_PLAYER + 4;

        //450 bytes per pack max
        if((bytes_container + byteCount) < 450) // +4 (container size)
        {
            byteCount += bytes_container;
            playerContainer.push_back(player);
            return true;
        }
        return false;
    }

    std::vector <Packet_Player> playerContainer;
    int byteCount;
};

static sf::Packet& operator << (sf::Packet& packet, const PacketContainer_Player& packetContainer)
{
    packet << static_cast <sf::Int32> (pkt::Header::playerContainer);
    packet << packetContainer.packetNumber;

    packet << packetContainer.playerContainer.size();

    for(int it = 0; it != packetContainer.playerContainer.size(); it++)
    {
        packet << packetContainer.playerContainer[it].playerID;
        packet << packetContainer.playerContainer[it].coords_x;
        packet << packetContainer.playerContainer[it].coords_y;
    }
    return packet;
}

static sf::Packet& operator >> (sf::Packet& packet, PacketContainer_Player& packetContainer)
{
    int packetNumber;
    packet >> packetContainer.packetNumber;

    int packetCount;
    packet >> packetCount;

    int playerID;
    int coords_x;
    int coords_y;

    for(int it = 0; it != packetCount; it++)
    {
        packet >> playerID;
        packet >> coords_x;
        packet >> coords_y;
        packetContainer.add(Packet_Player(std::make_pair(coords_x, coords_y), playerID));
    }
    return packet;
}
//}


#endif // PACKET_PLAYER_H
