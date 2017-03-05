#ifndef STATE_MULTIPLAYERGAME_H
#define STATE_MULTIPLAYERGAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "Questia/StateManager/State.h"
#include "Questia/StateManager/States/State_Transition.h"
#include "Questia/StateManager/StateManager.h"

#include "Questia/TileEngine/TileEngine.h"
#include "Questia/EntityManager/EntityManager.h"
#include "Questia/GuiManager/GuiManager.h"
#include "Questia/ResourceManager/ResourceManager.h"
#include "Questia/MultiplayerManager/MultiplayerManager.h"

#include "Questia/Utl/SaveFile/SaveFile.h"
#include "Questia/Data/Data_Desktop.h"

class State_MultiplayerGame : public State
{
public:
    State_MultiplayerGame(sf::RenderWindow &window);
    ~State_MultiplayerGame();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:

    bool pause;

    sf::View gameView;
    sf::View overlayView;

    sf::RenderWindow& window;

    ResourceManager resourceManager;
    EntityManager entityManager;
    GuiManager newGuiManager;
    MultiplayerManager multiplayerManager;

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

    //UNIMPLENTED
    mappedKey toggleTalkKey;
    mappedKey talkKey;

    std::vector <struct mappedKey> keybindVector;


    //TEMP
    sf::Sprite alignment;

};

#endif // STATE_MULTIPLAYERGAME_H
