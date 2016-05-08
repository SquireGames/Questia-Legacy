#ifndef ENTITY_LIVING_H
#define ENTITY_LIVING_H

#include "EntityManager/Entity/Collidable/Entity_Collidable.h"

enum class EntityCategory {passive, hostile, player};

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

    virtual std::string getName() = 0;          // Death message, log
    virtual std::string getEntityType() = 0;    // Entity spawn name
    virtual EntityCategory getCategory() = 0;   // hostile, passive, player...


    std::string getCharacteristic(std::string characteristic)
    {
        for(std::map<std::string, std::string>::iterator it = saveCharacteristics.begin(); it!=saveCharacteristics.end(); ++it)
        {
            if(characteristic == it->first)
            {
                return it->second;
            }
        }
    }

    void setCharacteristics(std::string characteristic, std::string value) // only use in init
    {
        saveCharacteristics[characteristic] = value;
    }

    std::map <std::string, std::string>& getSaveCharacteristics() {return saveCharacteristics;} // Needed to access map
    virtual void saveEntity() = 0;
    virtual void getNumb(int distance, sf::Vector2i entityCoords) = 0; // getting distance and coordinates from player

private:
    std::map <std::string, std::string> saveCharacteristics;
};

#endif // ENTITY_LIVING_H


