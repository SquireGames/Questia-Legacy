#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "StateManager/States/State_MainMenu.h"
#include "StateManager/StateManager.h"
#include "StateManager/States/State_Transition.h"
#include "EntityManager/SpawnManager.h"

State_MainMenu::State_MainMenu(sf::RenderWindow &mWindow):
    window(mWindow)
    , resourceManager()
    , guiManager(mWindow, resourceManager, false)

{
    aMenuImage.setTexture(resourceManager.getTexture("Media/Image/Menu/aMenu.png"));

    guiManager.addButton(1, false, 150, 400, std::string("Media/Image/Menu/Buttons/aButton.png"), std::string(""), 0,0,0,0, sf::Color::Transparent, sf::Color(153,153,0,111));
    guiManager.addButton(2, false, 150, 600, std::string("Media/Image/Menu/Buttons/aButton.png"), std::string(""), 0,0,0,0, sf::Color::Transparent, sf::Color(153,153,0,111));
    guiManager.addButton(3, false, 150, 800, std::string("Media/Image/Menu/Buttons/aButton.png"), std::string(""), 0,0,0,0, sf::Color::Transparent, sf::Color(153,153,0,111));
    guiManager.addButton(4, false, 1700, 1000, std::string("Media/Image/Menu/Buttons/Button_Editor.png"), std::string("Editor"), 1750, 1005,1,30, sf::Color::Black, sf::Color(153,153,0,111));

    aButton_PlayImage.setTexture(resourceManager.getTexture("Media/Image/Menu/Buttons/aButton_Play.png"));
    aButton_OptionsImage.setTexture(resourceManager.getTexture("Media/Image/Menu/Buttons/aButton_Options.png"));
    aButton_ExitImage.setTexture(resourceManager.getTexture("Media/Image/Menu/Buttons/aButton_Exit.png"));

    aButton_PlayImage.setPosition(180,450);
    aButton_OptionsImage.setPosition(180,650);
    aButton_ExitImage.setPosition(180,850);

    if(!musicBuffer.loadFromFile("Media/Music/gameMenu.ogg")) {}
    musicSound.setBuffer(musicBuffer);
    musicSound.setVolume(Data_Desktop::getInstance().getMusicVolume());
    musicSound.play();

    guiManager.addStats(std::string(" "), std::string("Version 0.0.14 Alpha"));
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
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(guiManager.testButton(1))
        {
            StateManager::getInstance().changeState(new State_Transition(window, 4));
        }
        else if(guiManager.testButton(2))
        {
            StateManager::getInstance().changeState(new State_Transition(window, 3));
        }
        else if(guiManager.testButton(3))
        {
            window.close();
        }
        else if(guiManager.testButton(4))
        {
            StateManager::getInstance().changeState(new State_Transition(window, 6));
        }
    }
}

void State_MainMenu::displayTextures()
{
    window.draw(aMenuImage);

    guiManager.buttonCheck();
    guiManager.drawGui();

    window.draw(aButton_PlayImage);
    window.draw(aButton_OptionsImage);
    window.draw(aButton_ExitImage);
}
