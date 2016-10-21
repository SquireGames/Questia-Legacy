#ifndef STATE_TRANSITION_H
#define STATE_TRANSITION_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "StateManager/StateManager.h"
#include "StateManager/State.h"
#include "StateManager/States/State_Transition.h"

#include "StateManager/States/State_MainMenu.h"
#include "StateManager/States/State_Game.h"
#include "StateManager/States/State_OptionsMenu/State_OptionsMenu.h"
#include "StateManager/States/State_CharacterSelection.h"
#include "StateManager/States/State_TileMapEditor.h"
#include "StateManager/States/State_MapSelector.h"
#include "StateManager/States/State_MultiplayerGame.h"
#include "StateManager/States/State_MultiplayerSelection.h"

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


