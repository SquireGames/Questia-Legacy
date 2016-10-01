#ifndef STATE_OPTIONSMENU_H
#define STATE_OPTIONSMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Data_Desktop.h"

#include "StateManager/State.h"
#include "StateManager/StateManager.h"
#include "StateManager/States/State_Transition.h"

#include "ResourceManager.h"
#include "GuiManager.h"
#include "GuiLoader.h"

#include "Utl/Utl.h"
#include "FileData.h"

#include "StateManager/States/State_OptionsMenu/Option.h"
#include "Option_Base.h"
#include "OptionManager.h"

#include "SaveFile_Options.h"

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
    GuiManagerNew guiManager;
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
    Option<char> option_key_moveUp      {Option<char>()};
    Option<char> option_key_moveDown    {Option<char>()};
    Option<char> option_key_moveLeft    {Option<char>()};
    Option<char> option_key_moveRight   {Option<char>()};
    Option<char> option_key_skill_1     {Option<char>()};
    Option<char> option_key_skill_2     {Option<char>()};
    Option<char> option_key_skill_3     {Option<char>()};
    Option<char> option_key_skill_4     {Option<char>()};
    Option<char> option_key_skill_5     {Option<char>()};
    Option<char> option_key_skill_6     {Option<char>()};
    //game
    //Option<int> option_deleteData       {Option<int>()};
};

#endif // STATE_OPTIONSMENU_H
