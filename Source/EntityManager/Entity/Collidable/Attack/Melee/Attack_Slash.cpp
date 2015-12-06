#include "Attack_Slash.h"
#include <iostream>

Attack_Slash::Attack_Slash( ResourceManager &res, int _attackID,int _attackerID, std::string _attackerName,
                            sf::Vector2f _coordinates, sf::Vector2f _velocity, float _angle,
                            int _duration, int _attackDamage, float _sizeMultiplier, float _timeMultiplier,
                            int _extra):
    attackID(_attackID)
    , attackerName(_attackerName)
    , attackerID (_attackerID)
    , coordinates(_coordinates)
    , velocity(_velocity)
    , duration(_duration)
    , attackDamage(_attackDamage)
    , sizeMultiplier(_sizeMultiplier)
    , timeMultiplier(_timeMultiplier)
    , extra(_extra)

    , angle(_angle)

    , res(res)
    , initDuration(_duration)
{
    angle = fixAngle(angle);
    angle = angle;

    entitySprite.setTexture(res.getTexture("Media/Image/Game/Attacks/Melee/sword_club.png"));
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


    /*
    rectBox2[0] = sf::Vector2f(entityCoordinates.x-sideRadius.x,entityCoordinates.y-sideRadius.y);
    rectBox2[1] = sf::Vector2f(entityCoordinates.x+sideRadius.x,entityCoordinates.y-sideRadius.y);
    rectBox2[2] = sf::Vector2f(entityCoordinates.x-sideRadius.x,entityCoordinates.y+sideRadius.y);
    rectBox2[3] = sf::Vector2f(entityCoordinates.x+sideRadius.x,entityCoordinates.y+sideRadius.y);

    rectTarget[0].setSize(sf::Vector2f((float)0,2*sideRadius.x));
    rectTarget[1].setSize(sf::Vector2f((float)0,2*sideRadius.y));
    rectTarget[2].setSize(sf::Vector2f((float)0,2*sideRadius.x));
    rectTarget[3].setSize(sf::Vector2f((float)0,2*sideRadius.y));

    rectTarget[0].setRotation(270);
    rectTarget[1].setRotation(0);
    rectTarget[2].setRotation(180);
    rectTarget[3].setRotation(90);

    rectTarget[0].setPosition(rectBox2[0]);
    rectTarget[1].setPosition(rectBox2[1]);
    rectTarget[2].setPosition(rectBox2[2]);
    rectTarget[3].setPosition(rectBox2[3]);

    circleTarget[0].setPosition(rectBox2[0]);
    circleTarget[1].setPosition(rectBox2[1]);
    circleTarget[2].setPosition(rectBox2[2]);
    circleTarget[3].setPosition(rectBox2[3]);

    //Axis of rect1

    for(int i = 0; i<=7; i++)
    {
        float normal;

        if(i<3)
        {
            normal = -(rectBox1[i].x-rectBox1[i+1].x)/(rectBox1[i].y-rectBox1[i+1].y);
        }
        else if(i==3)
        {
            normal = -(rectBox1[3].x-rectBox1[0].x)/(rectBox1[3].y-rectBox1[0].y);
        }
        else if(i>3&&i<7)
        {
            normal = -(rectBox2[i-4].x-rectBox2[i-3].x)/(rectBox2[i-4].y-rectBox2[i-3].y);
        }
        else  // I must be equal to 7, it is the last point
        {
            normal = -(rectBox2[3].x-rectBox2[0].x)/(rectBox2[3].y-rectBox2[0].y);
        }


        // Scalar answer, dot product
        float poly1_p[4];
        float poly2_p[4];

        // Vector answer
        float proj1_p[4][2];
        float proj2_p[4][2];

        // Dot product
        for(int j = 0; j<=3; j++)
        {
            poly1_p[j] = (rectBox1[j].x + rectBox1[j].y * normal);
            poly2_p[j] = (rectBox2[j].x + rectBox2[j].y * normal);
        }

        float poly1_min = poly1_p[0], poly1_max = poly1_p[0], poly2_min = poly2_p[0], poly2_max = poly2_p[0];

        //Polygon min, max
        for(int j = 1; j<=3; j++)
        {
            if(poly1_p[j] >  poly1_max)
            {
                poly1_max = poly1_p[j];
            }
            else if (poly1_p[j] <  poly1_min)
            {
                poly1_min = poly1_p[j];
            }

            if(poly2_p[j] >  poly2_max)
            {
                poly2_max = poly2_p[j];
            }
            else if (poly2_p[j] <  poly2_min)
            {
                poly2_min = poly2_p[j];
            }
        }
        if(poly1_min > poly2_max || poly1_max < poly2_min)
        {
            return false;
        }
    }
    return true;
    */
}

void Attack_Slash::drawEntity(sf::RenderWindow &mWindow)
{

}
void Attack_Slash::drawLayer2(sf::RenderWindow &mWindow)
{
    entitySprite.setPosition(coordinates);
    mWindow.draw(entitySprite);

    /*
    for(int x = 0; x <= 3; x++)
    {
        circleAttack[x].setFillColor(sf::Color::Red);
        circleAttack[x].setRadius(2);
        circleAttack[x].setOrigin(2,2);
        circleAttack[x].setPosition(hitbox_Attack[x].x, hitbox_Attack[x].y);
        mWindow.draw(circleAttack[x]);
    }
    */
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
    for(int x = 0; x != hitbox_Attack.size(); x++)
    {
        hitbox_Attack[x].x = hitbox_Attack[x].x - coordinates.x + coords.x;
        hitbox_Attack[x].y = hitbox_Attack[x].y - coordinates.y + coords.y;
    }
    coordinates = coords;
}
int Attack_Slash::getDamage(int ID)
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

