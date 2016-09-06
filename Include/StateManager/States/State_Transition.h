#ifndef STATE_TRANSITION_H
#define STATE_TRANSITION_H

#include <SFML/Graphics.hpp>
#include "StateManager/State.h"


class State_Transition : public State
{
public:
    State_Transition(sf::RenderWindow &window, int stateID);
    ~State_Transition();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;

    int stateID;

    sf::Texture aLoadingTexture;
    sf::Sprite aLoadingImage;
};

#endif // STATE_TRANSITION_H


