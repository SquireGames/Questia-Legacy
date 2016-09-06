#ifndef STATE_TILEMAPEDITOR_H
#define STATE_TILEMAPEDITOR_H

#include <SFML/Graphics.hpp>

#include "Data_Desktop.h"

#include "StateManager/State.h"

#include "Data_Desktop.h"
#include "TileEngine_Editor.h"

#include "ResourceManager.h"

#include "GuiManager.h"
#include "GuiLoader.h"

#include "SaveFile_Options.h"

class State_TileMapEditor : public State
{
public:
    State_TileMapEditor(sf::RenderWindow &window);
    ~State_TileMapEditor();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;

    ResourceManager resourceManager;
    TileEngine_Editor tileEngineEditor;

    GuiManagerNew guiManager;
    GuiLoader guiLoader;

    SaveFile_Options saveFile_options;

    sf::View mapView;
    sf::View overlayView;

    utl::Vector2f cameraPosition = utl::Vector2f(0,0);

    bool is_key_up    = false;
    bool is_key_down  = false;
    bool is_key_left  = false;
    bool is_key_right = false;
};

#endif // STATE_TILEMAPEDITOR_H
