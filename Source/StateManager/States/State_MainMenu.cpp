#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "StateManager/States/State_MainMenu.h"
#include "StateManager/StateManager.h"
#include "StateManager/States/State_Transition.h"
#include "EntityManager/SpawnManager.h"

#include "Utl/Utl.h"

State_MainMenu::State_MainMenu(sf::RenderWindow &mWindow):
    window(mWindow)
    , resourceManager()
    , guiManager(mWindow, resourceManager)
    , saveFile()
{
    ///gui
    //font
    guiManager.setFont(Data_Desktop::getInstance().font1);
    //loader
    guiLoader.setGuiPack(saveFile.getGuiPack());
    guiLoader.loadGui(guiManager, "mainMenu");

    ///music
    if(!musicBuffer.loadFromFile("Media/Music/gameMenu.ogg")) {}
    musicSound.setBuffer(musicBuffer);
    musicSound.setVolume(utl::asInt(Data_Desktop::getInstance().getSaveOptions().getItem("music volume")));
    musicSound.play();
}


State_MainMenu::~State_MainMenu()
{
    std::cout<<"DEBUG: State_MainMenu Destroyed"<<std::endl;
}

void State_MainMenu::processImput(sf::Keyboard::Key key,bool isPressed)
{

}

void State_MainMenu::update(sf::Time elapsedTime)
{
    guiManager.setMousePosition(std::make_pair(Data_Desktop::getInstance().getScaledMousePosition(window).x,Data_Desktop::getInstance().getScaledMousePosition(window).y));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(guiManager.isClicked("play"))
        {
            StateManager::getInstance().changeState(new State_Transition(window, 4));
        }
        else if(guiManager.isClicked("options"))
        {
            StateManager::getInstance().changeState(new State_Transition(window, 3));
        }
        else if(guiManager.isClicked("exit"))
        {
            window.close();
        }
        else if(guiManager.isClicked("editor"))
        {
            StateManager::getInstance().changeState(new State_Transition(window, 6));
        }
        else if(guiManager.isClicked("multiplayer"))
        {
            StateManager::getInstance().changeState(new State_Transition(window, 7));
        }
    }
}

void State_MainMenu::displayTextures()
{
    guiManager.drawButtons();
}

