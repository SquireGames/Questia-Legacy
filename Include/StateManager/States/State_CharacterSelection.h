#ifndef STATE_CHARACTERSELECTION_H
#define STATE_CHARACTERSELECTION_H

#include <SFML/Graphics.hpp>
#include <StateManager/State.h>

#include "ResourceManager.h"
#include "GuiManager.h"

class State_CharacterSelection : public State
{
public:
    State_CharacterSelection(sf::RenderWindow &mWindow);
    ~State_CharacterSelection();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;

    sf::Sprite background;

    ResourceManager resourceManager;
    GuiManager guiManager;
};

#endif // STATE_CHARACTERSELECTION_H
