#include <iostream>
#include <sstream>
#include <math.h>
#include <tuple>
#include <string>

#include "StateManager/StateManager.h"
#include "StateManager/States/State_Game.h"
#include "StateManager/States/State_Transition.h"

#include "MultiplayerManager/Struct_Character.h"

State_Game::State_Game(sf::RenderWindow &mWindow):
    window(mWindow)
    //managers
    , resourceManager()
    , timeManager(0,0)
    , lightManager(mWindow, timeManager, resourceManager)
    , tileEngine (mWindow, resourceManager)
    , guiManager(mWindow, resourceManager, true)
    , entityManager (mWindow, resourceManager, lightManager, sf::Vector2f(800,2400))
    , spawnManager (true, entityManager)
    , characterManager(mWindow, entityManager, guiManager)
    , itemManager(mWindow, resourceManager)
    , commandsManager(mWindow, entityManager)

    , multiplayerManager()

    //character info
    , player_Velocity(1,1)
    , player_MapCoordinates(0,0)
    , playerAngle(0)

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

    //etc
    , pause(false)
    , tick (0)
{
    //std::vector<std::string> path = Data_Desktop::getInstance().getFiles("Maps");

    guiManager.addButton(100, true, 0, 0, std::string("Media/Image/Game/Gui/PauseOverlay.png"),std::string(""), 30, 30, 1, 50, sf::Color::Transparent, sf::Color(123, 123, 123, 0));
    guiManager.addButton(101, true, 753, 400, std::string("Media/Image/Game/Gui/Buttons/PauseButton.png"),std::string("Main Menu"), 845, 410, 1, 50, sf::Color::Black, sf::Color(123, 123, 123, 100));
    guiManager.addButton(102, true, 753, 600, std::string("Media/Image/Game/Gui/Buttons/PauseButton.png"),std::string("Exit Game"), 845, 610, 1, 50, sf::Color::Black, sf::Color(123, 123, 123, 100));

    //views
    gameView.setSize(1920,1080);
    gameView.setCenter(960,540);
    gameView.zoom(0.5);

    overlayView.setSize(1920,1080);
    overlayView.setCenter(960,540);
    overlayView.zoom(1);

    //character
    entityManager.createEntity(0, sf::Vector2f(std::atoi(Data_Desktop::getInstance().getSaved_coordinates_x().c_str()),std::atoi(Data_Desktop::getInstance().getSaved_coordinates_y().c_str())));

    //light init
    lightManager.setLightOverlay_Coords(entityManager.getPlayerCoordinates());

    //loading the map
    tileEngine.loadMap(Data_Desktop::getInstance().getMapSelection(), true);
    spawnManager.loadSpawnFile(Data_Desktop::getInstance().getMapSelection());

    //rebindable keys
    moveKey0.keyType = 0;
    moveKey0.keyInput = Data_Desktop::getInstance().getKey(0);
    keybindVector.push_back(moveKey0);
    moveKey1.keyType = 0;
    moveKey1.keyInput = Data_Desktop::getInstance().getKey(1);
    keybindVector.push_back(moveKey1);
    moveKey2.keyType = 0;
    moveKey2.keyInput = Data_Desktop::getInstance().getKey(2);
    keybindVector.push_back(moveKey2);
    moveKey3.keyType = 0;
    moveKey3.keyInput = Data_Desktop::getInstance().getKey(3);
    keybindVector.push_back(moveKey3);
    skillKey4.keyType = 0;
    skillKey4.keyInput = Data_Desktop::getInstance().getKey(4);
    keybindVector.push_back(skillKey4);
    skillKey5.keyType = 0;
    skillKey5.keyInput = Data_Desktop::getInstance().getKey(5);
    keybindVector.push_back(skillKey5);
    skillKey6.keyType = 0;
    skillKey6.keyInput = Data_Desktop::getInstance().getKey(6);
    keybindVector.push_back(skillKey6);
    talkKey.keyType = 0;
    talkKey.keyInput = sf::Keyboard::Return;
    keybindVector.push_back(talkKey);
    toggleTalkKey.keyType = 0;
    toggleTalkKey.keyInput = sf::Keyboard::RControl;
    keybindVector.push_back(toggleTalkKey);

    lightManager.create_lightSource(sf::Vector2f(22*32 + 3,17*32), 100, 2, sf::Vector2f(32 * 10 - 6,32 * 9));
    lightManager.create_lightSource(sf::Vector2f(23*32 + 12,26*32), 100, 3, sf::Vector2f(200,200));
    lightManager.create_lightSource(sf::Vector2f(30*32 + 12,26*32), 100, 3, sf::Vector2f(200,200));
    //lightManager.create_lightSource(sf::Vector2f(20,20), 50, 2, sf::Vector2f(120,120));


    //lightManager.delete_lightSource(2);


    alignment.setTexture(resourceManager.getTexture("Media/Image/Alignment.png"));
}

State_Game::~State_Game()
{
    std::cout<<"DEBUG: State_Game Destroyed"<<std::endl;
}

