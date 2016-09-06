#ifndef ENTITY_CHICKEN_H
#define ENTITY_CHICKEN_H

#include "EntityManager/Entity/Collidable/Living/Entity_Living.h"
#include "ResourceManager.h"
#include "EntityManager/EntityManager.h"

class Entity_Chicken : public Entity_Living
{
public:
    Entity_Chicken(ResourceManager &res,EntityManager &entityManager, sf::Vector2f coordinates, int ID, std::string _entityType);

    sf::Vector2f getSideRadius();
    sf::Vector2f getVelocity();
    sf::Vector2f getCoordinates();
    sf::Vector2i getMapCoordinates();

    void drawEntity(sf::RenderWindow &window);
    void update(int effect, int (&returnCollision)[4]);
    int returnID();

    void saveEntity() {};

    std::string getName();
    void getNumb(int a, sf::Vector2i  b);
    std::string getEntityType(){return entityType;}
    EntityCategory getCategory(){return EntityCategory::passive;}

    void setCoordinates(sf::Vector2f coords) {coordinates = coords;}

    int ID;

private:
    std::string entityType;

    int hp;
    int mp;
    int stamina;

    int maxHP;
    int maxMP;
    int maxST;

    sf::Sprite entitySprite_HP;
    sf::Texture entityTexture_HP;

    sf::Vector2f coordinates;
    sf::Vector2i mapCoordinates;
    sf::Sprite entitySprite;

    sf::Vector2f sideRadius;
    sf::Vector2f velocity;

    sf::Texture entityTexture_up;
    sf::Texture entityTexture_upRight;
    sf::Texture entityTexture_upLeft;
    sf::Texture entityTexture_right;
    sf::Texture entityTexture_left;
    sf::Texture entityTexture_downRight;
    sf::Texture entityTexture_downLeft;
    sf::Texture entityTexture_down;

    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;

    int AIInt;

public:

    int getHP()
    {
        return hp;
    }
    int getMP()
    {
        return mp;
    }
    int getST()
    {
        return stamina;
    }
    int getMaxHP()
    {
        return maxHP;
    }
    int getMaxMP()
    {
        return maxMP;
    }
    int getMaxST()
    {
        return maxST;
    }

    void setHP(int HP)
    {
        hp = HP;
    }
    void setMP(int MP)
    {
        mp = MP;
    }
    void setST(int ST)
    {
        stamina = ST;
    }
    ResourceManager &res;
    EntityManager& entityManager;
};

#endif // ENTITY_CHICKEN_H
