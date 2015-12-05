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
    rectBox1_P[0] = sf::Vector2f(coordinates.x,coordinates.y);
    rectBox1_P[1] = sf::Vector2f(coordinates.x- 25,coordinates.y+ 25);
    rectBox1_P[2] = sf::Vector2f(coordinates.x- 19,coordinates.y+ 29);
    rectBox1_P[3] = sf::Vector2f(coordinates.x- 12,coordinates.y+ 32);
    rectBox1_P[4] = sf::Vector2f(coordinates.x- 6,coordinates.y+ 34);
    rectBox1_P[5] = sf::Vector2f(coordinates.x,coordinates.y+ 35);
    rectBox1_P[6] = sf::Vector2f(coordinates.x+ 6,coordinates.y+ 34);
    rectBox1_P[7] = sf::Vector2f(coordinates.x+ 12,coordinates.y+ 32);
    rectBox1_P[8] = sf::Vector2f(coordinates.x+ 19,coordinates.y+ 29);
    rectBox1_P[9] = sf::Vector2f(coordinates.x+ 25,coordinates.y+ 25);


    angle = angle - 90;
    if(angle < 0)
    {
        angle +=360;
    }
    angle  = angle - 360;
    if(angle<0)
    {
        angle = angle * -1;
    }

    if(angle<180)
    {
        angle = angle + 180;
    }
    else
    {
        angle = angle - 180;
    }

    entitySprite.setTexture(res.getTexture("Media/Image/Game/Attacks/Melee/sword_club.png"));
    entitySprite.setOrigin(3.5,35);
    entitySprite.setRotation(angle-45-180);

    angle = angle * 3.141592 / 180;

    //std::cout<<"Angle :"<<angle<<std::endl;

    rectBox1[0] = rectBox1_P[0];
    rectBox1[1] = rectBox1_P[1];
    rectBox1[2] = rectBox1_P[2];
    rectBox1[3] = rectBox1_P[3];

    for(int i = 1; i <= 9; i++)
    {
        float sin = std::sin(angle);
        float cos = std::cos(angle);

        rectBox1_P[i].x -= coordinates.x;
        rectBox1_P[i].y -= coordinates.y;

        float x,y;

        x = rectBox1_P[i].x * cos - rectBox1_P[i].y * sin;
        y = rectBox1_P[i].x * sin + rectBox1_P[i].y * cos;

        rectBox1_P[i].x = coordinates.x + x;
        rectBox1_P[i].y = coordinates.y + y;
    }


    //temp Line + Angle exa
    /*
    rectAttack[0].setSize(sf::Vector2f(1,std::sqrt(25*25*2)));
    rectAttack[1].setSize(sf::Vector2f(1,std::sqrt(25*25+10*10)));
    rectAttack[2].setSize(sf::Vector2f(1,std::sqrt(25*25+10*10)));
    rectAttack[3].setSize(sf::Vector2f(1,std::sqrt(25*25*2)));
    */

    rectAttack[0].setSize(sf::Vector2f(0,std::sqrt(25*25*2)));
    rectAttack[1].setSize(sf::Vector2f(0,std::sqrt(25*25+10*10)));
    rectAttack[2].setSize(sf::Vector2f(0,std::sqrt(25*25+10*10)));
    rectAttack[3].setSize(sf::Vector2f(0,std::sqrt(25*25*2)));

    // for(int i = 0; i <= 3; i++)
    // {
    //    if(i!=3)
    //   {
    //      angleRectA[i] = atan2(rectBox1[i+1].x-rectBox1[i].x,rectBox1[i+1].y-rectBox1[i].y);
    //   }
    //   else
    //    {
    //        angleRectA[i] = atan2(rectBox1[0].x-rectBox1[i].x,rectBox1[0].y-rectBox1[i].y);
    //    }
    // }


    for(int x = 0; x <= 3; x++)
    {
        circleAttack[x].setFillColor(sf::Color::Red);
        circleTarget[x].setFillColor(sf::Color::Blue);

        circleAttack[x].setRadius(2);
        circleTarget[x].setRadius(2);

        circleAttack[x].setOrigin(2,2);
        circleTarget[x].setOrigin(2,2);

        //rectAttack[x].setFillColor(sf::Color::Red);
        //rectTarget[x].setFillColor(sf::Color::Blue);

        //rectAttack[x].setOrigin(0.5,0);
        // rectTarget[x].setOrigin(0.5,0);

        // angleRectA[x] = angleRectA[x] * 180 / 3.14159265;
        //  if(angleRectA[x]<0)
        // {
        //     angleRectA[x] = angleRectA[x]*-1;
        //   }
        // else
        // {
        //   angleRectA[x] = angleRectA[x] -360;
        //    angleRectA[x] = angleRectA[x] * -1;
        //  }
        //  rectAttack[x].setRotation(angleRectA[x]);
    }
}

bool Attack_Slash::checkCollision(sf::Vector2f entityCoordinates, sf::Vector2f sideRadius)
{

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
}

int Attack_Slash::returnID()
{
    return attackID;
}

void Attack_Slash::drawEntity(sf::RenderWindow &mWindow)
{

}
void Attack_Slash::drawLayer2(sf::RenderWindow &mWindow)
{
      entitySprite.setPosition(coordinates);
    mWindow.draw(entitySprite);
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

    if(duration>=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Attack_Slash::update(sf::Vector2f coords)
{
    for(int x = 0; x < 10; x++)
    {
        rectBox1_P[x].x = rectBox1_P[x].x - coordinates.x + coords.x;
        rectBox1_P[x].y = rectBox1_P[x].y - coordinates.y + coords.y;
    }
    coordinates = coords;

    float rotateAngle = 90/(float)initDuration;
    entitySprite.setRotation(((entitySprite.getRotation())+1e-2)+rotateAngle);


    if(duration > (int)(.75 * initDuration))
    {
        rectBox1[0] = rectBox1_P[0];
        rectBox1[1] = rectBox1_P[7];
        rectBox1[2] = rectBox1_P[8];
        rectBox1[3] = rectBox1_P[9];

    }
    else if (duration > (int)(.5 * initDuration))
    {
        rectBox1[0] = rectBox1_P[0];
        rectBox1[1] = rectBox1_P[5];
        rectBox1[2] = rectBox1_P[6];
        rectBox1[3] = rectBox1_P[7];

    }
    else if (duration > (int)(.25 * initDuration))
    {
        rectBox1[0] = rectBox1_P[0];
        rectBox1[1] = rectBox1_P[3];
        rectBox1[2] = rectBox1_P[4];
        rectBox1[3] = rectBox1_P[5];
    }
    else
    {
        rectBox1[0] = rectBox1_P[0];
        rectBox1[1] = rectBox1_P[1];
        rectBox1[2] = rectBox1_P[2];
        rectBox1[3] = rectBox1_P[3];
    }

    circleAttack[0].setPosition(rectBox1[0]);
    circleAttack[1].setPosition(rectBox1[1]);
    circleAttack[2].setPosition(rectBox1[2]);
    circleAttack[3].setPosition(rectBox1[3]);
    rectAttack[0].setPosition(rectBox1[0]);
    rectAttack[1].setPosition(rectBox1[1]);
    rectAttack[2].setPosition(rectBox1[2]);
    rectAttack[3].setPosition(rectBox1[3]);

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

