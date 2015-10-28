#ifndef ENTITY_COLLIDABLE_H
#define ENTITY_COLLIDABLE_H

#include "EntityManager/Entity.h"
#include <SFML/Graphics/Vertex.hpp>

class Entity_Collidable : public Entity
{
public:
    Entity_Collidable();
    ~Entity_Collidable();

    virtual sf::Vector2f getSideRadius() = 0;
    virtual sf::Vector2f getVelocity() = 0;
    virtual sf::Vector2i getMapCoordinates() = 0;

    virtual void setCoordinates(sf::Vector2f coords) = 0;

    bool check_Collision_SAT(std::vector<sf::Vector2f>& objectVector_1, std::vector<sf::Vector2f>& objectVector_2);


protected:
    sf::Vector2f velocity;
private:
};

#endif // ENTITY_COLLIDABLE_H
