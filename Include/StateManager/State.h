#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

class State
{
public:
    State();
    virtual ~State();

    virtual void processImput(sf::Keyboard::Key key,bool isPressed) = 0;
    virtual void update(sf::Time elapsedTime) = 0;
    virtual void displayTextures() = 0;
};

#endif // STATE_H
