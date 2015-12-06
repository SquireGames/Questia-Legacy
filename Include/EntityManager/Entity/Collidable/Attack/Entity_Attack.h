#ifndef ENTITY_ATTACK_H
#define ENTITY_ATTACK_H

#include <EntityManager/Entity/Collidable/Entity_Collidable.h>
#include <EntityManager/Entity/Collidable/Living/Entity_Living.h>


class Entity_Attack : public Entity_Collidable
{
public:
    Entity_Attack();
    ~Entity_Attack();

    virtual bool checkCollision(sf::Vector2f coordinates, sf::Vector2f sideRadius) = 0;
    virtual bool isActive() = 0;
    virtual void update(sf::Vector2f coords) = 0;
    virtual int getDamage(int ID) = 0;

    virtual std::string getAttacker() = 0;
    virtual int getAttackerID() = 0;

    virtual void drawLayer2(sf::RenderWindow &mWindow) = 0;

    float fixAngle(float& angle);
    float convertDegreesToRadians(float angle);
    float convertRadiansToDegrees(float angle);

    void rotatePoints(float angle, sf::Vector2f coordinates, std::vector<sf::Vector2f>& _point);
    void rotateNewPoints(float angle, sf::Vector2f coordinates, std::vector<sf::Vector2f>& _point);
    void movePoints(float angle, sf::Vector2f& coordinates, sf::Vector2f velocity, std::vector<sf::Vector2f>& _point);

protected:
private:

};

#endif // ENTITY_ATTACK_H
