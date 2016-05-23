#include <iostream>
#include <cmath>
#include "EntityManager/Entity/Collidable/Living/Player/Entity_Player.h"
#include "Utl.h"

extern bool isInDebugMode;

Entity_Player::Entity_Player(ResourceManager &res, EntityManager &entityManager, LightManager& _lightManager,
                             sf::Vector2f coordinates, int ID, std::string _entityType,
                             int _hp, int _maxHp,
                             int _mp, int _maxMp,
                             int _st, int _maxSt):
    coordinates(coordinates.x,coordinates.y)
    , ID(ID)
    , entityManager(entityManager)
    , res(res)
    , lightManager(_lightManager)

    , tick(1)

    , sideRadius(12.5, 12.5)
    , velocity(12, 12)

    , maxHP(_maxHp)
    , maxMP(_maxMp)
    , maxST(_maxSt)
    , hp(_hp)
    , mp(_mp)
    , stamina(_st)

    , entityType(_entityType)

    , mIsMovingUp(false)
    , mIsMovingDown(false)
    , mIsMovingLeft(false)
    , mIsMovingRight(false)
    , shiftIsPressed(false)

    , count_playerStep(1)
    , previousVelocity(1.25)

    , direction_facing(0)
    , playerStep(1)


    , animationDirection(1)
    , animationStep(1)

    , wasRunning(false)
    , runningTick(0)

    , animation(res, "Media/Image/Game/Player/Customization/Skin/White.png", 8, 3)
    , colRect()
{
    entitySprite.setTexture(res.getTexture("Media/Image/Game/Player/Character_Base.png"));
    entitySprite_HP.setTexture(res.getTexture("Media/Image/Game/Gui/Health.png"));

    lightID = lightManager.create_lightSource(coordinates, 20, 4, sf::Vector2f(200,200));

    colRect.setFillColor(sf::Color(0,0,255,100));
    colRect.setSize(sf::Vector2f(sideRadius.x *2, sideRadius.y*2));
}

Entity_Player::~Entity_Player()
{

}

void Entity_Player::drawEntity(sf::RenderWindow &window)
{
    animation.getSprite(animationDirection-1, animationStep-1).setPosition(coordinates.x-(animation.getSheetWidth()/2.f), coordinates.y-(animation.getSheetHeight()/2.f)-12.5);
    window.draw(animation.getSprite(animationDirection-1, animationStep-1));

    if(isInDebugMode)
    {
        colRect.setPosition(sf::Vector2f(coordinates.x - sideRadius.x, coordinates.y - sideRadius.y));
        window.draw(colRect);
    }


    entitySprite_HP.setPosition(coordinates.x-sideRadius.x, coordinates.y-sideRadius.y-35);
    float HPP;
    HPP = (float)hp/(float)maxHP;
    entitySprite_HP.setTextureRect(sf::IntRect(0,0,(394*(HPP))/16,5));
    window.draw(entitySprite_HP);

    if(isInDebugMode)
    {
        stamina = 100;
    }
}

void Entity_Player::handleImput(int actionType, bool isPressed)
{
    if(actionType == 0)
    {
        mIsMovingUp = isPressed;
    }
    else if(actionType == 1)
    {
        mIsMovingDown = isPressed;
    }
    else if(actionType == 2)
    {
        mIsMovingLeft = isPressed;
    }
    else if(actionType == 3)
    {
        mIsMovingRight = isPressed;
    }
    else if(actionType == 4)
    {
        shiftIsPressed = isPressed;
    }
}

