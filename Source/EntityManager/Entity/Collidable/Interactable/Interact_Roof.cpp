#include "Interact_Roof.h"

Interact_Roof::Interact_Roof(ResourceManager &res, int _ID, int x, int y, int type, int subtype):
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
            entitySprite.setTexture(resource.getTexture("Media/Image/Game/MapEntity/Roof/Roof.png"));
            bounds = sf::Vector2f (320, 288);
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
}

Interact_Roof::~Interact_Roof()
{

}

void Interact_Roof::drawEntity(sf::RenderWindow &mWindow)
{

}

void Interact_Roof::update(int effect, int (&returnCollision)[4])
{

}

sf::Vector2f Interact_Roof::getCoordinates()
{

}

void Interact_Roof::setCoordinates(sf::Vector2f coords)
{

}

int Interact_Roof::returnID()
{

}

//Collision
sf::Vector2f Interact_Roof::getSideRadius()
{

}

sf::Vector2f Interact_Roof::getVelocity()
{

}

sf::Vector2i Interact_Roof::getMapCoordinates()
{

}


//Interaction
void Interact_Roof::checkInteraction(int x, int y,int sideRadius_x, int sideRadius_y)
{
    sf::FloatRect roof(x,y - 12,sideRadius_x,sideRadius_y + 12);
    sf::FloatRect player(coordinates.x, coordinates.y, bounds.x,bounds.y);

    if(roof.intersects(player))
    {
        interaction = true;
    }
    else
    {
        interaction = false;
    }
}

void Interact_Roof::drawLayer3(sf::RenderWindow &mWindow)
{
    if(!interaction)
    {
         mWindow.draw(entitySprite);
    }
}
