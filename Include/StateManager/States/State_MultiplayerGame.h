#ifndef STATE_MULTIPLAYERGAME_H
#define STATE_MULTIPLAYERGAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "StateManager/State.h"

#include "TimeManager/TimeManager.h"
#include "LightManager/LightManager.h"
#include "TileEngine/TileEngine.h"
#include "EntityManager/EntityManager.h"
#include "GuiManager/GuiManager.h"
#include "ResourceManager/ResourceManager.h"
#include "EntityManager/SpawnManager.h"
#include "CharacterManager/CharacterManager.h"
#include "ItemManager/ItemManager.h"
#include "Data/CommandsManager.h"
#include "MultiplayerManager/MultiplayerManager.h"

#include "Utl/SaveFile/SaveFile.h"
#include "Data/Data_Desktop.h"

class State_MultiplayerGame : public State
{
public:
    State_MultiplayerGame(sf::RenderWindow &mWindow);
    ~State_MultiplayerGame();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:

    bool pause;
    unsigned char tick;

    sf::Vector2f player_Velocity;
    sf::Vector2f player_Coordinates;
    sf::Vector2f player_MapCoordinates;

    sf::View gameView;
    sf::View overlayView;

    sf::RenderWindow& window;

    ResourceManager resourceManager;
    //TileEngine tileEngine;
    EntityManager entityManager;
    GuiManager guiManager;
    GuiManagerNew newGuiManager;
    SpawnManager spawnManager;
    CharacterManager characterManager;
    ItemManager itemManager;
    CommandsManager commandsManager;
    LightManager lightManager;
    MultiplayerManager multiplayerManager;
    TimeManager timeManager;

    int tempCoords_x, tempCoords_y;
    float playerAngle;

    ///Saves
    SaveFile save_location;
    SaveFile save_character;
    SaveFile save_entities;
    SaveFile save_spawn;

    ///Key binds

    enum keyEnum {mouse, keyboard, joystick};

    struct mappedKey
    {
        mappedKey(int key_):
            keyType()
            , keyNumber(key_)
            , activated(false) {}

        int keyType; // 0-keyBoard, 2-Mouse, 3-Joystick
        int keyNumber;
        sf::Keyboard::Key keyInput;
        sf::Mouse::Button mouseInput;
        bool activated;
    };

    mappedKey moveKey0;
    mappedKey moveKey1;
    mappedKey moveKey2;
    mappedKey moveKey3;

    mappedKey skillKey4;
    mappedKey skillKey5;
    mappedKey skillKey6;

    //UNIMPLENTED
    mappedKey toggleTalkKey;
    mappedKey talkKey;

    std::vector <struct mappedKey> keybindVector;


    //TEMP
    sf::Sprite alignment;

};

#endif // STATE_MULTIPLAYERGAME_H