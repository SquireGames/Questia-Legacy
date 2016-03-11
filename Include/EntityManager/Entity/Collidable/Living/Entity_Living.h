#ifndef ENTITY_LIVING_H
#define ENTITY_LIVING_H

#include "EntityManager/Entity/Collidable/Entity_Collidable.h"

class Entity_Living : public Entity_Collidable
{
public:
    Entity_Living();
    virtual int getHP() = 0;
    virtual int getMP() = 0;
    virtual int getST() = 0;
    virtual int getMaxHP() = 0;
    virtual int getMaxMP() = 0;

    virtual void setHP(int HP) = 0;
    virtual void setMP(int MP) = 0;
    virtual void setST(int ST) = 0;

    virtual std::string getName() = 0;
    virtual std::string getEntityType() = 0;
    virtual int getType() = 0;

    virtual void getNumb(int a, sf::Vector2i b) = 0;


protected:
private:
    int hp,mp,stamina;
    int maxHP, maxMP, maxST;
};

#endif // ENTITY_LIVING_H


