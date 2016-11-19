#include "Entity_Living.h"

Entity_Living::Entity_Living(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager, Bounds collBounds, Bounds hitBounds, utl::Vector2f origin):
    Entity_Coll(id, entityManager, resourceManager, collBounds, hitBounds, origin)
{
    //ctor
}

Entity_Living::~Entity_Living()
{
    //dtor
}
