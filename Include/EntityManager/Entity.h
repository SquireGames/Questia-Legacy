#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class Entity
{
public:
    Entity();
    ~Entity();

    virtual void drawEntity(sf::RenderWindow &mWindow) = 0;
    virtual void update(int effect, int (&returnCollision)[4]) = 0;
    virtual sf::Vector2f getCoordinates() = 0;

    virtual int returnID() = 0;

protected:
private:
    //sf::Vector2f coordinates;
    //sf::Sprite entitySprite;
    //sf::Vector2i mapCoordinates;
};

#endif // ENTITY_H
