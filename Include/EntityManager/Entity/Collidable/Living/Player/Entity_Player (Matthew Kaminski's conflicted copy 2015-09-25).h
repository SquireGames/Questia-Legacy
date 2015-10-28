#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

#include <SFML/Graphics.hpp>
#include <tuple>

#include "EntityManager/Entity/Collidable/Living/Player/Entity_Playable.h"
#include "ResourceManager.h"
#include "EntityManager/EntityManager.h"


class Entity_Player : public Entity_Playable
{
public:
    Entity_Player(ResourceManager &res,EntityManager &entityManager, sf::Vector2f coordinates, int ID);
    ~Entity_Player();

    ///default
    void drawEntity(sf::RenderWindow &mWindow);
    void handleImput(int actionType, bool isPressed);
    void update(int effect, int (&returnCollision)[4]);

    ///get's
    int returnID();
    std::string getName();
    void getNumb(int a, sf::Vector2i entityCoords);
    int getType();
    sf::Vector2f getCoordinates();
    sf::Vector2i getMapCoordinates();
    sf::Vector2f getSideRadius();
    sf::Vector2f getVelocity();
    std::tuple<int, int, int, int, int, int> getStats();
    int getHP(){return hp;}
    int getMP(){return mp;}
    int getST(){return stamina;}
    int getMaxHP(){return maxHP;}
    int getMaxMP(){return maxMP;}
    int getMaxST(){return maxST;}

    ///set's
    void setAngleToMouse(float angle);
    void setMouseCoordinates(sf::Vector2f gottenMouseCoordinates);
    void setHP(int HP){hp = HP;}
    void setMP(int MP){mp = MP;}
    void setST(int ST){stamina = ST;}
    void setCoordinates(sf::Vector2f coords) {coordinates = coords;}

    ///temp server crap
    int getPlayerStep(){return playerStep;}

private:
    ///default
    int ID;
    sf::Sprite entitySprite_HP;
    sf::Sprite entitySprite;
    sf::Vector2f coordinates;
    sf::Vector2i mapCoordinates;
    sf::Vector2f mouseCoordinates;
    float angleToMouse;
    sf::Vector2f velocity;
    const sf::Vector2f sideRadius;

    ///timing
    unsigned short tick;

    ///stats
    int hp;
    int maxHP;
    int mp;
    int maxMP;
    int stamina;
    int maxST;

    ///animation
    int count_playerStep;
    int playerStep;
    float previousVelocity;

    ///controls
    bool shiftIsPressed;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;

    ///temp running
    bool wasRunning;
    int runningTick;

    ///references
    ResourceManager &res;
    EntityManager& entityManager;
};

#endif // ENTITY_PLAYER_H
