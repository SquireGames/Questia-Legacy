#include "EntityManager/EntityManager.h"

/// declaration of Entity Bases
#include "Entity.h"
#include "Entity_Obj/Entity_Obj.h"

/// declaration of Derived Entities
//Entity_Obj
#include "Entity_Orb.h"

EntityManager::EntityManager(ResourceManager& _resourceManager):
    resourceManager(_resourceManager)
{
    std::cout<<"DEBUG: Entity Manager Initialized"<<std::endl;

    std::shared_ptr<Entity_Orb> entity = std::make_shared<Entity_Orb> (1, *this, resourceManager);

    entities.push_back(entity);
    entities_Obj.push_back(entity);
}

EntityManager::~EntityManager()
{
    std::cout<<"DEBUG: Destroyed Entity Manager"<<std::endl;
}

void EntityManager::update()
{
    for(auto& entity : entities)
    {
        entity->update();
    }
}

void EntityManager::draw(sf::RenderWindow& window, const DrawLayer& drawLayer)
{
    // sort entities by y value
    // ...

    for(auto& entity : entities_Obj)
    {
        entity->draw(window, drawLayer);
    }
}

