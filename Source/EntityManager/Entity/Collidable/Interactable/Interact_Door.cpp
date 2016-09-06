#include "EntityManager/Entity/Collidable/Interactable/Interact_Door.h"

Interact_Door::Interact_Door (ResourceManager &res, int _ID, int x, int y, int type, int subtype):
    resource(res)
    , ID(_ID)
    , coordinates(sf::Vector2f(x,y))
    , interaction(false)
{
    switch (type)
    {
    case 1:
    {
        switch (subtype)
        {
        case 1:
        {
            entitySprite.setTexture(resource.getTexture("Media/Image/Game/MapEntity/Door/Door_1a.png"));
            entitySprite2.setTexture(resource.getTexture("Media/Image/Game/MapEntity/Door/Door_1b.png"));

            bounds = sf::Vector2f (64, 32);
            break;
        }

        case 2:
        {
            break;
        }

        }
        break;
    }

    case 2:
    {
        break;
    }
    }
    entitySprite.setPosition(coordinates);
    entitySprite2.setPosition(coordinates);
}

Interact_Door::~Interact_Door()
{

}

void Interact_Door::drawEntity(sf::RenderWindow &window)
{

}

void Interact_Door::update(int effect, int (&returnCollision)[4])
{

}

sf::Vector2f Interact_Door::getCoordinates()
{

}

void Interact_Door::setCoordinates(sf::Vector2f coords)
{

}

int Interact_Door::returnID()
{

}

//Collision
sf::Vector2f Interact_Door::getSideRadius()
{

}

sf::Vector2f Interact_Door::getVelocity()
{

}

sf::Vector2i Interact_Door::getMapCoordinates()
{

}


//Interaction
void Interact_Door::checkInteraction(int x, int y,int sideRadius_x, int sideRadius_y)
{
    sf::FloatRect door(x,y - 32,sideRadius_x,sideRadius_y + 32);
    sf::FloatRect player(coordinates.x, coordinates.y, bounds.x,bounds.y);

    if(door.intersects(player))
    {
        interaction = true;
    }
    else
    {
        interaction = false;
    }
}

void Interact_Door::drawLayer3(sf::RenderWindow &window)
{
    if(!interaction)
    {
        window.draw(entitySprite);
    }
    else
    {
        window.draw(entitySprite2);
    }
}
