#ifndef STATE_GAME_H
#define STATE_GAME_H

#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/Engine.h"

#include "QuestiaEng/Utl/Type/Vector2.h"

#include "QuestiaEng/Utl/Controls/KeyAction.h"
#include "QuestiaEng/Utl/Controls/MouseListener.h"

class State_Game : public State
{
public:
	State_Game();
	void init();
	~State_Game();

	void processInput(std::u32string const& inputText);
	void update(sf::Time elapsedTime);
	void displayTextures();

private:
	utl::Vector2f pos;

	sf::View gameView;
	sf::View guiView;
};

#endif // STATE_GAME_H
