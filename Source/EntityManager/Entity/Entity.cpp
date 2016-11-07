#include "Entity.h"

Entity::Entity(unsigned int _id, EntityManager& _entityManager):
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

unsigned int Entity::getId()
{
    return id;
}
