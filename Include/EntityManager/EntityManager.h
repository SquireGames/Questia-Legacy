#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <list>
#include <memory> //std::shared_ptr

#include <iostream>

#include <SFML/Graphics.hpp>

#include "ResourceManager.h"
#include "DrawLayer.h"

#include "Bounds.h"

//forward declaration for stored classes
class Entity;
class Entity_Obj;
class Entity_Coll;
class Entity_Living;
class Entity_Player;

class EntityManager
{
public:
    EntityManager(ResourceManager& _resourceManager);
    ~EntityManager();

    void update();
    void draw(sf::RenderWindow& window, const DrawLayer& drawLayer);
    void draw_coll(sf::RenderWindow& window);

    Entity_Player& getPlayer(const unsigned int& playerID);

    unsigned int getNewID();
    void killEntity(const unsigned int& id);

    void queueKill(const unsigned int& id);

private:
    ResourceManager& resourceManager;

    unsigned int idCounter = 0;

    std::vector <std::shared_ptr<Entity> >        entities;
    std::vector <std::shared_ptr<Entity_Obj> >    entities_Obj;
    std::vector <std::shared_ptr<Entity_Coll> >   entities_Coll;
    std::vector <std::shared_ptr<Entity_Living> > entities_Living;
    std::vector <std::shared_ptr<Entity_Player> > entities_Player;

    std::list <unsigned int> ids;
    std::vector <unsigned int> deadIDs;

    template <class T> void removeID(const unsigned int& id, std::vector<T>& entityVector)
    {
        auto iter = entityVector.end();
        for(auto it = entityVector.begin(); it != entityVector.end(); it++)
        {
            if(id == (*it)->getID())
            {
                iter = it;
                break;
            }
        }
        if(iter != entityVector.end())
        {
            entityVector.erase(iter);
        }
    }
};

#endif // ENTITYMANAGER_H
