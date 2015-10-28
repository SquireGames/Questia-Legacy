#include "EntityManager/Entity/Collidable/Living/Hostile/Hostile_Goblin.h"

#include <iostream>
#include <sstream>

Hostile_Goblin::Hostile_Goblin( ResourceManager &res, EntityManager &entityManager,sf::Vector2f coordinates, int aID):
    coordinates(coordinates.x,coordinates.y)
    , ID(aID)
    , sideRadius(12.5, 12.5)
    , velocity(.75,.75)

    , hp(50)
    , mp(0)
    , stamina(50.f)
    , maxHP(50)
    , maxMP(0)
    , maxST(50)

    , entityManager(entityManager)
    , res(res)

    , tick (0)
    , cooldown(0)
    , stateDuration(288)
    , count_entityStep(0)

    , direction(0)
    , entityStep(1)

    , entityState(passive)
{
    entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Hostile/hostile_goblin.png"));
    entitySprite.setTextureRect(sf::IntRect(27,0,24,50));

    entitySprite_HP.setTexture(res.getTexture("Media/Image/Game/Gui/Health.png"));
}

void Hostile_Goblin::drawEntity(sf::RenderWindow &window)
{
    entitySprite.setPosition(coordinates.x-sideRadius.x, coordinates.y-sideRadius.y-25);
    window.draw(entitySprite);

    entitySprite_HP.setPosition(coordinates.x-sideRadius.x, coordinates.y-sideRadius.y-35);
    float HPP;
    HPP = (float)hp/(float)maxHP;
    entitySprite_HP.setTextureRect(sf::IntRect(0,0,(394*(HPP))/16,5));
    window.draw(entitySprite_HP);
}

