#include <iostream>
#include <sstream>
#include <math.h>
#include <tuple>
#include <string>

#include "StateManager/StateManager.h"
#include "StateManager/States/State_Game.h"
#include "StateManager/States/State_Transition.h"

#include "Utl/Utl.h"

///Global variables
extern bool isInDebugMode;// = false;

State_Game::State_Game(sf::RenderWindow &mWindow):
    window(mWindow)
    //managers
    , resourceManager()
    , timeManager(0,0)
    , lightManager(mWindow, timeManager, resourceManager)
    , tileEngine (mWindow, resourceManager)
    , guiManager(mWindow, resourceManager)
    , guiLoader()
    , entityManager (EntityManager::ManagerType::singleplayer, mWindow, resourceManager, lightManager)
    , spawnManager (true, entityManager)
    , characterManager(mWindow, entityManager, guiManager)
    , itemManager(mWindow, resourceManager)
    , commandsManager(mWindow, entityManager, timeManager)

    , tileEngineNew(window, resourceManager)

    //character info
    , player_Velocity(1,1)
    , player_MapCoordinates(0,0)
    , playerAngle(0)

    //saves
    , save_location()
    , save_character()
    , save_entities()
    , save_spawn()

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

    //perm
    , saveFile()
{
    ///gui
    //font
    guiManager.setFont(Data_Desktop::getInstance().font1);
    //loader
    guiLoader.setGuiPack(saveFile.getGuiPack());
    guiLoader.loadGui(guiManager, "game");



    //{savesso
    //location
    std::stringstream sStream;
    sStream << "Saves/Characters/" << Data_Desktop::getInstance().getCharacterSelection() << "/" << "location" << ".txt";
    save_location.setFilePath(sStream.str());
    sStream.str(std::string());

    sStream << "Saves/Characters/" << Data_Desktop::getInstance().getCharacterSelection() << "/" << "character" << ".txt";
    save_character.setFilePath(sStream.str());
    sStream.str(std::string());

    sStream << "Saves/Characters/" << Data_Desktop::getInstance().getCharacterSelection() << "/" << "entities" << ".txt";
    save_entities.setFilePath(sStream.str());
    sStream.str(std::string());

    sStream << "Saves/Characters/" << Data_Desktop::getInstance().getCharacterSelection() << "/" << "spawn" << ".txt";
    save_spawn.setFilePath(sStream.str());
    sStream.str(std::string());

    save_location.readFile();
    save_character.readFile();

    timeManager.setTime(utl::asInt(save_location.getItem("time")));

    std::vector <int> savedID;
    std::map <int, int> newID; //old ID, new ID

    if(save_entities.readFile())
    {
        std::vector<std::pair<std::string, std::string> > entityVector = save_entities.getSaveList();
        for(unsigned int it = 0; it != entityVector.size(); it++)
        {
            std::vector<std::string> entityInfo = utl::separateString(entityVector[it].second, ',');
            int entityID = entityManager.createEntity(entityVector[it].first, sf::Vector2f(utl::asFloat(entityInfo[1]),utl::asFloat(entityInfo[2])));
            entityManager.setCharacteristic(entityID,"hp", utl::asInt(entityInfo[3]));
            savedID.push_back(utl::asInt(entityInfo[0]));
            newID[utl::asInt(entityInfo[0])] = entityID;
        }
    }
    else
    {
        save_entities.clearSave();
    }
    //}

    ///views
    gameView.setSize(1920,1080);
    gameView.setCenter(960,540);
    gameView.zoom(1.f);

    overlayView.setSize(1920,1080);
    overlayView.setCenter(960,540);
    overlayView.zoom(1.f);

    ///character
    entityManager.createPlayer(Data_Desktop::getInstance().getCharacterSelection(),
                               sf::Vector2f(utl::asFloat(save_location.getItem("coords_x")),utl::asFloat(save_location.getItem("coords_y"))),
                               utl::asInt(save_character.getItem("hp")), utl::asInt(save_character.getItem("maxHp")),
                               utl::asInt(save_character.getItem("mp")), utl::asInt(save_character.getItem("maxMp")),
                               utl::asInt(save_character.getItem("st")), utl::asInt(save_character.getItem("maxSt")));

    ///light init
    lightManager.setLightOverlay_Coords(entityManager.getPlayerCoordinates());

    ///loading the map
    tileEngine.loadMap(Data_Desktop::getInstance().getMapSelection(), true);
    if(save_spawn.readFile())
    {
        spawnManager.loadSpawnFile(Data_Desktop::getInstance().getMapSelection(), save_spawn, savedID, newID);
    }
    else
    {
        save_spawn.clearSave();
        spawnManager.loadSpawnFile(Data_Desktop::getInstance().getMapSelection(), save_spawn, savedID, newID);
    }


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

    alignment.setTexture(resourceManager.getTexture("Media/Image/Gui/Game/Alignment.png"));
    alignment2.setTexture(resourceManager.getTexture("Media/Image/Gui/Game/Alignment.png"));

    alignment2.setOrigin(1920/2, 1080/2);

    itemManager.spawnItem("item:test", ItemUsage::ground, 64, 64);

    ///font
    guiManager.setFont(Data_Desktop::getInstance().font1);

    ///NEW TILE ENGINE
    tileEngineNew.loadMap("TEST");
}

