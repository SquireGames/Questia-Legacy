#include "Questia/Entities/Test/Entity_Orb.h"

Entity_Orb::Entity_Orb(unsigned int id, EntityManager& entitiyManager, ResourceManager* resourceManager, utl::Vector2f coords):
	Entity_Obj(id, entitiyManager, resourceManager, coords)
{
	if(resourceManager != nullptr)
	{
		sprite.setTexture((*resourceManager).getTexture("Media/Image/Game/Entity/Test/Orb.png"));
		sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
		sprite.setScale(S_ORB_SIZE_X / sprite.getLocalBounds().width, S_ORB_SIZE_Y / sprite.getLocalBounds().height);
		sprite.setPosition(coords.sf());
	}
}

Entity_Orb::~Entity_Orb()
{

}

void Entity_Orb::update()
{

}

void Entity_Orb::draw(sf::RenderWindow& window, DrawLayer drawLayer)
{
	switch(drawLayer)
	{
	case DrawLayer::Entity_Regular:
		window.draw(sprite);
		break;
	default:
		break;
	}
}

int Entity_Orb::getGroundOffset()
{
	return 16;
}
