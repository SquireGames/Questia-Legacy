#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory> //std::shared_ptr

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceManager.h"
#include "DrawLayer.h"

//forward declaration for stored classes
class Entity;
class Entity_Obj;
class Entity_Coll;

class EntityManager
{
public:
    EntityManager(ResourceManager& _resourceManager);
    ~EntityManager();

    std::vector <std::shared_ptr<Entity> >      entities;
    std::vector <std::shared_ptr<Entity_Obj> >  entities_Obj;
    std::vector <std::shared_ptr<Entity_Coll> > entities_Coll;

    void update();
    void draw(sf::RenderWindow& window, const DrawLayer& drawLayer);

private:
    ResourceManager& resourceManager;
};

#endif // ENTITYMANAGER_H
