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
    State_TileMapEditor(sf::RenderWindow &mWindow);
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
};

#endif // STATE_TILEMAPEDITOR_H
