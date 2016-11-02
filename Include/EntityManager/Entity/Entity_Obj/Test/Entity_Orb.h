#ifndef ENTITY_ORB_H
#define ENTITY_ORB_H

#include "Entity_Obj/Entity_Obj.h"

class Entity_Orb : public Entity_Obj
{
    public:
        Entity_Orb(int id, EntityManager& entityManager, ResourceManager& resourceManager);
        ~Entity_Orb();

        void draw(sf::RenderWindow& window, const DrawLayer& drawLayer);
    private:
};

#endif // ENTITY_ORB_H