State_Game::~State_Game()
{
    std::cout<<"DEBUG: State_Game Destroyed"<<std::endl;
}

void State_Game::processImput(sf::Keyboard::Key key,bool isPressed)
{
    if(pause)
    {
        if(key == sf::Keyboard::Escape && isPressed == false)
        {
            guiManager.setGroupAtr("pauseMenu", gui::ButtonCharacteristic::isVisible, false);
            pause = false;
        }
    }
    else
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
            //guiManager.toggleOverlay();
        }
        else if(key == sf::Keyboard::T)
        {
            isInDebugMode = true;
        }
        else if(key == sf::Keyboard::Y)
        {
            isInDebugMode = false;
        }

        else if(key == sf::Keyboard::Escape && isPressed == false)
        {
            guiManager.setGroupAtr("pauseMenu", gui::ButtonCharacteristic::isVisible, true);
            pause = true;
        }
    }

    if(key == sf::Keyboard::Escape)
    {
        save_location.saveItem("map", Data_Desktop::getInstance().getMapSelection());
        save_location.saveItem("coords_x", entityManager.getPlayerCoordinates().x);
        save_location.saveItem("coords_y", entityManager.getPlayerCoordinates().y);
        save_location.saveItem("time", timeManager.getTime());
        save_location.writeFile();

        int HP, MP, ST;
        int maxHP, maxMP, maxST;
        std::tie(HP,MP,ST,maxHP,maxMP,maxST) = entityManager.getPlayerStats();

        save_character.saveItem("hp", HP);
        save_character.saveItem("mp", MP);
        save_character.saveItem("st", ST);
        save_character.saveItem("maxHp", maxHP);
        save_character.saveItem("maxMp", maxMP);
        save_character.saveItem("maxSt", maxST);
        save_character.writeFile();

        save_entities.clearSave();
        entityManager.saveEntities(save_entities);
        save_spawn.clearSave();
        spawnManager.saveSpawns(save_spawn);
    }
}

void State_Game::update(sf::Time elapsedTime)
{
    ///update mouse
    guiManager.setMousePosition(std::make_pair(Data_Desktop::getInstance().getScaledMousePosition(window).x,Data_Desktop::getInstance().getScaledMousePosition(window).y));

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
        }

        //Angle
        float angle = atan2(Data_Desktop::getInstance().getScaledMousePosition(window).y - 540, Data_Desktop::getInstance().getScaledMousePosition(window).x - 960);
        angle = angle * 180 / 3.14159265;

        //Coordinates
        player_MapCoordinates.x = (int)entityManager.getPlayerCoordinates().x/64;
        player_MapCoordinates.y = (int)entityManager.getPlayerCoordinates().y/64;
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


    int HP, MP, ST;
    int maxHP, maxMP, maxST;
    int HPP, MPP, STP;
    std::tie(HP,MP,ST,maxHP,maxMP,maxST) = entityManager.getPlayerStats();
    HPP = (float)HP * 100/(float)maxHP;
    MPP = (float)MP * 100/(float)maxMP;
    STP = (float)ST * 100/(float)maxST;

    ///gui
    //game
    guiManager.setButtonAtr("hpBar", "percent", gui::ButtonAtrCharacteristic::percentage, HPP);
    guiManager.setButtonAtr("mpBar", "percent", gui::ButtonAtrCharacteristic::percentage, MPP);
    guiManager.setButtonAtr("stBar", "percent", gui::ButtonAtrCharacteristic::percentage, STP);
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
    //tileEngine.drawMap(player_MapCoordinates);
    tileEngineNew.drawMap();

    lightManager.drawLighting_1();
    itemManager.drawItems();
    entityManager.drawEntity();
    lightManager.drawLighting_2();
    window.draw(alignment2);

    window.setView(overlayView);
    commandsManager.drawCommandArea();

    guiManager.drawButtons();
    window.draw(alignment);
}


