#ifndef PACKET_ENTITY_H
#define PACKET_ENTITY_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Packet.h"

struct Packet_Entity : public Packet
{
    Packet_Entity();
    ~Packet_Entity();
};

static sf::Packet& operator << (sf::Packet& packet, const Packet_Entity& player)
{

}

static sf::Packet& operator >> (sf::Packet& packet, Packet_Entity& player)
{

}

#endif // PACKET_ENTITY_H
