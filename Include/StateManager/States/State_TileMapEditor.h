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

#include "Utl/Ticker.h"
#include "Utl/Toggler.h"
#include "Utl/Executor.h"

class State_TileMapEditor : public State
{
public:
    State_TileMapEditor(sf::RenderWindow &window);
    ~State_TileMapEditor();

    void processImput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;

    ResourceManager resourceManager;
    TileEngine_Editor tileEngineEditor;

    GuiManager guiManager;
    GuiLoader guiLoader;

    SaveFile_Options saveFile_options;

    sf::View overlayView;

    int moveSpeed = 5;
    float moveSpeedModifier = 1;

    bool is_key_up    = false;
    bool is_key_down  = false;
    bool is_key_left  = false;
    bool is_key_right = false;

    //handles animations
    utl::Executor executor;

    //handles different modes
    enum class EditorState {View, Idle, Tile} editorState = EditorState::Idle;

    //handles actions in various states
    void updateState_view();
    void updateState_idle();
    void updateState_tile();

    //handles movement in map view state
    void moveCamera_map();
    sf::View mapView;
    utl::Vector2f cameraPosition_map = utl::Vector2f(0,0);

    //handles movement in tile view state
    void moveCamera_tiles();
    sf::View tileView;
    utl::Vector2f cameraPosition_tile = utl::Vector2f(0,0);

    //toggles
    utl::Ticker ticker_overlayToggle = utl::Ticker(20);
    utl::Toggler overlayToggler = utl::Toggler(true);

    //gui
    void setOverlayStatus(bool isVisible);
};

#endif // STATE_TILEMAPEDITOR_H
