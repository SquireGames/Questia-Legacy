#ifndef STATE_TILEMAPEDITOR_H
#define STATE_TILEMAPEDITOR_H

#include <SFML/Graphics.hpp>

#include "StateManager/State.h"

#include "Data_Desktop.h"
#include "TileEngine_Editor.h"
#include "ResourceManager.h"
#include "GuiManager.h"



class State_TileMapEditor : public State
{
public:
    State_TileMapEditor(sf::RenderWindow &mWindow);
    ~State_TileMapEditor();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;

    TileEngine_Editor tileEngineEditor;
    ResourceManager resourceManager;
    GuiManager guiManager;

    sf::View mapView;
    sf::View overlayView;

    sf::Vector2f velocity;
    sf::Vector2f coordinates;

    float scrollMultiplier;

    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;

    int selectionSize;
    int selectedLayer;

    sf::Vector2f player_MapCoordinates;
};

#endif // STATE_TILEMAPEDITOR_H
