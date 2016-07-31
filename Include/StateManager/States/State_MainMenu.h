#ifndef STATE_MAINMENU_H
#define STATE_MAINMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <StateManager/State.h>

#include "GuiLoader.h"

#include "Data_Desktop.h"
#include "ResourceManager.h"
#include "GuiManager.h"

class State_MainMenu : public State
{
public:
    State_MainMenu(sf::RenderWindow &mWindow);
    ~State_MainMenu();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    GuiLoader guiLoader;

    sf::RenderWindow& window;

    sf::SoundBuffer musicBuffer;
    sf::Sound musicSound;

    ResourceManager resourceManager;
    GuiManagerNew guiManager;
};

#endif // STATE_MAINMENU_H
