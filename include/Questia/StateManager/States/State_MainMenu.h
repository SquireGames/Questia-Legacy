#ifndef STATE_MAINMENU_H
#define STATE_MAINMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include "Questia/StateManager/State.h"
#include "Questia/StateManager/StateManager.h"
#include "Questia/StateManager/States/State_Transition.h"

#include "Questia/GuiManager/GuiLoader.h"

#include "Questia/Data/Data_Desktop.h"
#include "Questia/ResourceManager/ResourceManager.h"
#include "Questia/GuiManager/GuiManager.h"

#include "Questia/Utl/SaveFile/SaveFile_Options.h"
#include "Questia/Utl/SaveFile/SaveFile.h"

#include "Questia/Utl/Utl.h"

class State_MainMenu : public State
{
public:
    State_MainMenu(sf::RenderWindow &window);
    ~State_MainMenu();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    GuiLoader guiLoader;

    SaveFile_Options saveFile;

    sf::RenderWindow& window;

    sf::SoundBuffer musicBuffer;
    sf::Sound musicSound;

    ResourceManager resourceManager;
    GuiManager guiManager;
};

#endif // STATE_MAINMENU_H
