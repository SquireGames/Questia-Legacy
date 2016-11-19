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

#include "Utl/Threads/ThreadPool_Fixed.h"

#include "DrawLayer.h"

#include "KeyAction.h"

//temp
#include "Entity_Player.h"

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
    GuiManager guiManager;
    GuiLoader guiLoader;

    TileEngine tileEngine;
    EntityManager entityManager;

    bool paused = false;
    bool showColl = true;

    ThreadPool_Fixed threadPool;

    //tasks
    void gameLogic();
    void task_lighting();
    void task_ai();
    void task_particles();
    void task_gui();

    //keys
    ctr::Input ctr_moveUp;
    ctr::Input ctr_moveDown;
    ctr::Input ctr_moveLeft;
    ctr::Input ctr_moveRight;
    ctr::Input ctr_skill_1;
    ctr::Input ctr_skill_2;
    ctr::Input ctr_skill_3;
    ctr::Input ctr_skill_4;
    ctr::Input ctr_skill_5;
    ctr::Input ctr_skill_6;

    //TEMP
    sf::Sprite alignment;
    sf::Sprite alignment2;
    sf::VertexArray visibleScreen;

};

#endif // STATE_GAME_H