void State_Game::processImput(sf::Keyboard::Key key,bool isPressed)
{
    if(!pause)
    {
        int currentKey;
        for(unsigned char x = 0; x < keybindVector.size(); x++)
        {
            if(keybindVector[x].keyType == 0)
            {
                if(key == keybindVector[x].keyInput)
                {
                    keybindVector[x].activated = isPressed;
                    currentKey = keybindVector[x].keyNumber;
                    x = keybindVector.size();
                }
            }
        }

        if(commandsManager.handleImput(currentKey, isPressed, 0))
        {
            entityManager.handleInput(currentKey, isPressed, 0); // player input
        }

        if(key == sf::Keyboard::Tilde && !isPressed)
        {
            guiManager.toggleOverlay();
        }
        else if(key == sf::Keyboard::H)
        {
            multiplayerManager.startServer(7777);
        }
        else if(key == sf::Keyboard::J)
        {
            multiplayerManager.joinServer("192.168.2.77", 7777);
        }
    }

    if(key == sf::Keyboard::Escape)
    {
        Data_Desktop::getInstance().writeGameOptions(entityManager.getPlayerCoordinates());
        if(guiManager.buttonTimer())
        {
            if(!pause)
            {
                guiManager.changeVisibility(100, false);
                guiManager.changeVisibility(101, false);
                guiManager.changeVisibility(102, false);

                entityManager.handleInput(0, false, 0);
                entityManager.handleInput(1, false, 0);
                entityManager.handleInput(2, false, 0);
                entityManager.handleInput(3, false, 0);
                pause = true;
            }
            else
            {
                guiManager.changeVisibility(100, true);
                guiManager.changeVisibility(101, true);
                guiManager.changeVisibility(102, true);
                pause = false;
            }
        }
    }
}

void State_Game::update(sf::Time elapsedTime)
{
    commandsManager.getCharImput(Data_Desktop::getInstance().getMostRecentChar());
    commandsManager.update();

    tick++;
    if(tick >= 144)
    {
        tick = 0;
    }

    if(tick == 0)
    {
        timeManager.update();
        lightManager.updateLighting();
    }

    if(!pause)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            entityManager.doAttack(1, playerAngle, entityManager.getPlayerID(), entityManager.getPlayerCoordinates().x,  entityManager.getPlayerCoordinates().y);
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            entityManager.doAttack(2, playerAngle, entityManager.getPlayerID(), entityManager.getPlayerCoordinates().x,  entityManager.getPlayerCoordinates().y);
            guiManager.changeVisibility(1, false);
        }

        //Angle
        float angle = atan2(Data_Desktop::getInstance().getScaledMousePosition(window).y - 540, Data_Desktop::getInstance().getScaledMousePosition(window).x - 960);
        angle = angle * 180 / 3.14159265;

        //Coordinates
        player_MapCoordinates.x = (int)entityManager.getPlayerCoordinates().x/32 + 1;
        player_MapCoordinates.y = (int)entityManager.getPlayerCoordinates().y/32 + 1;
        tempCoords_x = player_MapCoordinates.x-1;
        tempCoords_y = player_MapCoordinates.y-1;

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

    entityManager.update(tileEngine, player_MapCoordinates, Data_Desktop::getInstance().getScaledMousePosition(window), playerAngle);
    spawnManager.checkSpawns();



    gameView.setCenter(entityManager.getPlayerCoordinates());
    lightManager.setLightOverlay_Coords(entityManager.getPlayerCoordinates());


    //lightManager.moveLightSource(1,entityManager.getPlayerCoordinates());
    /*
    lightManager.moveLightSource(2,entityManager.getPlayerCoordinates());
    lightManager.moveLightSource(3,entityManager.getPlayerCoordinates());
    lightManager.moveLightSource(4,entityManager.getPlayerCoordinates());
    lightManager.moveLightSource(5,entityManager.getPlayerCoordinates());
    lightManager.moveLightSource(6,entityManager.getPlayerCoordinates());
    lightManager.moveLightSource(7,entityManager.getPlayerCoordinates());
    lightManager.moveLightSource(8,entityManager.getPlayerCoordinates());
    */



    //Multi-player
    if(multiplayerManager.isRunningServer())
    {
        std::string a = "Hosting Server";
    }
    else if(multiplayerManager.isClient())
    {
        std::string a = "Joining Server";
    }
    if(multiplayerManager.isRunningServer())
    {
        multiplayerManager.server_recievePackets();
    }
    if (multiplayerManager.isClient())
    {
        multiplayerManager.client_recievePackets();
    }


    /* Gui */
    guiManager.addStats(std::string("FPS: "), Data_Desktop::getInstance().get_FPS());
    guiManager.addStats(std::string("Coordinates: "), tempCoords_x, std::string(" , "), tempCoords_y);
    guiManager.addStats(std::string("Entities: "), entityManager.getEntityCount());
    guiManager.addStats(std::string("Hour  : "), (int) timeManager.getHour());
    guiManager.addStats(std::string("Minute: "), (int) timeManager.getMinute());
    guiManager.addStats(std::string("Time: "), (float) timeManager.getDecimalTime());


    guiManager.setStats(entityManager.getPlayerStats());

    if(pause)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(guiManager.testButton(101))
            {
                StateManager::getInstance().changeState(new State_Transition(window, 1));
            }
            else if(guiManager.testButton(102))
            {
                window.close();
            }
        }
    }
}

void State_Game::displayTextures()
{
    window.setView(gameView);
    tileEngine.drawMap(player_MapCoordinates);
    lightManager.drawLighting_1();
    entityManager.drawEntity();
    lightManager.drawLighting_2();

    window.setView(overlayView);
    guiManager.buttonCheck();
    commandsManager.drawCommandArea();
    guiManager.drawGui();

    window.draw(alignment);
}


