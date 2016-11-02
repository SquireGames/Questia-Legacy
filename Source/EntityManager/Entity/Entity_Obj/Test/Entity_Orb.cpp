#include "Entity_Orb.h"

Entity_Orb::Entity_Orb(int id, EntityManager& entityManager, ResourceManager& resourceManager):
    Entity_Obj(id, entityManager, resourceManager)
{
    //ctor
}

Entity_Orb::~Entity_Orb()
{
    //dtor
}

void Entity_Orb::draw(sf::RenderWindow& window, const DrawLayer& drawLayer)
{

}

