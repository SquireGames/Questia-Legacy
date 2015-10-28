#include "EntityManager/Entity/Collidable/Attack/Entity_Attack.h"

Entity_Attack::Entity_Attack()
{
    //ctor
}

Entity_Attack::~Entity_Attack()
{
    //dtor
}

float Entity_Attack::fixAngle(float& angle)
{
    angle = angle - 90;
    if(angle < 0)
    {
        angle +=360;
    }
    angle = angle - 360;
    if(angle < 0)
    {
        angle = angle * -1;
    }
    return angle;
}

float Entity_Attack::convertDegreesToRadians(float& angle)
{
    return (angle * 3.141592 / 180);
}
