#ifndef STATE_MULTIPLAYERSELECTION_H
#define STATE_MULTIPLAYERSELECTION_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <StateManager/State.h>

#include "Data_Desktop.h"
#include "ResourceManager.h"
#include "GuiManager.h"

class State_MultiplayerSelection : public State
{
public:
    State_MultiplayerSelection(sf::RenderWindow &window);
    ~State_MultiplayerSelection();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;

    sf::Sprite aMenuImage;

    ResourceManager resourceManager;
    GuiManager guiManager;
};

#endif // STATE_MULTIPLAYERSELECTION_H
