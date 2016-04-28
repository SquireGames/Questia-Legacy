#ifndef PACKET_PLAYER_H
#define PACKET_PLAYER_H

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

struct Packet_Player
{
    Packet_Player(std::pair <float, float> coordinates, int _packetNumber):
        coords_x(static_cast <sf::Int32> (coordinates.first))
        , coords_y(static_cast <sf::Int32> (coordinates.second))
        , packetNumber(static_cast <sf::Int32> (_packetNumber))
    {}
    ~Packet_Player();

    sf::Int32 coords_x;
    sf::Int32 coords_y;

    sf::Int32 packetNumber; // to make sure to organize them in the right order

    sf::Int32 playerID;
};

sf::Packet& operator >> (sf::Packet& packet, const Packet_Player& player)
{
    return packet << player.coords_x << player.coords_y << player.packetNumber;
}

sf::Packet& operator >> (sf::Packet& packet, Packet_Player& player)
{
    return packet >> player.coords_x >> player.coords_y >> player.packetNumber;
}

#endif // PACKET_PLAYER_H
