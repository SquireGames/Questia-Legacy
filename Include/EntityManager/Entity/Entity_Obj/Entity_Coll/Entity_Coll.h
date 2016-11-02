#ifndef ENTITY_COLL_H
#define ENTITY_COLL_H

#include "Entity_Obj/Entity_Obj.h"
#include "Bounds.h"

class Entity_Coll : public Entity_Obj
{
public:
    Entity_Coll(int id, EntityManager& entityManager, ResourceManager& resourceManager, Bounds _bounds);
    virtual ~Entity_Coll() = 0;

    Bounds bounds;

    bool isPermeable = true;
    bool isSolid     = true;
};

#endif // ENTITY_COLL_H