void Hostile_Goblin::getNumb(int distance, sf::Vector2i entityCoords)
{
    ///getting angle to nearest target
    float angle = atan2(entityCoords.y - coordinates.y, entityCoords.x - coordinates.x);
    angle = angle * 180 / 3.14159265;

    if(angle < 0)
    {
        angle = angle*-1;
    }
    else
    {
        angle = angle -360;
        angle = angle * -1;
    }

    if(337.5<angle || angle<22.5)
    {
        direction = 1; //right
    }
    else if(22.5<angle && angle<67.5)
    {
        direction = 2; //up right
    }
    else if(67.5<angle && angle<112.5)
    {
        direction = 3; //foward
    }
    else if(112.5<angle && angle<157.5)
    {
        direction = 4; //up left
    }
    else if(157.5<angle && angle<202.5)
    {
        direction = 5; //left
    }
    else if(202.5<angle && angle<247.5)
    {
        direction = 6; //down left
    }
    else if(247.5<angle && angle<292.5)
    {
        direction = 7; //down
    }
    else
    {
        direction = 8; //down right
    }

    ///AI states

    if(entityState == passive)
    {
        direction = 0;

        if(stateDuration == 0)
        {
            if(hp < 10)
            {
                entityState = run;
                stateDuration = 30;
            }
            else if(distance < 50)
            {
                entityState = melee;
                stateDuration = 30;
            }
            else if(distance < 150 && distance > 50)
            {
                entityState = charge;
                stateDuration = 50;
            }
            else if(distance < 400 && distance > 150)
            {
                entityState = ranged;
                stateDuration = 30;
            }
            else
            {
                stateDuration = 10;
            }
        }
        stateDuration--;
    }
    else if(entityState == melee)
    {
        if(distance < 50)
        {
            if(cooldown == 0 )
            {
                entityManager.createSpecialEntity(1,ID,getName(),coordinates,sf::Vector2f(4,4),angle,40,10,0,0,0);
                cooldown = 50;
            }
        }

        if(stateDuration == 0)
        {
            if(hp < 10)
            {
                entityState = run;
                stateDuration = 30;
            }
            else if(distance < 100)
            {
                stateDuration = 30;
            }
            else if(distance < 150 && distance > 100)
            {
                entityState = charge;
                stateDuration = 50;
            }
            else if(distance < 400 && distance > 150)
            {
                entityState = ranged;
                stateDuration = 30;
            }
            else
            {
                entityState = passive;
                stateDuration = 10;
            }
        }
        stateDuration--;
    }
    else if(entityState == charge)
    {
        if(distance < 50)
        {
            if(cooldown == 0 )
            {
                entityManager.createSpecialEntity(1,ID,getName(),coordinates,sf::Vector2f(4,4),angle,40,10,0,0,0);
                cooldown = 30;
            }
        }

        velocity = sf::Vector2f(1.25, 1.25);

        if(stateDuration == 0)
        {
            velocity = sf::Vector2f(.75, .75);
            if(hp < 10)
            {
                entityState = run;
                stateDuration = 30;
            }
            else if(distance < 75)
            {
                entityState = melee;
                stateDuration = 50;
            }
            else if(distance < 400 && distance > 75)
            {
                entityState = ranged;
                stateDuration = 50;
            }
            else
            {
                entityState = passive;
                stateDuration = 10;
            }
        }
        stateDuration--;
    }
    else if(entityState == ranged)
    {
        if(distance < 400 && distance > 40)
        {
            if(cooldown == 0)
            {
                entityManager.createSpecialEntity(2,ID,getName(),coordinates,sf::Vector2f(4,4),angle,200,10,0,0,0);
                cooldown = 144;
            }
        }
        if(stateDuration == 0)
        {
            if(hp < 10)
            {
                entityState = run;
                stateDuration = 30;
            }
            else if(distance < 75)
            {
                stateDuration = 30;
                entityState = melee;
            }
            else if(distance < 150 && distance > 75)
            {
                entityState = charge;
                stateDuration = 50;
            }
            else if(distance < 400 && distance > 150)
            {
                stateDuration = 30;
            }
            else
            {
                entityState = passive;
                stateDuration = 10;
            }
        }
        stateDuration--;
    }

    else if(entityState == dodge)
    {

    }
    else if(entityState == run)
    {
        int realDirection = direction - 4;
        if(realDirection < 0)
        {
            realDirection = realDirection + 8;
        }
        direction = realDirection;

    }




    if(count_entityStep>144/velocity.x)
    {
        count_entityStep=0;
    }
    if(count_entityStep >= 0 && count_entityStep < 36 / velocity.x || count_entityStep >= 72 / velocity.x && count_entityStep < 108 / velocity.x)
    {
        entityStep=1;
    }
    else if(count_entityStep >= 36 / velocity.x && count_entityStep < 72 / velocity.x)
    {
        entityStep=2;
    }
    else
    {
        entityStep=3;
    }
    count_entityStep++;


    ///AI
    if(cooldown != 0)
    {
        cooldown--;
    }
    /*
        if(a < 500&& a> 40)
        {
            if(cooldown == 0)
            {
                entityManager.createSpecialEntity(2,ID,getName(),coordinates,sf::Vector2f(4,4),angle,200,10,0,0,0);
                cooldown = 144;
            }
        }
        else if(a < 40)
        {
            if(cooldown == 0 )
            {
                entityManager.createSpecialEntity(1,ID,getName(),coordinates,sf::Vector2f(4,4),angle,40,10,0,0,0);
                cooldown = 50;
            }
        }
        */
}

