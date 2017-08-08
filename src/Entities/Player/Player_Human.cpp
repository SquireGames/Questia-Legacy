#include "Questia/Entities/Player/Player_Human.h"

Player_Human::Player_Human(unsigned int id, EntityManager& entitiyManager, ResourceManager* resourceManager, utl::Vector2f coords):
	Entity_Player(id, entityManager, resourceManager, coords)
{

}

Player_Human::~Player_Human()
{

}
