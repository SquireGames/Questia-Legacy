#include <iostream>

#include "StateManager/StateManager.h"
#include "StateManager/States/State_Transition.h"

#include "StateManager/States/State_MainMenu.h"
#include "StateManager/States/State_Game.h"
#include "StateManager/States/State_OptionsMenu/State_OptionsMenu.h"
#include "StateManager/States/State_CharacterSelection.h"
#include "StateManager/States/State_TileMapEditor.h"
#include "StateManager/States/State_MapSelector.h"
#include "StateManager/States/State_MultiplayerGame.h"
#include "StateManager/States/State_MultiplayerSelection.h"


State_Transition::State_Transition(sf::RenderWindow &window, int stateID):
    window(window)
    , stateID(stateID)
{
    std::cout<<"DEBUG: Transition Initialized"<<std::endl;

    if(!aLoadingTexture.loadFromFile("Media/Image/Gui/Menu/BasicLoading.png")) {}
    aLoadingImage.setTexture(aLoadingTexture);
    aLoadingImage.setPosition(0.f,0.f);

    sf::View normalView;
    normalView.setSize(1920,1080);
    normalView.setCenter(960,540);
    window.setView(normalView);
}

State_Transition::~State_Transition()
{
    std::cout<<std::endl;
    std::cout<<"DEBUG: Transition Destroyed"<<std::endl;
    std::cout<<std::endl;
}

void State_Transition::processImput(sf::Keyboard::Key key,bool isPressed)
{

}

void State_Transition::update(sf::Time elapsedTime)
{

}

void State_Transition::displayTextures()
{
    window.draw(aLoadingImage);
    window.display();

    //sf::Time loadingTime = sf::seconds(0.05);
    //sf::sleep(loadingTime);

    window.draw(aLoadingImage);
    std::cout<<std::endl;
    switch (stateID)
    {
    case 1:
        std::cout<<"--------------------"<<std::endl;
        std::cout<<"DEBUG: State_MainMenu Initialized"<<std::endl;
        std::cout<<"--------------------"<<std::endl;
        StateManager::getInstance().changeState(new State_MainMenu(window));
        break;
    case 2:
        std::cout<<"--------------------"<<std::endl;
        std::cout<<"DEBUG: State_Game Initialized"<<std::endl;
        std::cout<<"--------------------"<<std::endl;
        StateManager::getInstance().changeState(new State_Game(window));
        break;
    case 3:
        std::cout<<"--------------------"<<std::endl;
        std::cout<<"DEBUG: State_OptionsMenu Initialized"<<std::endl;
        std::cout<<"--------------------"<<std::endl;
        StateManager::getInstance().changeState(new State_OptionsMenu(window));
        break;
    case 4:
        std::cout<<"--------------------"<<std::endl;
        std::cout<<"DEBUG: State_CharacterSelection Initialized"<<std::endl;
        std::cout<<"--------------------"<<std::endl;
        StateManager::getInstance().changeState(new State_CharacterSelection(window));
        break;
    case 5:
        std::cout<<"--------------------"<<std::endl;
        std::cout<<"DEBUG: State_TileMapEditor Initialized"<<std::endl;
        std::cout<<"--------------------"<<std::endl;
        StateManager::getInstance().changeState(new State_TileMapEditor(window));
        break;
    case 6:
        std::cout<<"--------------------"<<std::endl;
        std::cout<<"DEBUG: State_MapSelector Initialized"<<std::endl;
        std::cout<<"--------------------"<<std::endl;
        StateManager::getInstance().changeState(new State_MapSelector(window));
        break;
    case 7:
        std::cout<<"--------------------"<<std::endl;
        std::cout<<"DEBUG: State_MultiplayerGame Initialized"<<std::endl;
        std::cout<<"--------------------"<<std::endl;
        StateManager::getInstance().changeState(new State_MultiplayerGame(window));
        break;
    case 8:
        std::cout<<"--------------------"<<std::endl;
        std::cout<<"DEBUG: State_MultiplayerSelection Initialized"<<std::endl;
        std::cout<<"--------------------"<<std::endl;
        StateManager::getInstance().changeState(new State_MultiplayerSelection(window));
        break;
    }
}




