#include "State_TileMapEditor.h"

///ctor + dtor

State_TileMapEditor::State_TileMapEditor(sf::RenderWindow &window):
    window(window)
    , resourceManager()
    , tileEngineEditor(window, resourceManager)
    , guiManager(window, resourceManager)
    , saveFile_options()
{
    ///gui
    //font
    guiManager.setFont(Data_Desktop::getInstance().font1);
    //loader
    guiLoader.setGuiPack(saveFile_options.getGuiPack());
    guiLoader.loadGui(guiManager, "tileMapEditor");

    //map view
    mapView.setSize(1920,1080);
    mapView.setCenter(0,0);

    //tile view
    tileView.setSize(1920,1080);
    tileView.setCenter(0,0);

    //gui view
    overlayView.setSize(1920,1080);
    overlayView.setCenter(1920/2,1080/2);

    //load map
    tileEngineEditor.createMap("test1",3,3,1);
    tileEngineEditor.loadMap("test1");
    tileEngineEditor.setPosition(0,0);

    //map data
    guiManager.setButtonAtr("mapDataText", "width", gui::ButtonAtrCharacteristic::text, utl::asString(tileEngineEditor.getMapWidth()));
    guiManager.setButtonAtr("mapDataText", "height", gui::ButtonAtrCharacteristic::text, utl::asString(tileEngineEditor.getMapHeight()));
    guiManager.setButtonAtr("mapDataText", "layers", gui::ButtonAtrCharacteristic::text, utl::asString(tileEngineEditor.getMapLayers()));
}
State_TileMapEditor::~State_TileMapEditor()
{
    //dtor
}

///state functions

void State_TileMapEditor::processImput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::Escape && isPressed)
    {
        window.close();
    }
    else if(key == sf::Keyboard::W)
    {
        is_key_up = isPressed;
    }
    else if(key == sf::Keyboard::S)
    {
        is_key_down = isPressed;
    }
    else if(key == sf::Keyboard::A)
    {
        is_key_left = isPressed;
    }
    else if(key == sf::Keyboard::D)
    {
        is_key_right = isPressed;
    }
}
void State_TileMapEditor::update(sf::Time)
{
    executor.processTasks();

    //gui
    guiManager.setMousePosition(std::make_pair(Data_Desktop::getInstance().getScaledMousePosition(window).x,Data_Desktop::getInstance().getScaledMousePosition(window).y));

    //tickers
    ticker_overlayToggle.tick();

    //handling states
    switch(editorState)
    {
    case EditorState::Idle:
        updateState_idle();
        break;
    case EditorState::Tile:
        updateState_tile();
        break;
    case EditorState::View:
        updateState_view();
        break;
    default:
        editorState = EditorState::Idle;
        break;
    }
}
void State_TileMapEditor::displayTextures()
{
    //handling states
    switch(editorState)
    {
    case EditorState::Idle:
    case EditorState::View:
        window.setView(mapView);
        tileEngineEditor.drawMap();
        break;
    case EditorState::Tile:
        window.setView(tileView);
        tileEngineEditor.drawTiles();
        break;
    default:
        editorState = EditorState::Idle;
        break;
    }

    //gui
    window.setView(overlayView);
    guiManager.drawButtons();
}

///states

void State_TileMapEditor::updateState_view()
{
    //handle gui elements
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(guiManager.isClicked("overlayToggle"))
        {
            if(ticker_overlayToggle.isDone())
            {
                editorState = EditorState::Idle;
                setOverlayStatus(true);
            }
        }
    }

    //handle movement and zoom
    moveCamera_map();
}
void State_TileMapEditor::updateState_idle()
{
    //handle gui elements
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(guiManager.isClicked("overlayToggle"))
        {
            if(ticker_overlayToggle.isDone())
            {
                editorState = EditorState::View;
                setOverlayStatus(false);
            }
        }
        if(guiManager.isClicked("b_tileScreen"))
        {
            //TODO add another button ticker here
            if(ticker_overlayToggle.isDone())
            {
                editorState = EditorState::Tile;
                overlayToggler = utl::Toggler(true);
            }
        }
    }

    //handle movement and zoom
    moveCamera_map();

    //debug
    guiManager.setButtonAtr("fpsText", "fps", gui::ButtonAtrCharacteristic::text, utl::asString(Data_Desktop::getInstance().get_FPS()));
}
void State_TileMapEditor::updateState_tile()
{
    //handle gui elements
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(guiManager.isClicked("overlayToggle"))
        {
            if(ticker_overlayToggle.isDone())
            {
                setOverlayStatus(overlayToggler.toggle());
            }
        }
        if(guiManager.isClicked("b_mapScreen"))
        {
            //TODO add another button ticker here
            if(ticker_overlayToggle.isDone())
            {
                editorState = EditorState::Idle;
                overlayToggler = utl::Toggler(true);
            }
        }
    }
    moveCamera_tiles();
}

