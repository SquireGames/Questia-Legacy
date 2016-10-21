#ifndef STATE_MAPSELECTOR_H
#define STATE_MAPSELECTOR_H

#include <SFML/Graphics.hpp>
#include <StateManager/State.h>

#include "ResourceManager.h"
#include "GuiManager.h"
#include "Data_Desktop.h"

class State_MapSelector : public State
{
public:
    State_MapSelector(sf::RenderWindow &window);
    ~State_MapSelector();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;
};

#endif // STATE_MAPSELECTOR_H
