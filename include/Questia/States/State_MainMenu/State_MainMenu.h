#ifndef STATE_MAINMENU_H
#define STATE_MAINMENU_H

#include "QuestiaEng/StateManager/State.h"

#include "QuestiaEng/Utl/Controls/Input.h"

#include "QuestiaEng/Engine.h"

class State_MainMenu : public State
{
public:
	State_MainMenu();
	void init();
	~State_MainMenu();

	void processInput(std::u32string const& inputText);
	void update(sf::Time elapsedTime);
	void displayTextures();
};

#endif // STATE_MAINMENU_H
