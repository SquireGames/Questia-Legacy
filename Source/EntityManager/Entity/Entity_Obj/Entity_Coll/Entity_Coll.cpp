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
    //TODO add tilemap coll
    entity.coords += velocity;
}

void Entity_Coll::forceMove(const utl::Vector2f velocity, Entity_Coll& entity)
{
    entity.coords += velocity;
}

void Entity_Coll::onCollision(Entity_Coll& other)
{
    onCollision(other.atrs, other.getID());
}

void Entity_Coll::onCollision(std::map <Type, Type_Field>& atrs, const unsigned int& entityID)
{

}

