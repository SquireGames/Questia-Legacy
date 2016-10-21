#ifndef STATE_GAME_H
#define STATE_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "StateManager/StateManager.h"
#include "StateManager/State.h"
#include "StateManager/States/State_Transition.h"

#include "TileEngine/TileEngine.h"
#include "EntityManager/EntityManager.h"
#include "GuiManager/GuiManager.h"
#include "ResourceManager/ResourceManager.h"
#include "MultiplayerManager/MultiplayerManager.h"

#include "GuiLoader.h"

#include "Utl/SaveFile/SaveFile.h"
#include "SaveFile_Options.h"
#include "Data/Data_Desktop.h"

class State_Game : public State
{
public:
    State_Game(sf::RenderWindow &window);
    ~State_Game();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    SaveFile_Options saveFile;

    sf::View gameView;
    sf::View overlayView;

    sf::RenderWindow& window;

    ResourceManager resourceManager;
    GuiManagerNew guiManager;
    GuiLoader guiLoader;

    EntityManager entityManager;
    TileEngineNew tileEngineNew;

    float playerAngle;
    bool paused = false;


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
    sf::Sprite alignment2;
    sf::VertexArray visibleScreen;
};

#endif // STATE_GAME_H
