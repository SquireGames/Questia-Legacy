#ifndef STATE_MAPSELECTOR_H
#define STATE_MAPSELECTOR_H

#include <SFML/Graphics.hpp>
#include <StateManager/State.h>

class State_MapSelector : public State
{
public:
    State_MapSelector(sf::RenderWindow &mWindow);
    ~State_MapSelector();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;
};

#endif // STATE_MAPSELECTOR_H
