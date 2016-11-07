#include "Entity_Orb.h"

Entity_Orb::Entity_Orb(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager, utl::Vector2f _coords):
    Entity_Obj(id, entityManager, resourceManager)
{
    coords = _coords;

    //set sprite
    sprite.setTexture(resourceManager.getTexture("Media/Image/Game/Entity/Test/Orb.png"));
    sprite.setScale(SIZE_X / sprite.getLocalBounds().width, SIZE_Y / sprite.getLocalBounds().height);
}

Entity_Orb::~Entity_Orb()
{

}

void Entity_Orb::update()
{
    sprite.setPosition(coords.sf());
}

void Entity_Orb::draw(sf::RenderWindow& window, const DrawLayer& drawLayer)
{
    switch (drawLayer)
    {
    case DrawLayer::Entity_Regular:
        window.draw(sprite);
        break;
    case DrawLayer::Entity_Top:
        break;
    default:
        break;
    }
}
