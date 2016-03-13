#include "Entity_Chicken.h"
#include <iostream>
#include <sstream>

Entity_Chicken::Entity_Chicken( ResourceManager& res, EntityManager& entityManager,sf::Vector2f coordinates, int aID, std::string _entityType):
    coordinates(coordinates.x,coordinates.y)
    , sideRadius(12.5, 12.5)
    , velocity(0.85f, 0.85f)
    , hp(30)
    , mp(0)
    , stamina(50.f)
    , maxHP(30)
    , maxMP(0)
    , maxST(50)

    , entityType(_entityType)

    , mIsMovingUp(false)
    , mIsMovingDown(false)
    , mIsMovingLeft(false)
    , mIsMovingRight(false)
    , entityManager(entityManager)

    , AIInt(0)

    , ID(aID)

    , res(res)
{
    entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_N.png"));
    entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_NE.png"));
    entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_NW.png"));
    entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_W.png"));
    entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_E.png"));
    entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_S.png"));
    entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_SW.png"));
    entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_SE.png"));

    entitySprite_HP.setTexture(res.getTexture("Media/Image/Game/Gui/Health.png"));
}

sf::Vector2f Entity_Chicken::getSideRadius()
{
    return sideRadius;
}
sf::Vector2f Entity_Chicken::getVelocity()
{
    return velocity;
}

void Entity_Chicken::drawEntity(sf::RenderWindow &window)
{
    entitySprite.setPosition(coordinates.x-sideRadius.x, coordinates.y-sideRadius.y);
    window.draw(entitySprite);

    entitySprite_HP.setPosition(coordinates.x-sideRadius.x, coordinates.y-sideRadius.y-35);
    float HPP;
    HPP = (float)hp/(float)maxHP;
    entitySprite_HP.setTextureRect(sf::IntRect(0,0,(394*(HPP))/16,5));
    window.draw(entitySprite_HP);
}
void Entity_Chicken::update(int effect, int (&returnCollision)[4])
{
    // AI
    AIInt++;

    if(AIInt>=0 && AIInt < 200)
    {
        mIsMovingUp = true;
        mIsMovingDown = false;
        mIsMovingRight = false;
        mIsMovingLeft = false;
    }
    else if(AIInt>=200 && AIInt < 400)
    {
        mIsMovingUp = true;
        mIsMovingDown = false;
        mIsMovingRight = true;
        mIsMovingLeft = false;
    }
    else if(AIInt>=400 && AIInt < 600)
    {
        mIsMovingUp = false;
        mIsMovingDown = false;
        mIsMovingRight = true;
        mIsMovingLeft = false;
    }
    else if(AIInt>=600 && AIInt < 800)
    {
        mIsMovingUp = false;
        mIsMovingDown = true;
        mIsMovingRight = true;
        mIsMovingLeft = false;
    }
    else if(AIInt>=800 && AIInt < 1000)
    {
        mIsMovingUp = false;
        mIsMovingDown = true;
        mIsMovingRight = false;
        mIsMovingLeft = false;
    }
    else if(AIInt>=1000 && AIInt < 1200)
    {
        mIsMovingUp = false;
        mIsMovingDown = true;
        mIsMovingRight = false;
        mIsMovingLeft = true;
    }
    else if(AIInt>=1200 && AIInt < 1400)
    {
        mIsMovingUp = false;
        mIsMovingDown = false;
        mIsMovingRight = false;
        mIsMovingLeft = true;
    }
    else if(AIInt>=1400 && AIInt < 1600)
    {
        mIsMovingUp = true;
        mIsMovingDown = false;
        mIsMovingRight = false;
        mIsMovingLeft = true;
    }
    else if(AIInt>1600)
    {
        AIInt = 0;
    }




    // Collision

    if(returnCollision[0] == 0 && mIsMovingUp)
    {
        coordinates.y = coordinates.y - velocity.y;
    }
    if(returnCollision[2] == 0 && mIsMovingDown)
    {
        coordinates.y = coordinates.y + velocity.y;
    }
    if(returnCollision[3] == 0 && mIsMovingLeft)
    {
        coordinates.x = coordinates.x - velocity.x;
    }
    if(returnCollision[1] == 0 && mIsMovingRight)
    {
        coordinates.x = coordinates.x + velocity.x;
    }
    if((returnCollision[0] == 1 && mIsMovingUp)||(returnCollision[2] == 1 && mIsMovingDown)||(returnCollision[3] == 1 && mIsMovingLeft)||(returnCollision[1] == 1 && mIsMovingRight))
    {
        AIInt+=200;
    }


    // Sprite

    if(mIsMovingUp && !mIsMovingDown)
    {
        if(!mIsMovingLeft && !mIsMovingRight)
        {
            entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_N.png"));

        }
        else
        {
            if(mIsMovingLeft)
            {
                entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_NW.png"));

            }
            else if (mIsMovingRight)
            {

                entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_NE.png"));

            }
        }
    }
    else if(mIsMovingDown && !mIsMovingUp)
    {
        if(!mIsMovingLeft&&!mIsMovingRight)
        {

            entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_S.png"));

        }
        else
        {
            if(mIsMovingLeft)
            {
                entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_SW.png"));

            }
            else if (mIsMovingRight)
            {

                entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_SE.png"));
            }
        }
    }
    else
    {
        if(mIsMovingLeft)
        {
            entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_W.png"));

        }
        else if (mIsMovingRight)
        {
            entitySprite.setTexture(res.getTexture("Media/Image/Game/Entity/Passive/Chicken/Chicken_E.png"));

        }
    }
}

int Entity_Chicken::getType()
{
    return 5;
}

void Entity_Chicken::getNumb(int a, sf::Vector2i  b)
{

}

sf::Vector2f Entity_Chicken::getCoordinates()
{
    return coordinates;
}

sf::Vector2i Entity_Chicken::getMapCoordinates()
{
    mapCoordinates.x = (int)coordinates.x/32 + 1;
    mapCoordinates.y = (int)coordinates.y/32 + 1;

    return mapCoordinates;
}

int Entity_Chicken::returnID()
{
    return ID;
}

std::string Entity_Chicken::getName()
{
    std::ostringstream os;
    os<<"Chicken_";
    os<<ID;
    std::string entityName(os.str());
    return entityName;
}
