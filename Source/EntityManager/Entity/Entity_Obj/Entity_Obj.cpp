#include "Entity_Obj/Entity_Obj.h"

Entity_Obj::Entity_Obj(int id, EntityManager& entityManager, ResourceManager& _resourceManager):
    Entity(id, entityManager)
    , resourceManager(_resourceManager)
{
    //ctor
}

Entity_Obj::~Entity_Obj()
{
    //dtor
}

void Entity_Obj::draw(sf::RenderWindow& window, const DrawLayer& drawLayer)
{

}
