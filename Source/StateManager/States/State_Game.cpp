#include "StateManager/States/State_Game.h"

State_Game::State_Game(sf::RenderWindow &window):
    window(window)
    //managers
    , resourceManager()
    , guiManager(window, resourceManager)
    , guiLoader()
    , entityManager(resourceManager)
    , tileEngine(window, resourceManager)

    , threadPool()

    , saveFile()
{
    ///gui
    //font
    guiManager.setFont(Data_Desktop::getInstance().font1);
    //loader
    guiLoader.setGuiPack(saveFile.getGuiPack());
    guiLoader.loadGui(guiManager, "game");

    ///views
    gameView.setSize(1920,1080);
    gameView.setCenter(960,540);
    gameView.zoom(1.f);

    overlayView.setSize(1920,1080);
    overlayView.setCenter(960,540);
    overlayView.zoom(1.f);

    alignment.setTexture(resourceManager.getTexture("Media/Image/Gui/Game/Alignment.png"));
    alignment2.setTexture(resourceManager.getTexture("Media/Image/Gui/Game/Alignment.png"));

    alignment2.setOrigin(1920/2, 1080/2);

    ///font
    guiManager.setFont(Data_Desktop::getInstance().font1);

    ///NEW TILE ENGINE
    tileEngine.loadMap("TEST");

    //temp
    visibleScreen.setPrimitiveType(sf::PrimitiveType::LinesStrip);
    visibleScreen.resize(5);
    visibleScreen.append(sf::Vertex(sf::Vector2f(0,0), sf::Color::Black));
    visibleScreen.append(sf::Vertex(sf::Vector2f(1920,0), sf::Color::Black));
    visibleScreen.append(sf::Vertex(sf::Vector2f(1920,1080), sf::Color::Black));
    visibleScreen.append(sf::Vertex(sf::Vector2f(0,1080), sf::Color::Black));
    visibleScreen.append(sf::Vertex(sf::Vector2f(0,0), sf::Color::Black));

    ///Asynchronous tasks
    threadPool.addTask(std::bind(&State_Game::task_gui, this));
    threadPool.addTask(std::bind(&State_Game::task_lighting, this));
    threadPool.addTask(std::bind(&State_Game::task_ai, this));
    threadPool.addTask(std::bind(&State_Game::task_particles, this));
}

State_Game::~State_Game()
{
    std::cout<<"DEBUG: State_Game Destroyed"<<std::endl;
}

void State_Game::processImput(sf::Keyboard::Key key,bool isPressed)
{
    if(paused)
    {
        if(key == sf::Keyboard::Escape && isPressed == false)
        {
            guiManager.setGroupAtr("pauseMenu", gui::ButtonCharacteristic::isVisible, false);
            paused = false;
        }
    }
    else
    {
        if(key == sf::Keyboard::Tilde && !isPressed)
        {
            //guiManager.toggleOverlay();
        }
        else if(key == sf::Keyboard::Escape && isPressed == false)
        {
            guiManager.setGroupAtr("pauseMenu", gui::ButtonCharacteristic::isVisible, true);
            paused = true;
        }
    }
}

void State_Game::update(sf::Time elapsedTime)
{
    gameLogic();
    threadPool.runTasks();

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(guiManager.isClicked("mainMenu"))
        {
            threadPool.kill();
            StateManager::getInstance().changeState(new State_Transition(window, 1));
        }
        else if(guiManager.isClicked("exitGame"))
        {
            threadPool.kill();
            window.close();
        }
    }
}

void State_Game::gameLogic()
{
    if(!paused)
    {
        //Angle
        float angle = atan2(Data_Desktop::getInstance().getScaledMousePosition(window).y - 540, Data_Desktop::getInstance().getScaledMousePosition(window).x - 960);
        angle = angle * 180 / 3.14159265;
        if(angle<0)
        {
            angle = angle*-1;
        }
        else
        {
            angle = angle -360;
            angle = angle * -1;
        }
        playerAngle = angle;
    }

    gameView.setCenter(sf::Vector2f (1920/2, 1080/2));

    tileEngine.setPosition(1920/2, 1080/2);

    entityManager.update();
}

void State_Game::task_lighting()
{

}

void State_Game::task_ai()
{

}

void State_Game::task_particles()
{

}

void State_Game::task_gui()
{
    //update mouse
    guiManager.setMousePosition(std::make_pair(Data_Desktop::getInstance().getScaledMousePosition(window).x,Data_Desktop::getInstance().getScaledMousePosition(window).y));

    //game
    guiManager.setButtonAtr("hpBar", "percent", gui::ButtonAtrCharacteristic::percentage, 100);
    guiManager.setButtonAtr("mpBar", "percent", gui::ButtonAtrCharacteristic::percentage, 100);
    guiManager.setButtonAtr("stBar", "percent", gui::ButtonAtrCharacteristic::percentage, 100);
    //debug
    guiManager.setButtonAtr("fpsText", "text", gui::ButtonAtrCharacteristic::text, utl::asString(Data_Desktop::getInstance().get_FPS()));
}

void State_Game::displayTextures()
{
    window.setView(gameView);

    tileEngine.drawMap();
    //tileEngine.drawTiles();

    entityManager.draw(window, DrawLayer::Entity_Regular);

    window.draw(alignment2);

    window.setView(overlayView);

    guiManager.drawButtons();

    //window.draw(alignment);

    //temp
    /* *
    sf::View zoomOut;
    zoomOut.setSize(1920,1080);
    zoomOut.setCenter(1920/2, 1080/2);
    zoomOut.zoom(1.75);
    window.setView(zoomOut);
    window.draw(visibleScreen);
    //\
    */
}