void Hostile_Goblin::update(int effect, int (&returnCollision)[4])
{
    /// Collision

    if(returnCollision[0] == 0 && (direction == 2 || direction == 3 || direction == 4))
    {
        coordinates.y = coordinates.y - velocity.y;
    }
    if(returnCollision[2] == 0 && (direction == 6 || direction == 7 || direction == 8))
    {
        coordinates.y = coordinates.y + velocity.y;
    }
    if(returnCollision[3] == 0 && (direction == 4 || direction == 5 || direction == 6))
    {
        coordinates.x = coordinates.x - velocity.x;
    }
    if(returnCollision[1] == 0 && (direction == 1 || direction == 2 || direction == 8))
    {
        coordinates.x = coordinates.x + velocity.x;
    }

    if(returnCollision[0] != 0 || returnCollision[1] != 0 || returnCollision[2] != 0 || returnCollision[3] != 0 || entityState == passive)
    {
        count_entityStep = 0;
    }


    /// Sprite

    if(direction == 1)
    {
        switch (entityStep)
        {
        case 1:
            entitySprite.setTextureRect(sf::IntRect(105,0,23,50));
            break;
        case 2:
            entitySprite.setTextureRect(sf::IntRect(105,51,23,50));
            break;
        case 3:
            entitySprite.setTextureRect(sf::IntRect(105,102,23,50));
            break;
        }

    }
    else if(direction == 2)
    {
        switch (entityStep)
        {
        case 1:
            entitySprite.setTextureRect(sf::IntRect(157,0,23,50));
            break;
        case 2:
            entitySprite.setTextureRect(sf::IntRect(157,51,23,50));
            break;
        case 3:
            entitySprite.setTextureRect(sf::IntRect(157,102,23,50));
            break;
        }
    }
    else if(direction == 3 || direction == 0)
    {
        switch (entityStep)
        {
        case 1:
            entitySprite.setTextureRect(sf::IntRect(0,0,23,50));
            break;
        case 2:
            entitySprite.setTextureRect(sf::IntRect(0,51,23,50));
            break;
        case 3:
            entitySprite.setTextureRect(sf::IntRect(0,102,23,50));
            break;
        }
    }
    else if(direction == 4)
    {
        switch (entityStep)
        {
        case 1:
            entitySprite.setTextureRect(sf::IntRect(183,0,23,50));
            break;
        case 2:
            entitySprite.setTextureRect(sf::IntRect(183,51,23,50));
            break;
        case 3:
            entitySprite.setTextureRect(sf::IntRect(183,102,23,50));
            break;
        }
    }
    else if(direction == 5)
    {
        switch (entityStep)
        {
        case 1:
            entitySprite.setTextureRect(sf::IntRect(131,0,23,50));
            break;
        case 2:
            entitySprite.setTextureRect(sf::IntRect(131,51,23,50));
            break;
        case 3:
            entitySprite.setTextureRect(sf::IntRect(131,102,23,50));
            break;
        }
    }
    else if(direction == 6)
    {
        switch (entityStep)
        {
        case 1:
            entitySprite.setTextureRect(sf::IntRect(79,0,23,50));
            break;
        case 2:
            entitySprite.setTextureRect(sf::IntRect(79,51,23,50));
            break;
        case 3:
            entitySprite.setTextureRect(sf::IntRect(79,102,23,50));
            break;
        }

    }
    else if(direction == 7)
    {
        switch (entityStep)
        {
        case 1:
            entitySprite.setTextureRect(sf::IntRect(27,0,23,50));
            break;
        case 2:
            entitySprite.setTextureRect(sf::IntRect(27,51,23,50));
            break;
        case 3:
            entitySprite.setTextureRect(sf::IntRect(27,102,23,50));
            break;
        }
    }
    else if(direction == 8)
    {
        switch (entityStep)
        {
        case 1:
            entitySprite.setTextureRect(sf::IntRect(53,0,23,50));
            break;
        case 2:
            entitySprite.setTextureRect(sf::IntRect(53,51,23,50));
            break;
        case 3:
            entitySprite.setTextureRect(sf::IntRect(53,102,23,50));
            break;
        }
    }
}


///get's
int Hostile_Goblin::returnID()
{
    return ID;
}
std::string Hostile_Goblin::getName()
{

    std::ostringstream os;
    os<<"Goblin_";
    os<<ID;
    std::string entityName(os.str());
    return entityName;
}
sf::Vector2f Hostile_Goblin::getCoordinates()
{
    return coordinates;
}
sf::Vector2i Hostile_Goblin::getMapCoordinates()
{
    mapCoordinates.x = (int)coordinates.x/32 + 1;
    mapCoordinates.y = (int)coordinates.y/32 + 1;

    return mapCoordinates;
}
sf::Vector2f Hostile_Goblin::getSideRadius()
{
    return sideRadius;
}
sf::Vector2f Hostile_Goblin::getVelocity()
{
    return velocity;
}
int Hostile_Goblin::getType()
{
    return 10;
}
