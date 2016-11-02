#ifndef ENTITY_H
#define ENTITY_H

#include "EntityManager.h"

class Entity
{
public:
    Entity(int _id, EntityManager& _entityManager);
    virtual ~Entity() = 0;

    virtual void update();

    int getId();

protected:
    EntityManager& entityManager;

private:
    int id;
};

#endif // ENTITY_H
