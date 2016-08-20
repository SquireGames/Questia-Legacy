#include "StateManager/States/State_MainMenu.h"

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
    if(!musicBuffer.loadFromFile("Media/Sound/Music/gameMenu.ogg")) {}
    musicSound.setBuffer(musicBuffer);
    musicSound.setVolume(utl::asInt(Data_Desktop::getInstance().getSaveOptions().getItem("music volume")));
    musicSound.play();

    sf::Vertex vertexTest;

    sf::VertexArray vertexArrayTest;
    vertexArrayTest.setPrimitiveType(sf::PrimitiveType::Quads);
    vertexArrayTest.resize(4);
    vertexArrayTest[0] = vertexTest;
    vertexArrayTest[1] = vertexTest;
    vertexArrayTest[2] = vertexTest;
    vertexArrayTest[3] = vertexTest;


    std::cout << "Bytes of array:  " << sizeof(vertexArrayTest) << std::endl;
    std::cout << "Bytes of vertex: " << sizeof(vertexTest) << std::endl;
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

