#include "Entity_Coll.h"

Entity_Coll::Entity_Coll(int id, EntityManager& entityManager, ResourceManager& resourceManager, Bounds _bounds):
    Entity_Obj(id, entityManager, resourceManager)
    , bounds(_bounds)
{
    //ctor
}

Entity_Coll::~Entity_Coll()
{
    //dtor
}
