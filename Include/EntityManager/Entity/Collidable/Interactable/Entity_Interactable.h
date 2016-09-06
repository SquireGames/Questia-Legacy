#ifndef ENTITY_INTERACTABLE_H
#define ENTITY_INTERACTABLE_H

#include "EntityManager/Entity/Collidable/Entity_Collidable.h"
#include <SFML/Graphics.hpp>


class Entity_Interactable : public Entity_Collidable
{
public:
    Entity_Interactable();
    ~Entity_Interactable();

    virtual void checkInteraction(int x, int y,int sideRadius_x, int sideRadius_y) = 0;
    virtual void drawLayer3(sf::RenderWindow &window) = 0;

protected:
private:
};


#endif // ENTITY_INTERACTABLE_H
