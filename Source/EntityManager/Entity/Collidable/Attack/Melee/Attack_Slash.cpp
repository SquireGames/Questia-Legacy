#include "Attack_Slash.h"
#include <iostream>

Attack_Slash::Attack_Slash( ResourceManager &res, int _attackID,int _attackerID, std::string _attackerName,
                            sf::Vector2f _coordinates, sf::Vector2f _velocity, float _angle,
                            int _duration, int _attackDamage, float _sizeMultiplier, float _timeMultiplier,
                            int _extra):
    coordinates(_coordinates)
    , velocity(_velocity)
    , attackID(_attackID)
    , attackerName(_attackerName)
    , attackerID (_attackerID)
    , duration(_duration)
    , initDuration(_duration)
    , attackDamage(_attackDamage)
    , sizeMultiplier(_sizeMultiplier)
    , timeMultiplier(_timeMultiplier)
    , extra(_extra)

    , angle(_angle)

    , res(res)
{
    angle = fixAngle(angle);

    entitySprite.setTexture(res.getTexture("Media/Image/Game/Items/Weapons/Shared/Sword/Club/sword_club.png"));
    entitySprite.setTextureRect(sf::IntRect(0, 35, 7, -35));
    entitySprite.setOrigin(3.5,0); //set the origin to the middle of the attack
    entitySprite.setRotation(angle - 180);
    entitySprite.rotate(-45);

    angle = convertDegreesToRadians(angle);
    angleDifference = convertDegreesToRadians(90) / duration;

    hitbox_Attack.push_back(sf::Vector2f(-3.5,-35));
    hitbox_Attack.push_back(sf::Vector2f(3.5,-35));
    hitbox_Attack.push_back(sf::Vector2f(3.5,0));
    hitbox_Attack.push_back(sf::Vector2f(-3.5,0));

    rotateNewPoints(angle, coordinates, hitbox_Attack); // rotate around axis, add coordinates
    rotatePoints(convertDegreesToRadians(-45), coordinates, hitbox_Attack); // Rewind attack
    movePoints(angle, coordinates, sf::Vector2f(10,10), hitbox_Attack); // Starting point
}

bool Attack_Slash::checkCollision(sf::Vector2f entityCoordinates, sf::Vector2f sideRadius)
{
    std::vector<sf::Vector2f> hitbox_Target;

    hitbox_Target.push_back(sf::Vector2f(entityCoordinates.x-sideRadius.x,entityCoordinates.y-sideRadius.y));
    hitbox_Target.push_back(sf::Vector2f(entityCoordinates.x+sideRadius.x,entityCoordinates.y-sideRadius.y));
    hitbox_Target.push_back(sf::Vector2f(entityCoordinates.x-sideRadius.x,entityCoordinates.y+sideRadius.y));
    hitbox_Target.push_back(sf::Vector2f(entityCoordinates.x+sideRadius.x,entityCoordinates.y+sideRadius.y));

    return check_Collision_SAT(hitbox_Attack, hitbox_Target);
}

void Attack_Slash::drawEntity(sf::RenderWindow &window)
{

}
void Attack_Slash::drawLayer2(sf::RenderWindow &window)
{
    entitySprite.setPosition(coordinates);
    window.draw(entitySprite);
}


void Attack_Slash::update(int effect, int (&returnCollision)[4])
{

}
sf::Vector2f Attack_Slash::getSideRadius()
{
    //TEMP
    return sf::Vector2f(0,0);//sideRadiusAttack;
}
sf::Vector2f Attack_Slash::getVelocity()
{
    return velocity;
}
sf::Vector2f Attack_Slash::getCoordinates()
{
    return coordinates;
}
sf::Vector2i Attack_Slash::getMapCoordinates()
{
    return mapCoordinates;
}

bool Attack_Slash::isActive()
{
    duration--;
    if(duration==0)
    {
        return false;
    }

    rotatePoints(angleDifference, coordinates, hitbox_Attack);
    entitySprite.rotate(convertRadiansToDegrees(angleDifference));
    return true;
}
void Attack_Slash::update(sf::Vector2f coords)
{
    for(unsigned int x = 0; x != hitbox_Attack.size(); x++)
    {
        hitbox_Attack[x].x = hitbox_Attack[x].x - coordinates.x + coords.x;
        hitbox_Attack[x].y = hitbox_Attack[x].y - coordinates.y + coords.y;
    }
    coordinates = coords;
}
int Attack_Slash::getDamage(int ID)
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
        return 11;
    }
    else
    {
        return 0;
    }
}
std::string Attack_Slash::getAttacker()
{
    return attackerName;
}
int Attack_Slash::returnID()
{
    return attackID;
}

