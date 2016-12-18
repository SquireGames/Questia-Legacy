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

    sf::View mapView;
    sf::View overlayView;

    utl::Vector2f cameraPosition = utl::Vector2f(0,0);
    int moveSpeed = 5;
    float moveSpeedModifier = 1;

    bool is_key_up    = false;
    bool is_key_down  = false;
    bool is_key_left  = false;
    bool is_key_right = false;

    utl::Executor executor;

    //overlay toggles
    utl::Ticker ticker_overlayToggle = utl::Ticker(20);
    utl::Toggler toggler_overlay = utl::Toggler(true);



    void setOverlayStatus(bool isVisible)
    {
        if(isVisible)
        {
            guiManager.setButtonAtr("overlayToggle", "buttonSprite", gui::ButtonAtrCharacteristic::flip, 'n');

            executor.addTask("overlayOpen", utl::Executor::TaskType::Continuous, utl::Ticker(40), [&](float taskPercentage)
            {
                guiManager.setButtonAtr("overlay_up",   "sprite", gui::ButtonAtrCharacteristic::percentage, static_cast<int>(100.f * taskPercentage));
                guiManager.setButtonAtr("overlay_down", "sprite", gui::ButtonAtrCharacteristic::percentage, static_cast<int>(100.f * taskPercentage));
            });
        }
        else
        {
            guiManager.setButtonAtr("overlayToggle", "buttonSprite", gui::ButtonAtrCharacteristic::flip, 'y');

            executor.addTask("overlayClose", utl::Executor::TaskType::Continuous, utl::Ticker(40), [&](float taskPercentage)
            {
                guiManager.setButtonAtr("overlay_up",   "sprite", gui::ButtonAtrCharacteristic::percentage, 100 - static_cast<int>(100.f * taskPercentage));
                guiManager.setButtonAtr("overlay_down", "sprite", gui::ButtonAtrCharacteristic::percentage, 100 - static_cast<int>(100.f * taskPercentage));
            });
        }
    }
};

#endif // STATE_TILEMAPEDITOR_H
