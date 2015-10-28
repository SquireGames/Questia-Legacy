#ifndef ENTITY_PLAYABLE_H
#define ENTITY_PLAYABLE_H

#include "EntityManager/Entity/Collidable/Living/Entity_Living.h"
#include <SFML/Graphics.hpp>

class Entity_Playable : public Entity_Living
{
public:
    virtual void handleImput(int actionType, bool isPressed) = 0;
    virtual void setAngleToMouse(float angle) = 0;
    virtual void setMouseCoordinates(sf::Vector2f mouseCoordinates) = 0;
    virtual std::tuple<int, int, int, int, int, int> getStats() = 0;
    virtual unsigned char getClass() = 0;
};

#endif // ENTITY_PLAYABLE_H


