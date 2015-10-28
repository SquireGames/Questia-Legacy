#include <iostream>

#include "StateManager/States/State_CharacterSelection.h"
#include "StateManager/StateManager.h"
#include "StateManager/States/State_Transition.h"

State_CharacterSelection::State_CharacterSelection(sf::RenderWindow &mWindow):
    window(mWindow)
    , resourceManager()
    , guiManager(mWindow, resourceManager, false)
{
    background.setTexture(resourceManager.getTexture("Media/Image/Menu/Options.png"));

    guiManager.addButton(1, false, 1700, 1000, std::string("Media/Image/Menu/Buttons/Button_Editor.png"), std::string("Play"), 1760, 1005,1,30, sf::Color::Black, sf::Color(153,153,0,111));
    guiManager.addButton(2, false, 20, 1000, std::string("Media/Image/Menu/Buttons/Button_Editor.png"), std::string("Back"), 80, 1005,1,30, sf::Color::Black, sf::Color(153,153,0,111));
}

State_CharacterSelection::~State_CharacterSelection()
{

}

void State_CharacterSelection::processImput(sf::Keyboard::Key key,bool isPressed)
{

}

void State_CharacterSelection::update(sf::Time elapsedTime)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(guiManager.testButton(1))
        {
            StateManager::getInstance().changeState(new State_Transition(window, 2));
        }
        else if(guiManager.testButton(2))
        {
            StateManager::getInstance().changeState(new State_Transition(window, 1));
        }
    }
}

void State_CharacterSelection::displayTextures()
{
    window.draw(background);
    guiManager.buttonCheck();
    guiManager.drawGui();
}


