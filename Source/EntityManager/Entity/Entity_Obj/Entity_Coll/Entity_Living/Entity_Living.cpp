#include "Entity_Living.h"

Entity_Living::Entity_Living(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager, Bounds collBounds, Bounds hitBounds):
    Entity_Coll(id, entityManager, resourceManager, collBounds, hitBounds)
{
    //ctor
}

Entity_Living::~Entity_Living()
{
    //dtor
}
