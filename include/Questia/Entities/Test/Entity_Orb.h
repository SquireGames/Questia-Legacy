#ifndef ENTITY_ORB_H
#define ENTITY_ORB_H

#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Obj.h"

#define S_ORB_SIZE_X 50
#define S_ORB_SIZE_Y 50

class Entity_Orb : public Entity_Obj
{
public:
	Entity_Orb(unsigned int id, EntityManager& entitiyManager, ResourceManager* resourceManager, utl::Vector2f coords);
	~Entity_Orb();
	
	virtual void update() override final;
	virtual void draw(sf::RenderWindow& window, DrawLayer drawLayer) override final;
	virtual int getGroundOffset() override final;
	
private:
	sf::Sprite sprite;
};

#endif // ENTITY_ORB_H