///camera

void State_TileMapEditor::moveCamera_map()
{
    //zoom
    const int mouseScroll = Data_Desktop::getInstance().getMouseWheelDelta();
    if(mouseScroll == 1)
    {
        mapView.zoom(0.95);
        tileEngineEditor.setViewportSize(mapView.getSize().x, mapView.getSize().y);
    }
    else if(mouseScroll == -1)
    {
        mapView.zoom(1.05);
        tileEngineEditor.setViewportSize(mapView.getSize().x, mapView.getSize().y);
    }

    //calculate movement speed
    moveSpeedModifier = std::max((mapView.getSize().x / 1920.f), 0.5f);
    float moveDistance = moveSpeed * moveSpeedModifier;

    //movement
    if(is_key_up)
    {
        cameraPosition_map.y -= moveDistance;
    }
    if(is_key_down)
    {
        cameraPosition_map.y += moveDistance;
    }
    if(is_key_left)
    {
        cameraPosition_map.x -= moveDistance;
    }
    if(is_key_right)
    {
        cameraPosition_map.x += moveDistance;
    }

    //updating position
    mapView.setCenter(cameraPosition_map.x, cameraPosition_map.y);
    tileEngineEditor.setPosition(cameraPosition_map.x, cameraPosition_map.y);
}
void State_TileMapEditor::moveCamera_tiles()
{
    //zoom
    const int mouseScroll = Data_Desktop::getInstance().getMouseWheelDelta();
    if(mouseScroll == 1)
    {
        tileView.zoom(0.95);
    }
    else if(mouseScroll == -1)
    {
        tileView.zoom(1.05);
    }

    //calculate movement speed
    moveSpeedModifier = std::max((tileView.getSize().x / 1920.f), 0.5f);
    float moveDistance = moveSpeed * moveSpeedModifier;

    //movement
    if(is_key_up)
    {
        cameraPosition_tile.y -= moveDistance;
    }
    if(is_key_down)
    {
        cameraPosition_tile.y += moveDistance;
    }
    if(is_key_left)
    {
        cameraPosition_tile.x -= moveDistance;
    }
    if(is_key_right)
    {
        cameraPosition_tile.x += moveDistance;
    }

    //updating position
    tileView.setCenter(cameraPosition_tile.x, cameraPosition_tile.y);
}

///helpers

///gui
void State_TileMapEditor::setOverlayStatus(bool isVisible)
{
    const std::string buttonName = "overlayToggle";
    const unsigned int animationTicks = 40;

    if(isVisible)
    {
        executor.tryDelete("overlayClose");
        guiManager.setButtonAtr(buttonName, "buttonSprite", gui::ButtonAtrCharacteristic::flip, 'n');

        executor.addTask("overlayOpen", utl::Executor::TaskType::Continuous, utl::Ticker(animationTicks), [&](float taskPercentage)
        {
            guiManager.setButtonAtr("overlay_up",   "sprite", gui::ButtonAtrCharacteristic::percentage, static_cast<int>(100.f * taskPercentage));
            guiManager.setButtonAtr("overlay_down", "sprite", gui::ButtonAtrCharacteristic::percentage, static_cast<int>(100.f * taskPercentage));

            if(taskPercentage == 1)
            {
                guiManager.setGroupAtr("overlayGroup", gui::ButtonCharacteristic::isVisible, true);
            }
        });
    }
    else
    {
        executor.tryDelete("overlayOpen");
        guiManager.setButtonAtr(buttonName, "buttonSprite", gui::ButtonAtrCharacteristic::flip, 'y');
        guiManager.setGroupAtr("overlayGroup", gui::ButtonCharacteristic::isVisible, false);

        executor.addTask("overlayClose", utl::Executor::TaskType::Continuous, utl::Ticker(animationTicks), [&](float taskPercentage)
        {
            guiManager.setButtonAtr("overlay_up",   "sprite", gui::ButtonAtrCharacteristic::percentage, 100 - static_cast<int>(100.f * taskPercentage));
            guiManager.setButtonAtr("overlay_down", "sprite", gui::ButtonAtrCharacteristic::percentage, 100 - static_cast<int>(100.f * taskPercentage));
        });
    }
}


