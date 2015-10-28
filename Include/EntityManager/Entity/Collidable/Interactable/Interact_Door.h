#ifndef INTERACT_DOOR_H
#define INTERACT_DOOR_H


#include "Entity_Interactable.h"
#include "ResourceManager.h"


class Interact_Door : public Entity_Interactable
{
public:
    Interact_Door(ResourceManager &res, int _ID, int x, int y, int type, int subtype);
    ~Interact_Door();

    //Default
    void drawEntity(sf::RenderWindow &mWindow);
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

    void drawLayer3(sf::RenderWindow &mWindow);

private:
    sf::Vector2f velocity;
    sf::Vector2f coordinates;
    sf::Sprite entitySprite;
    sf::Sprite entitySprite2;
    sf::Vector2i mapCoordinates;

    int ID;
    ResourceManager &resource;

    sf::Vector2f bounds;
    bool interaction;
};

#endif // INTERACT_DOOR_H
