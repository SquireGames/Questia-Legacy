#ifndef PLAYER_HUMAN_H
#define PLAYER_HUMAN_H

#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Coll/Entity_Living/Entity_Player/Entity_Player.h" // Base class: Entity_Player

class Player_Human : public Entity_Player
{
public:
	Player_Human(unsigned int id, EntityManager& entitiyManager, ResourceManager& resourceManager, utl::Vector2f coords);
	~Player_Human();
};

#endif // PLAYER_HUMAN_H
