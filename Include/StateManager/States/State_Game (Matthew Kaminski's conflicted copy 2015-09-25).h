#ifndef STATE_GAME_H
#define STATE_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <sstream>

#include "StateManager/State.h"

#include "TileEngine/TileEngine.h"
#include "EntityManager/EntityManager.h"
#include "MultiplayerManager/MultiplayerManager.h"
#include "GuiManager/GuiManager.h"
#include "ResourceManager.h"
#include "EntityManager/SpawnManager.h"
#include "CharacterManager/CharacterManager.h"
#include "ItemManager/ItemManager.h"

#include "Data_Desktop.h"

class State_Game : public State
{
public:
    State_Game(sf::RenderWindow &mWindow);
    ~State_Game();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    bool pause;

    sf::Vector2f player_Velocity;
    sf::Vector2f player_Coordinates;
    sf::Vector2f player_MapCoordinates;

    sf::View gameView;
    sf::View overlayView;

    sf::RenderWindow& window;

    ResourceManager resourceManager;
    TileEngine tileEngine;
    EntityManager entityManager;
    MultiplayerManager multiplayerManager;
    GuiManager guiManager;
    SpawnManager spawnManager;
    CharacterManager characterManager;
    ItemManager itemManager;


    int tempCoords_x, tempCoords_y;
    float playerAngle;

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

    std::vector <struct mappedKey> keybindVector;


    sf::Keyboard::Key testImput(int key)
    {

    }

};

#endif // STATE_GAME_H
