#include "Entity_Player.h"

Entity_Player::Entity_Player(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager):
    Entity_Living(id, entityManager, resourceManager, Bounds(Circ(13)),Bounds(Rect(utl::Vector2f(26,26), utl::Vector2f(13,13))))
{
    collBounds.rel_coords = utl::Vector2f(0, 20);
    hitBounds.rel_coords  = utl::Vector2f(0, -15);

    coords = utl::Vector2f(1000,1000);

    atrs[Type::test_attack].atrs[(int)Type_test_attack::destroyStuff] = true;
}

Entity_Player::~Entity_Player()
{
    //dtor
}

void Entity_Player::processInput(ctr::KeyAction action, bool isPressed)
{
    if(isPressed)
    {
        switch (action)
        {
        case ctr::KeyAction::MoveUp:
            isMovingUp = true;
            break;
        case ctr::KeyAction::MoveDown:
            isMovingDown = true;
            break;
        case ctr::KeyAction::MoveLeft:
            isMovingLeft = true;
            break;
        case ctr::KeyAction::MoveRight:
            isMovingRight = true;
            break;
        }
    }
    else
    {
        switch (action)
        {
        case ctr::KeyAction::MoveUp:
            isMovingUp = false;
            break;
        case ctr::KeyAction::MoveDown:
            isMovingDown = false;
            break;
        case ctr::KeyAction::MoveLeft:
            isMovingLeft = false;
            break;
        case ctr::KeyAction::MoveRight:
            isMovingRight = false;
            break;
        }
    }
}

void Entity_Player::update()
{

    switch(mov_control)
    {
    //if the player is normally moving (no movement skills)
    case MovementControl::inControl:
    {
        //calculate speed
        float mov_speed = (mov_speedBase + mov_speedModifier) * mov_speedMultiplier;

        float mov_velocity_x = 0;
        float mov_velocity_y = 0;

        //add input forces
        if(isMovingUp && !isMovingDown)
        {
            mov_velocity_y = -mov_speed;
        }
        if(isMovingDown && !isMovingUp)
        {
            mov_velocity_y = mov_speed;
        }
        if(isMovingLeft && !isMovingRight)
        {
            mov_velocity_x = -mov_speed;
        }
        if(isMovingRight && !isMovingLeft)
        {
            mov_velocity_x = mov_speed;
        }

        //find movement vector
        utl::Vector2f mov_velocity;
        if(mov_velocity_x != 0 && mov_velocity_y != 0)
        {
            mov_velocity = (utl::Vector2f(mov_velocity_x, mov_velocity_y) / std::sqrt(mov_velocity_x * mov_velocity_x + mov_velocity_y * mov_velocity_y)) * mov_speed;
        }
        else
        {
            mov_velocity = utl::Vector2f(mov_velocity_x, mov_velocity_y);
        }


        //add external forces
        if(mov_forces_external.size() > 0)
        {
            for(auto& force : mov_forces_external)
            {
                mov_velocity += force;
            }
        }

        //move player
        attemptMove(mov_velocity, *this);

        //reset forces
        mov_forces_external.clear();
    }
    break;
    case MovementControl::skillControl:
    {

    }

    default:
    {

    }
    break;
    }


}
