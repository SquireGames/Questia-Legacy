#include "Entity_Coll.h"

Entity_Coll::Entity_Coll(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager, Bounds _collBounds, Bounds _hitBounds):
    Entity_Obj(id, entityManager, resourceManager)
    , collBounds(_collBounds)
    , hitBounds(_hitBounds)
{
    //ctor
}

Entity_Coll::~Entity_Coll()
{
    //dtor
}

void Entity_Coll::attemptMove(const utl::Vector2f velocity, Entity_Coll& entity)
{

}

void Entity_Coll::forceMove(const utl::Vector2f velocity, Entity_Coll& entity)
{
    entity.coords += velocity;
}
