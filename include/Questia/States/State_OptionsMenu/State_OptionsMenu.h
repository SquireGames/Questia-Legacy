#ifndef STATE_OPTIONSMENU_H
#define STATE_OPTIONSMENU_H

#include <memory>

#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/Engine.h"

#include "Questia/States/State_OptionsMenu/OptionManager.h"

class State_OptionsMenu : public State
{
public:
	State_OptionsMenu();
	void init();
	~State_OptionsMenu();

	void processInput(std::u32string const& inputText);
	void update(sf::Time elapsedTime);
	void displayTextures();

private:
	//TODO make on stack
	std::unique_ptr<OptionManager> optionManager;

	std::string activeSelector = "displayList";

	///options
	//display
	Option<int> option_windowMode       {Option<int>()};
	Option<int> option_fps              {Option<int>()};
	Option<std::string> option_font     {Option<std::string>()};
	Option<std::string> option_guiPack  {Option<std::string>()};
	//audio
	Option<int> option_musicVolume      {Option<int>()};
	//input
	Option<ctr::Input> option_key_moveUp      {Option<ctr::Input>()};
	Option<ctr::Input> option_key_moveDown    {Option<ctr::Input>()};
	Option<ctr::Input> option_key_moveLeft    {Option<ctr::Input>()};
	Option<ctr::Input> option_key_moveRight   {Option<ctr::Input>()};
	Option<ctr::Input> option_key_skill_1     {Option<ctr::Input>()};
	Option<ctr::Input> option_key_skill_2     {Option<ctr::Input>()};
	Option<ctr::Input> option_key_skill_3     {Option<ctr::Input>()};
	Option<ctr::Input> option_key_skill_4     {Option<ctr::Input>()};
	Option<ctr::Input> option_key_skill_5     {Option<ctr::Input>()};
	Option<ctr::Input> option_key_skill_6	  {Option<ctr::Input>()};
};

#endif // STATE_OPTIONSMENU_H