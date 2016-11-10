#include "EntityManager/EntityManager.h"

/// declaration of Entity Bases
#include "Entity.h"
#include "Entity_Obj/Entity_Obj.h"
#include "Entity_Coll.h"
#include "Entity_Living.h"
#include "Entity_Player.h"

/// declaration of Derived Entities
//Entity_Obj
#include "Entity_Orb.h"

EntityManager::EntityManager(ResourceManager& _resourceManager):
    resourceManager(_resourceManager)
{
    std::cout<<"DEBUG: Entity Manager Initialized"<<std::endl;

    {
        std::shared_ptr<Entity_Orb> entity = std::make_shared<Entity_Orb> (getNewID(), *this, resourceManager, utl::Vector2f(500,500));

        entities.push_back(entity);
        entities_Obj.push_back(entity);
        ids.push_back(entity->getId());
    }

    {
        std::shared_ptr<Entity_Player> entity = std::make_shared<Entity_Player> (getNewID(), *this, resourceManager);

        entities.push_back(entity);
        entities_Obj.push_back(entity);
        entities_Coll.push_back(entity);
        entities_Living.push_back(entity);
        entities_Player.push_back(entity);
        ids.push_back(entity->getId());
    }
}

EntityManager::~EntityManager()
{
    for (auto& id : ids)
    {
        killEntity(id);
    }
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

Entity_Player& EntityManager::getPlayer(const unsigned int& playerID)
{
    return *entities_Player.front();
}

unsigned int EntityManager::getNewID()
{
    if(idCounter < 4292967295)
    {
        return (idCounter++);
    }
    //game can run a year straight spawning 136 entities per second before need for restart
    //reason why - simplifies networking
    throw std::runtime_error("ENTITYMANAGER: Out of ID's");
}

void EntityManager::killEntity(const unsigned int& id)
{
    removeID(id, entities);
    removeID(id, entities_Obj);
    removeID(id, entities_Coll);
    removeID(id, entities_Living);
    removeID(id, entities_Player);
    ids.remove(id);
    std::cout << "ENTITYMANAGER: Killed ID - " << id << std::endl;
}
