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

float Entity_Attack::convertDegreesToRadians(float angle)
{
    return (angle * 3.141592 / 180);
}

float Entity_Attack::convertRadiansToDegrees(float angle)
{
    return (angle * 180 / 3.141592);
}

void Entity_Attack::rotateNewPoints(float angle, sf::Vector2f coordinates, std::vector<sf::Vector2f>& _point)
{
    for(int it = 0; it != _point.size(); it++)
    {
        float sin = std::sin(angle);
        float cos = std::cos(angle);

        float x,y;

        x = _point[it].x * cos - _point[it].y * sin;
        y = _point[it].x * sin + _point[it].y * cos;

        _point[it].x =  x + coordinates.x;
        _point[it].y =  y + coordinates.y;
    }
}

void Entity_Attack::rotatePoints(float angle, sf::Vector2f coordinates, std::vector<sf::Vector2f>& _point)
{
    for(int it = 0; it != _point.size(); it++)
    {
        _point[it].x -= coordinates.x;
        _point[it].y -= coordinates.y;

        float sin = std::sin(angle);
        float cos = std::cos(angle);

        float x,y;

        x = _point[it].x * cos - _point[it].y * sin;
        y = _point[it].x * sin + _point[it].y * cos;

        _point[it].x =  x + coordinates.x;
        _point[it].y =  y + coordinates.y;
    }
}

void Entity_Attack::movePoints(float angle, sf::Vector2f& coordinates, sf::Vector2f velocity, std::vector<sf::Vector2f>& _point)
{
    float x_component, y_component;

    x_component = std::cos(angle - (.5 * 3.14159)) * velocity.x;
    y_component = std::sin(angle - (.5 * 3.14159)) * velocity.x;

    coordinates.x += x_component;
    coordinates.y += y_component;

    for(int it = 0; it != _point.size(); it++)
    {
        _point[it].x = _point[it].x + x_component;
        _point[it].y = _point[it].y + y_component;
    }
}
