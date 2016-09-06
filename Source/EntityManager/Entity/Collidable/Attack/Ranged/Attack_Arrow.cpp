#include "Attack_Arrow.h"
#include <iostream>

Attack_Arrow::Attack_Arrow( ResourceManager &res, EntityManager &entityManager, int _attackID, int _attackerID, std::string _attackerName,
                            sf::Vector2f _coordinates, sf::Vector2f _velocity, float _angle,
                            int _duration, int _attackDamage, float _sizeMultiplier, float _timeMultiplier,
                            int _extra):
    attackID(_attackID)
    , attackerName(_attackerName)
    , coordinates(_coordinates)
    , velocity(_velocity)
    , duration(_duration)
    , attackDamage(_attackDamage)
    , sizeMultiplier(_sizeMultiplier)
    , timeMultiplier(_timeMultiplier)
    , extra(_extra)
    , attackerID (_attackerID)
    , angle(_angle)

    , res(res)
    , entityManager(entityManager)

{
    angle = fixAngle(angle);

    entitySprite.setTexture(res.getTexture("Media/Image/Game/Items/Weapons/Shared/Arrow/Basic/Arrow.png"));
    entitySprite.setOrigin(2,10); //set the origin to the middle of the attack
    entitySprite.setRotation(angle);

    angle = convertDegreesToRadians(angle);

    hitbox_Attack.push_back(sf::Vector2f(-2, 10));
    hitbox_Attack.push_back(sf::Vector2f(2, 10));
    hitbox_Attack.push_back(sf::Vector2f(2, -10));
    hitbox_Attack.push_back(sf::Vector2f(-2, -10));

    rotateNewPoints(angle, coordinates, hitbox_Attack);

    //offset
    //movePoints(convertDegreesToRadians(0), coordinates, sf::Vector2f(10,10), hitbox_Attack);     // Up
    movePoints(angle, coordinates, sf::Vector2f(10,10), hitbox_Attack); // Distance
}

bool Attack_Arrow::checkCollision(sf::Vector2f entityCoordinates, sf::Vector2f sideRadius)
{
    std::vector<sf::Vector2f> hitbox_Target;

    hitbox_Target.push_back(sf::Vector2f(entityCoordinates.x-sideRadius.x,entityCoordinates.y-sideRadius.y));
    hitbox_Target.push_back(sf::Vector2f(entityCoordinates.x+sideRadius.x,entityCoordinates.y-sideRadius.y));
    hitbox_Target.push_back(sf::Vector2f(entityCoordinates.x-sideRadius.x,entityCoordinates.y+sideRadius.y));
    hitbox_Target.push_back(sf::Vector2f(entityCoordinates.x+sideRadius.x,entityCoordinates.y+sideRadius.y));

    return check_Collision_SAT(hitbox_Attack, hitbox_Target);
}

void Attack_Arrow::drawEntity(sf::RenderWindow &window)
{

}

void  Attack_Arrow::drawLayer2(sf::RenderWindow &window)
{
    entitySprite.setPosition(coordinates);
    window.draw(entitySprite);
}

void Attack_Arrow::update(int effect, int (&returnCollision)[4])
{
    if(returnCollision[0] + returnCollision[1] + returnCollision[2]+ returnCollision[3] != 0)
    {
        entityManager.destroyEntity(attackID);
    }
}

bool Attack_Arrow::isActive()
{
    duration--;
    if(duration==0)
    {
        return false;
    }

    movePoints(angle, coordinates, velocity, hitbox_Attack);
    return true;
}
void Attack_Arrow::update(sf::Vector2f coords)
{

}
int Attack_Arrow::getDamage(int ID)
{
    bool pass = true;

    for(unsigned int x = 0; x < entityIDList.size(); x++)
    {
        if(ID == entityIDList[x])
        {
            pass = false;
        }
    }

    if(pass)
    {
        entityIDList.push_back(ID);
        return 5;
    }
    else
    {
        return 0;
    }
}

std::string Attack_Arrow::getAttacker()
{
    return attackerName;
}
sf::Vector2f Attack_Arrow::getSideRadius()
{
    return sf::Vector2f(2,10);
}
sf::Vector2f Attack_Arrow::getVelocity()
{
    return velocity;
}
sf::Vector2f Attack_Arrow::getCoordinates()
{
    return coordinates;
}
sf::Vector2i Attack_Arrow::getMapCoordinates()
{
    mapCoordinates.x = (int)coordinates.x/32 + 1;
    mapCoordinates.y = (int)coordinates.y/32 + 1;

    return mapCoordinates;
}
int Attack_Arrow::returnID()
{
    return attackID;
}
