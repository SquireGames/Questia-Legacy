#ifndef HOSTILE_GOBLIN_H
#define HOSTILE_GOBLIN_H

#include "EntityManager/Entity/Collidable/Living/Entity_Living.h"
#include "ResourceManager.h"
#include "EntityManager/EntityManager.h"

class Hostile_Goblin : public Entity_Living
{
public:
    Hostile_Goblin(ResourceManager &res,EntityManager &entityManager, sf::Vector2f coordinates, int ID, std::string _entityType);

    ///default
    void drawEntity(sf::RenderWindow &mWindow);
    void update(int effect, int (&returnCollision)[4]);

    ///gets
    int returnID();
    std::string getName();
    int getType();
    sf::Vector2f getSideRadius();
    sf::Vector2f getVelocity();
    sf::Vector2f getCoordinates();
    sf::Vector2i getMapCoordinates();
    int getHP(){return hp;}
    int getMP(){return mp;}
    int getST(){return stamina;}
    int getMaxHP(){return maxHP;}
    int getMaxMP(){return maxMP;}
    int getMaxST(){return maxST;}
    std::string getEntityType(){return entityType;}

    ///sets
    void getNumb(int distance, sf::Vector2i  entityCoords);
    void setHP(int HP){hp = HP;}
    void setMP(int MP){mp = MP;}
    void setST(int ST){stamina = ST;}
    void setCoordinates(sf::Vector2f coords) {coordinates = coords;}

private:
    ///default
    std::string entityType;

    int ID;
    sf::Sprite entitySprite;
    sf::Sprite entitySprite_HP;
    sf::Vector2f coordinates;
    sf::Vector2i mapCoordinates;
    sf::Vector2f sideRadius;
    sf::Vector2f velocity;

    ///timing
    unsigned short tick;
    unsigned short count_entityStep;
    unsigned short entityStep;
    unsigned short stateDuration;
    unsigned short cooldown;


    ///stats
    int hp;
    int maxHP;
    int mp;
    int maxMP;
    int stamina;
    int maxST;

    ///AI
    unsigned short direction;
    enum entitystate{passive, ranged, melee, charge, dodge, run};
    entitystate entityState;

    ///references
    ResourceManager &res;
    EntityManager& entityManager;
};

#endif // HOSTILE_GOBLIN_H
