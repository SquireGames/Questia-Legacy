#ifndef INTERACT_ROOF_H
#define INTERACT_ROOF_H

#include "Entity_Interactable.h"
#include "ResourceManager.h"


class Interact_Roof : public Entity_Interactable
{
public:
    Interact_Roof(ResourceManager &res, int _ID, int x, int y, int type, int subtype);
    ~Interact_Roof();

    //Default
    void drawEntity(sf::RenderWindow &window);
    void update(int effect, int (&returnCollision)[4]);
    sf::Vector2f getCoordinates();
    void setCoordinates(sf::Vector2f coords);
    int returnID();

    //Collision
    sf::Vector2f getSideRadius();
    sf::Vector2f getVelocity();
    sf::Vector2i getMapCoordinates();

    //Interaction
    void checkInteraction(int x, int y,int sideRadius_x, int sideRadius_y);

    void drawLayer3(sf::RenderWindow &window);

private:
    ResourceManager &resource;
    int ID;

    sf::Vector2f velocity;
    sf::Vector2f coordinates;
    sf::Sprite entitySprite;
    sf::Vector2i mapCoordinates;

    sf::Vector2f bounds;
    bool interaction;
};

#endif // INTERACT_ROOF_H
