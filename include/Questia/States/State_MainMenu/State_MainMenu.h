#ifndef STATE_MAINMENU_H
#define STATE_MAINMENU_H

#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/Engine.h"

class State_MainMenu : public State
{
public:
	State_MainMenu();
	virtual void init() final;
	~State_MainMenu();

	virtual void processInput(std::u32string const& inputText) final;
	virtual void update(sf::Time elapsedTime) final;
	virtual void displayTextures() final;
};

#endif // STATE_MAINMENU_H