void Entity_Player::update(int effect, int (&returnCollision)[4])
{
    ///Determining the players step

    previousVelocity = previousVelocity/1.5;

    if(count_playerStep>144/previousVelocity)
    {
        count_playerStep=0;
    }

    if((count_playerStep >= 0 && count_playerStep < 36 / previousVelocity )||( count_playerStep >= 72 / previousVelocity && count_playerStep < 108 / previousVelocity))
    {
        playerStep=1;
    }
    else if(count_playerStep >= 36 / previousVelocity && count_playerStep < 72 / previousVelocity)
    {
        playerStep=2;
    }
    else
    {
        playerStep=3;
    }

    if((!mIsMovingUp && !mIsMovingDown && !mIsMovingLeft && !mIsMovingRight)||(mIsMovingUp && mIsMovingDown)||(mIsMovingLeft && mIsMovingRight))
    {
        playerStep=1;
        count_playerStep=0;
    }
    count_playerStep++;


    ///Determining the direction the player is facing
    ///And also, choosing the sprite

    if(337.5<angleToMouse || angleToMouse<22.5)
    {
        direction_facing = 0;

        animationDirection = 5;
        animationStep = playerStep;
    }
    else if(22.5<angleToMouse && angleToMouse<67.5)
    {
        direction_facing = 1;

        animationDirection = 7;
        animationStep = playerStep;

    }
    else if(67.5<angleToMouse && angleToMouse<112.5)
    {
        direction_facing = 2;

        animationDirection = 1;
        animationStep = playerStep;
    }
    else if(112.5<angleToMouse && angleToMouse<157.5)
    {
        direction_facing = 3;

        animationDirection = 8;
        animationStep = playerStep;

    }
    else if(157.5<angleToMouse && angleToMouse<202.5)
    {
        direction_facing = 4;

        animationDirection = 6;
        animationStep = playerStep;

    }
    else if(202.5<angleToMouse && angleToMouse<247.5)
    {
        direction_facing = 5;

        animationDirection = 4;
        animationStep = playerStep;


    }
    else if(247.5<angleToMouse && angleToMouse<292.5)
    {
        direction_facing = 6;

        animationDirection = 2;
        animationStep = playerStep;
    }
    else
    {
        direction_facing = 7;

        animationDirection = 3;
        animationStep = playerStep;
    }


    ///Determining the direction the player is moving

    int direction_moving;

    if(!mIsMovingUp && !mIsMovingDown && !mIsMovingLeft && mIsMovingRight)
    {
        direction_moving = 0;
    }
    else if(mIsMovingUp && !mIsMovingDown && !mIsMovingLeft && mIsMovingRight)
    {
        direction_moving = 1;
    }
    else if(mIsMovingUp && !mIsMovingDown && !mIsMovingLeft && !mIsMovingRight)
    {
        direction_moving = 2;
    }
    else if(mIsMovingUp && !mIsMovingDown && mIsMovingLeft && !mIsMovingRight)
    {
        direction_moving = 3;
    }
    else if(!mIsMovingUp && !mIsMovingDown && mIsMovingLeft && !mIsMovingRight)
    {
        direction_moving = 4;
    }
    else if(!mIsMovingUp && mIsMovingDown && mIsMovingLeft && !mIsMovingRight)
    {
        direction_moving = 5;
    }
    else if(!mIsMovingUp && mIsMovingDown && !mIsMovingLeft && !mIsMovingRight)
    {
        direction_moving = 6;
    }
    else if(!mIsMovingUp && mIsMovingDown && !mIsMovingLeft && mIsMovingRight)
    {
        direction_moving = 7;
    }
    else
    {
        direction_moving = 99;
    }


    /// Finding the altered velocity

    int differenceOfFacing = 4 - std::abs(std::abs(direction_moving-direction_facing)-4);

    float speedDivider = 0;

    switch(differenceOfFacing)
    {
    case 0:
        speedDivider = 1.f;
        break;
    case 1:
        speedDivider=0.8f;
        break;
    case 2:
        speedDivider=0.7f;
        break;
    case 3:
        speedDivider=0.5f;
        break;
    case 4:
        speedDivider=0.3f;
        break;
    }

    sf::Vector2f realVelocity = sf::Vector2f(velocity.x * speedDivider, velocity.y * speedDivider);
    previousVelocity = realVelocity.x;


    ///Checking collision

    if(returnCollision[0] == 0 && mIsMovingUp)
    {
        coordinates.y = coordinates.y - realVelocity.y;
    }
    if(returnCollision[2] == 0 && mIsMovingDown)
    {
        coordinates.y = coordinates.y + realVelocity.y;
    }
    if(returnCollision[3] == 0 && mIsMovingLeft)
    {
        coordinates.x = coordinates.x - realVelocity.x;
    }
    if(returnCollision[1] == 0 && mIsMovingRight)
    {
        coordinates.x = coordinates.x + realVelocity.x;
    }


    ///temporary stamina + mana + health regeneration

    //float staminaRegen = .1, healthRegen = .05, manaRegen = .1;

    if(stamina < maxST)
    {
        if(!shiftIsPressed)
        {
            if(tick % 24 == 0 )
            {
                stamina++;
            }
        }
    }
    if(hp < maxHP)
    {
        if(tick % 288 == 0 )
        {
            hp++;
        }
    }
    if(mp < maxMP)
    {
        if(tick % 48 == 0 )
        {
            mp++;
        }
    }


    ///running

    if(shiftIsPressed && stamina > 0)
    {
        if(wasRunning)
        {
            if(runningTick != 12)
            {
                runningTick++;
            }
            else
            {
                stamina = stamina - 1;
                wasRunning = true;
                runningTick = 0;
            }
        }
        else
        {
            stamina = stamina - 1;
            wasRunning = true;
            runningTick++;
        }
        velocity = sf::Vector2f(2, 2);
    }
    else
    {
        velocity = sf::Vector2f(1.25, 1.25);
    }

    ///lighting
    lightManager.moveLightSource(lightID,coordinates);
    lightManager.flickerLight(lightID, 80, 120);


    ///tick

    if(tick == 8640)
    {
        tick = 1;
    }
    else
    {
        tick++;
    }
}


///sets
void Entity_Player::setAngleToMouse(float angle)
{
    angleToMouse = angle;
}
void Entity_Player::setMouseCoordinates(sf::Vector2f gottenMouseCoordinates)
{
    mouseCoordinates = gottenMouseCoordinates;
}
void Entity_Player::getNumb(int a, sf::Vector2i  entityCoords)
{

}

///gets
int Entity_Player::returnID()
{
    return ID;
}
std::string Entity_Player::getName()
{
    std::string entityName("Player");
    return entityName;
}
sf::Vector2f Entity_Player::getSideRadius()
{
    return sideRadius;
}
sf::Vector2i Entity_Player::getMapCoordinates()
{
    mapCoordinates.x = (int)coordinates.x/32 + 1;
    mapCoordinates.y = (int)coordinates.y/32 + 1;

    return mapCoordinates;
}
sf::Vector2f Entity_Player::getVelocity()
{
    return velocity;
}
sf::Vector2f Entity_Player::getCoordinates()
{
    return coordinates;
}
std::tuple<int, int, int, int, int, int> Entity_Player::getStats()
{
    return std::make_tuple(hp,mp,stamina, maxHP, maxMP, maxST);
}
