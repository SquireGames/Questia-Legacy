#include "Entity.h"

Entity::Entity(int _id, EntityManager& _entityManager):
    id(_id)
    , entityManager(_entityManager)
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}

void Entity::update()
{

}

int Entity::getId()
{
    return id;
}
