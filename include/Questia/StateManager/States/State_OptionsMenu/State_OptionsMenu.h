#ifndef STATE_OPTIONSMENU_H
#define STATE_OPTIONSMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Questia/Data/Data_Desktop.h"

#include "Questia/StateManager/State.h"
#include "Questia/StateManager/StateManager.h"
#include "Questia/StateManager/States/State_Transition.h"

#include "Questia/ResourceManager/ResourceManager.h"
#include "Questia/GuiManager/GuiManager.h"
#include "Questia/GuiManager/GuiLoader.h"

#include "Questia/Utl/Utl.h"
#include "Questia/Utl/FileData.h"

#include "Questia/StateManager/States/State_OptionsMenu/Option.h"
#include "Questia/StateManager/States/State_OptionsMenu/Option_Base.h"
#include "Questia/StateManager/States/State_OptionsMenu/OptionManager.h"

#include "Questia/Utl/Controls/Keyboard.h"

#include "Questia/Utl/SaveFile/SaveFile_Options.h"

class State_OptionsMenu : public State
{
public:
    State_OptionsMenu(sf::RenderWindow &window);
    ~State_OptionsMenu();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;

    std::string activeSelector;
    bool key_up_isPressed;
    bool key_down_isPressed;

    ResourceManager resourceManager;
    GuiManager guiManager;
    OptionManager optionManager;

    SaveFile_Options saveFile;
    GuiLoader guiLoader;

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
    Option<ctr::Input> option_key_skill_6     {Option<ctr::Input>()};
    //game
    //Option<void> option_deleteData       {Option<void>()};
};

#endif // STATE_OPTIONSMENU_H