#include "StateManager/States/State_Game.h"

State_Game::State_Game(sf::RenderWindow &window):
    window(window)
    //managers
    , resourceManager()
    , guiManager(window, resourceManager)
    , guiLoader()
    , entityManager()
    , tileEngineNew(window, resourceManager)

    //keys
    , moveKey0(0)
    , moveKey1(1)
    , moveKey2(2)
    , moveKey3(3)
    , skillKey4(4)
    , skillKey5(5)
    , skillKey6(6)

    , talkKey(20)
    , toggleTalkKey(21)

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


    ///rebindable keys
    moveKey0.keyInput = sf::Keyboard::W;
    moveKey1.keyInput = sf::Keyboard::S;
    moveKey2.keyInput = sf::Keyboard::A;
    moveKey3.keyInput = sf::Keyboard::D;


    moveKey0.keyType = 0;
    //moveKey0.keyInput = Data_Desktop::getInstance().getKey(0);
    keybindVector.push_back(moveKey0);
    moveKey1.keyType = 0;
    //moveKey1.keyInput = Data_Desktop::getInstance().getKey(1);
    keybindVector.push_back(moveKey1);
    moveKey2.keyType = 0;
    //moveKey2.keyInput = Data_Desktop::getInstance().getKey(2);
    keybindVector.push_back(moveKey2);
    moveKey3.keyType = 0;
    //moveKey3.keyInput = Data_Desktop::getInstance().getKey(3);
    keybindVector.push_back(moveKey3);
    skillKey4.keyType = 0;
   // skillKey4.keyInput = Data_Desktop::getInstance().getKey(4);
    keybindVector.push_back(skillKey4);
    skillKey5.keyType = 0;
   // skillKey5.keyInput = Data_Desktop::getInstance().getKey(5);
    keybindVector.push_back(skillKey5);
    skillKey6.keyType = 0;
    //skillKey6.keyInput = Data_Desktop::getInstance().getKey(6);
    keybindVector.push_back(skillKey6);
    talkKey.keyType = 0;
    talkKey.keyInput = sf::Keyboard::Return;
    keybindVector.push_back(talkKey);
    toggleTalkKey.keyType = 0;
    toggleTalkKey.keyInput = sf::Keyboard::RControl;
    keybindVector.push_back(toggleTalkKey);

    alignment.setTexture(resourceManager.getTexture("Media/Image/Gui/Game/Alignment.png"));
    alignment2.setTexture(resourceManager.getTexture("Media/Image/Gui/Game/Alignment.png"));

    alignment2.setOrigin(1920/2, 1080/2);

    ///font
    guiManager.setFont(Data_Desktop::getInstance().font1);

    ///NEW TILE ENGINE
    tileEngineNew.loadMap("TEST");

    //temp
    visibleScreen.setPrimitiveType(sf::PrimitiveType::LinesStrip);
    visibleScreen.resize(5);
    visibleScreen.append(sf::Vertex(sf::Vector2f(0,0), sf::Color::Black));
    visibleScreen.append(sf::Vertex(sf::Vector2f(1920,0), sf::Color::Black));
    visibleScreen.append(sf::Vertex(sf::Vector2f(1920,1080), sf::Color::Black));
    visibleScreen.append(sf::Vertex(sf::Vector2f(0,1080), sf::Color::Black));
    visibleScreen.append(sf::Vertex(sf::Vector2f(0,0), sf::Color::Black));
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
        else if(key == sf::Keyboard::T)
        {
            //isInDebugMode = true;
        }
        else if(key == sf::Keyboard::Y)
        {
            //isInDebugMode = false;
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
    ///keyboard input
    int currentKey;
    for(unsigned char x = 0; x < keybindVector.size(); x++)
    {
        if(keybindVector[x].keyType == 0)
        {
            if(sf::Keyboard::isKeyPressed(keybindVector[x].keyInput))
            {
                keybindVector[x].activated = true;
                currentKey = keybindVector[x].keyNumber;

                //if(commandsManager.handleImput(currentKey, true, 0))
                //{
                 //   entityManager.handleInput(currentKey, true, 0); // player input
                //}
            }
            else
            {
                keybindVector[x].activated = false;
                currentKey = keybindVector[x].keyNumber;

                //if(commandsManager.handleImput(currentKey, false, 0))
                //{
                //    entityManager.handleInput(currentKey, false, 0); // player input
                //}
            }
        }
    }

    ///update mouse
    guiManager.setMousePosition(std::make_pair(Data_Desktop::getInstance().getScaledMousePosition(window).x,Data_Desktop::getInstance().getScaledMousePosition(window).y));

//    commandsManager.getCharImput(Data_Desktop::getInstance().getMostRecentChar());

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

    tileEngineNew.setPosition(1920/2, 1080/2);

    ///gui
    //game
    guiManager.setButtonAtr("hpBar", "percent", gui::ButtonAtrCharacteristic::percentage, 100);
    guiManager.setButtonAtr("mpBar", "percent", gui::ButtonAtrCharacteristic::percentage, 100);
    guiManager.setButtonAtr("stBar", "percent", gui::ButtonAtrCharacteristic::percentage, 100);
    //debug
    guiManager.setButtonAtr("fpsText", "text", gui::ButtonAtrCharacteristic::text, utl::asString(Data_Desktop::getInstance().get_FPS()));

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(guiManager.isClicked("mainMenu"))
        {
            StateManager::getInstance().changeState(new State_Transition(window, 1));
        }
        else if(guiManager.isClicked("exitGame"))
        {
            window.close();
        }
    }
}

void State_Game::displayTextures()
{
    window.setView(gameView);

    tileEngineNew.drawMap();
    tileEngineNew.drawTiles();

    window.draw(alignment2);

    window.setView(overlayView);

    guiManager.drawButtons();

    //window.draw(alignment);

    //temp\
    sf::View zoomOut;\
    zoomOut.setSize(1920,1080);\
    zoomOut.setCenter(1920/2, 1080/2);\
    zoomOut.zoom(1.75);\
    window.setView(zoomOut);\
    window.draw(visibleScreen);
}


