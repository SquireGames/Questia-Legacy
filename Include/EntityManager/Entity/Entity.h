#ifndef ENTITY_H
#define ENTITY_H

#include "EntityManager.h"

class Entity
{
public:
    Entity(unsigned int _id, EntityManager& _entityManager);
    virtual ~Entity() = 0;

    virtual void update();

    unsigned int getId();
protected:
    EntityManager& entityManager;

private:
    unsigned int id;
};

#endif // ENTITY_H