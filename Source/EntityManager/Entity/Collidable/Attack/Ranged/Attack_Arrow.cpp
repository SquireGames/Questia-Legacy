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
    entitySprite.setTexture(res.getTexture("Media/Image/Game/Attacks/Ranged/Arrow.png"));
    angle = fixAngle(angle);

    //set the origin to the middle of the attack
    entitySprite.setOrigin(2,10);
    entitySprite.setRotation(angle);

    angle = convertDegreesToRadians(angle);

    hitbox_Attack.push_back(sf::Vector2f(-2, 10));
    hitbox_Attack.push_back(sf::Vector2f(2, 10));
    hitbox_Attack.push_back(sf::Vector2f(2, -10));
    hitbox_Attack.push_back(sf::Vector2f(-2, -10));

    for(int it = 0; it != hitbox_Attack.size(); it++)
    {
        float sin = std::sin(angle);
        float cos = std::cos(angle);

        float x,y;

        x = hitbox_Attack[it].x * cos - hitbox_Attack[it].y * sin;
        y = hitbox_Attack[it].x * sin + hitbox_Attack[it].y * cos;

        hitbox_Attack[it].x =  x + coordinates.x;
        hitbox_Attack[it].y =  y + coordinates.y;
    }
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

int Attack_Arrow::returnID()
{
    return attackID;
}

void Attack_Arrow::drawEntity(sf::RenderWindow &mWindow)
{

}

void  Attack_Arrow::drawLayer2(sf::RenderWindow &mWindow)
{
    entitySprite.setPosition(coordinates);
    mWindow.draw(entitySprite);
    /*
    for(int it = 0; it != 4; it++)
    {
        mWindow.draw(circleAttack[it]);
        mWindow.draw(circleTarget[it]);
        mWindow.draw(rectTarget[it]);
        mWindow.draw(rectAttack[it]);
    }
    */
}

void Attack_Arrow::update(int effect, int (&returnCollision)[4])
{
    if(returnCollision[0] + returnCollision[1] + returnCollision[2]+ returnCollision[3] != 0)
    {
        entityManager.destroyEntity(attackID);
    }

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

bool Attack_Arrow::isActive()
{
    duration--;
    if(duration==0)
    {
        return false;
    }

    float x_component, y_component;

    x_component = std::cos(angle - (.5 * 3.14159)) * velocity.x;
    y_component = std::sin(angle - (.5 * 3.14159)) * velocity.x;

    coordinates.x += x_component;
    coordinates.y += y_component;

    for(int x = 0; x <= 3; x++)
    {
        hitbox_Attack[x].x = hitbox_Attack[x].x + x_component;
        hitbox_Attack[x].y = hitbox_Attack[x].y + y_component;
    }
    return true;
}
void Attack_Arrow::update(sf::Vector2f coords)
{

}
int Attack_Arrow::getDamage(int ID)
{
    bool pass = true;

    for(int x = 0; x < entityIDList.size(); x++)
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

