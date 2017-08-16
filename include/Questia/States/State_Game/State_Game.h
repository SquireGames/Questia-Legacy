#ifndef STATE_GAME_H
#define STATE_GAME_H

#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/Engine.h"

#include "QuestiaEng/Utl/Type/Vector2.h"

#include "QuestiaEng/Identifiers/DrawLayer.h"

#include "QuestiaEng/Utl/Controls/KeyAction.h"
#include "QuestiaEng/Utl/Controls/MouseListener.h"

#include "QuestiaEng/Utl/Threads/ThreadPool_Fixed.h"

#include "Questia/Entities/Test/Entity_Orb.h"

class State_Game : public State
{
public:
	State_Game();
	virtual void init() final;
	~State_Game();

	virtual void processInput(std::u32string const& inputText) final;
	virtual void update(sf::Time elapsedTime) final;
	virtual void displayTextures() final;

private:
	ThreadPool_Fixed threadPool;

	utl::Vector2f pos;

	sf::View gameView;
	sf::View guiView;
};

#endif // STATE_GAME_H
