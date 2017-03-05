#ifndef STATE_CHARACTERSELECTION_H
#define STATE_CHARACTERSELECTION_H

#include "Questia/StateManager/State.h"

#include "Questia/ResourceManager/ResourceManager.h"
#include "Questia/GuiManager/GuiManager.h"
#include "Questia/Utl/SaveFile/SaveFile.h"

class State_CharacterSelection : public State
{
public:
    State_CharacterSelection(sf::RenderWindow &window);
    ~State_CharacterSelection();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;
};

#endif // STATE_CHARACTERSELECTION_H
