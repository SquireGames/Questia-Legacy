#include "Entity_Player.h"

Entity_Player::Entity_Player(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager):
    Entity_Living(id, entityManager, resourceManager, Bounds(Circ(10)),Bounds(Circ(15)))
{
    collBounds.rel_coords = utl::Vector2f(0, 20);
    hitBounds.rel_coords  = utl::Vector2f(0, -15);
}

Entity_Player::~Entity_Player()
{
    //dtor
}

void Entity_Player::processInput(ctr::KeyAction action, bool isPressed)
{
    //temp
    if(isPressed)
    {
        switch (action)
        {
        case ctr::KeyAction::MoveUp:
            coords.y--;
            coords.y--;
            break;
        case ctr::KeyAction::MoveDown:
            coords.y++;
            coords.y++;
            break;
        case ctr::KeyAction::MoveLeft:
            coords.x--;
            coords.x--;
            break;
        case ctr::KeyAction::MoveRight:
            coords.x++;
            coords.x++;
            break;
        }
    }

}
