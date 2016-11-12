#ifndef ENTITY_COLL_H
#define ENTITY_COLL_H

#include "Entity_Obj/Entity_Obj.h"
#include "Bounds.h"

class Entity_Coll : public Entity_Obj
{
public:
    Entity_Coll(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager, Bounds _bounds, Bounds _hitBounds);

    virtual ~Entity_Coll() = 0;

    void attemptMove(const utl::Vector2f velocity, Entity_Coll& entity);
    void forceMove(const utl::Vector2f velocity, Entity_Coll& entity);

    void onCollision(Entity_Coll& other);

    Bounds collBounds;
    Bounds hitBounds;

    bool isPermeable = true;
    bool isSolid     = true;

protected:
    virtual void onCollision(std::map <Type, Type_Field>& atrs, const unsigned int& entityID);
};

#endif // ENTITY_COLL_H
