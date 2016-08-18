#include "StateManager/States/State_MainMenu.h"

State_MainMenu::State_MainMenu(sf::RenderWindow &mWindow):
    window(mWindow)
    , resourceManager()
    , guiManager(mWindow, resourceManager)
    , saveFile()
    , textureAtlasData(nullptr)
{
    ///gui
    //font
    guiManager.setFont(Data_Desktop::getInstance().font1);
    //loader
    guiLoader.setGuiPack(saveFile.getGuiPack());
    guiLoader.loadGui(guiManager, "mainMenu");

    ///music
    if(!musicBuffer.loadFromFile("Media/Sound/Music/gameMenu.ogg")) {}
    musicSound.setBuffer(musicBuffer);
    musicSound.setVolume(utl::asInt(Data_Desktop::getInstance().getSaveOptions().getItem("music volume")));
    musicSound.play();

    //TEMP
    TextureAtlas textureAtlas(resourceManager);
    textureAtlas.addTexture("Media/Image/Game/Tiles/01/01.png", "1");
    textureAtlas.addTexture("Media/Image/Game/Tiles/04/21.png", "2");
    textureAtlasData = std::move (textureAtlas.compileTextures("kekman"));

    tempSprite.setTexture(*textureAtlasData.texture);
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
    window.draw(tempSprite);
}

