#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

#include "Entity_Living.h"

#include "KeyAction.h"

class Entity_Player : public Entity_Living
{
public:
    Entity_Player(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager, Bounds collBounds, Bounds hitBounds);
    ~Entity_Player();

    int exp_gen = 0;

    //TODO new input system
    void processInput(ctr::KeyAction action, bool isPressed);
};

#endif // ENTITY_PLAYER_H
