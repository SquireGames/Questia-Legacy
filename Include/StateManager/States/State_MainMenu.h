#ifndef STATE_MAINMENU_H
#define STATE_MAINMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <StateManager/State.h>

#include "Data_Desktop.h"
#include "ResourceManager.h"
#include "GuiManager.h"
#include "Data/CommandsManager.h"

class State_MainMenu : public State
{
public:
    State_MainMenu(sf::RenderWindow &mWindow);
    ~State_MainMenu();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;


    sf::Sprite aMenuImage;

    sf::Sprite aButton_PlayImage;
    sf::Sprite aButton_OptionsImage;
    sf::Sprite aButton_ExitImage;

    sf::SoundBuffer musicBuffer;
    sf::Sound musicSound;

    ResourceManager resourceManager;
    GuiManager guiManager;
    GuiManagerNew guiManagerNew;
};

#endif // STATE_MAINMENU_H
