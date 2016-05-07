#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "StateManager/States/State_MainMenu.h"
#include "StateManager/StateManager.h"
#include "StateManager/States/State_Transition.h"
#include "EntityManager/SpawnManager.h"

#include "Utl.h"

State_MainMenu::State_MainMenu(sf::RenderWindow &mWindow):
    window(mWindow)
    , resourceManager()
    , guiManager(mWindow, resourceManager)
{
    ///background
    aMenuImage.setTexture(resourceManager.getTexture("Media/Image/Menu/aMenu.png"));

    ///music
    if(!musicBuffer.loadFromFile("Media/Music/gameMenu.ogg")) {}
    musicSound.setBuffer(musicBuffer);
    musicSound.setVolume(utl::asNumber(Data_Desktop::getInstance().getSaveOptions().getItem("music volume")));
    musicSound.play();

    ///gui
    createGui();
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
    window.draw(aMenuImage);
    guiManager.drawButtons();
}

void State_MainMenu::createGui()
{
    ///font
    guiManager.setFont(Data_Desktop::getInstance().font1);

    ///version text
    guiManager.createButton("versionText");
    guiManager.createButtonAtr("versionText", "text", gui::ButtonAtr::Text);
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::text, "Version 0.1.0 Alpha");
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::coords, std::make_pair(25,15));
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::charSize, 30);
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::color, sf::Color::Yellow);

    ///3 main button template
    guiManager.createButtonTemplate("mainTemplate");
    //sprite
    guiManager.createButtonAtr("mainTemplate", "buttonSprite", gui::ButtonAtr::Sprite);
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::texture, "Media/Image/Menu/Buttons/aButton.png");
    //text
    guiManager.createButtonAtr("mainTemplate", "text", gui::ButtonAtr::Text);
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::coords, std::make_pair(35,35));
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::charSize, 80);
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::color, sf::Color::Black);
    //bounds
    guiManager.setButton("mainTemplate", gui::ButtonCharacteristic::bounds, "buttonSprite");
    //hover
    guiManager.createButtonAtr("mainTemplate", "hover", gui::ButtonAtr::Hover);
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::color, sf::Color (153,153,0,111));

    ///main buttons
    //play
    guiManager.createButton("play", "mainTemplate");
    guiManager.setButton("play", gui::ButtonCharacteristic::coords, std::make_pair(150, 400));
    guiManager.setButtonAtr("play", "text", gui::ButtonAtrCharacteristic::text, "Play");
    //options
    guiManager.createButton("options", "mainTemplate");
    guiManager.setButton("options", gui::ButtonCharacteristic::coords, std::make_pair(150, 600));
    guiManager.setButtonAtr("options", "text", gui::ButtonAtrCharacteristic::text, "Options");
    //exit
    guiManager.createButton("exit", "mainTemplate");
    guiManager.setButton("exit", gui::ButtonCharacteristic::coords, std::make_pair(150, 800));
    guiManager.setButtonAtr("exit", "text", gui::ButtonAtrCharacteristic::text, "Exit");

    ///editor button
    guiManager.createButton("editor");
    //sprite
    guiManager.createButtonAtr("editor", "buttonSprite", gui::ButtonAtr::Sprite);
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::texture, "Media/Image/Menu/Buttons/Button_Editor.png");
    //text
    guiManager.createButtonAtr("editor", "text", gui::ButtonAtr::Text);
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::coords, std::make_pair(53,7));
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::charSize, 30);
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::color, sf::Color::Black);
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::text, "Editor");
    //bounds
    guiManager.setButton("editor", gui::ButtonCharacteristic::bounds, "buttonSprite");
    //hover
    guiManager.createButtonAtr("editor", "hover", gui::ButtonAtr::Hover);
    guiManager.setButtonAtr(gui::ButtonAtrCharacteristic::color, sf::Color (153,153,0,111));
    //position
    guiManager.setButton("editor", gui::ButtonCharacteristic::coords, std::make_pair(1700, 1000));

    ///multiplayer
    guiManager.createButton("multiplayer", "editor");
    //text
    guiManager.setButtonAtr("multiplayer", "text", gui::ButtonAtrCharacteristic::text, "Multi");
    //position
    guiManager.setButton("multiplayer", gui::ButtonCharacteristic::coords, std::make_pair(1700, 920));
}
