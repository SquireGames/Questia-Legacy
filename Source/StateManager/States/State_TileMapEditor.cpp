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
    tileEngineEditor.createMap("test3", 250, 250, 3);
    tileEngineEditor.loadMap("test3");
    tileEngineEditor.setPosition(0,0);

    //map data
    guiManager.setButtonAtr("mapDataText", "width", gui::ButtonAtrCharacteristic::text, utl::asString(tileEngineEditor.getMapWidth()));
    guiManager.setButtonAtr("mapDataText", "height", gui::ButtonAtrCharacteristic::text, utl::asString(tileEngineEditor.getMapHeight()));
    guiManager.setButtonAtr("mapDataText", "layers", gui::ButtonAtrCharacteristic::text, utl::asString(tileEngineEditor.getMapLayers()));

    //layers
    for(unsigned int it = 0; it != tileEngineEditor.getMapLayers(); it++)
    {
        std::string groupName    = guiManager.createListEntry("layers");
        std::string bottomButton = guiManager.getGroupEntry(groupName, "layerButtonTemplate");
        std::string topButton    = guiManager.getGroupEntry(groupName, "layerSelectionTemplate");

        guiManager.setButtonAtr(bottomButton, "buttonText", gui::ButtonAtrCharacteristic::text, " " + utl::asString(it));

        layerData.push_back(LayerData(bottomButton, topButton));
    }
    //'select' layer 0
    LayerData& changeLayer = layerData.at(0);
    guiManager.setButtonAtr(changeLayer.topButton, "buttonSprite", gui::ButtonAtrCharacteristic::color, sf::Color(0,255,0,38));
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
        tileEngineEditor.overrideMap();

        //window.close();
        StateManager::getInstance().changeState(new State_Transition(window, GameState::State_MainMenu));
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
    //layers
    else if(isPressed)
    {
        if(key == sf::Keyboard::Tilde)
        {
            setLayerSelection(0);
        }
        for(unsigned int keyIt = sf::Keyboard::Num0; keyIt < (sf::Keyboard::Num0 + tileEngineEditor.getMapLayers()); keyIt++)
        {
            if(key == keyIt)
            {
                setLayerSelection(keyIt - sf::Keyboard::Num0);
                break;
            }
        }
    }
}
void State_TileMapEditor::update(sf::Time)
{
    executor.processTasks();

    //gui
    guiManager.setMousePosition(std::make_pair(Data_Desktop::getInstance().getScaledMousePosition(window).x,Data_Desktop::getInstance().getScaledMousePosition(window).y));

    //tickers
    ticker_overlayToggle.tick();
    for(LayerData& layer : layerData)
    {
        layer.ticker.tick();
    }

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
    {
        window.setView(mapView);

        //draw map
        for(unsigned int it = 0; it != layerData.size(); it++)
        {
            tileEngineEditor.drawLayer(it, layerData.at(it).alpha);
        }
        tileEngineEditor.resetTileAlpha();

        //draw grid
        tileEngineEditor.drawGridLines();

        //get tile hover position
        utl::Vector2f mousePos = Data_Desktop::getInstance().getScaledMousePosition(window);
        mousePos = (mousePos * mapZoomRatio) - (utl::Vector2f(1920/2, 1080/2) * mapZoomRatio) + utl::Vector2f(mapView.getCenter());
        mousePos = mousePos / 64.f;
        selectedTile = utl::Vector2i(mousePos.x, mousePos.y);

        //show selected tile
        guiManager.setButtonAtr("selectedTile", "text", gui::ButtonAtrCharacteristic::text, "Selected: (" + utl::asString(selectedTile.x) + ", " + utl::asString(selectedTile.y) + ")");

        if(!(selectedTile.x < 0) && !(selectedTile.y < 0) && !(selectedTile.x > tileEngineEditor.getMapWidth() - 1) && !(selectedTile.y > tileEngineEditor.getMapHeight() - 1))
        {
            tileEngineEditor.hoverTile(selectedTile.x, selectedTile.y);
        }

        //debug
        guiManager.setButtonAtr("fpsText", "fps", gui::ButtonAtrCharacteristic::text, utl::asString(Data_Desktop::getInstance().get_FPS()));
    }
    break;
    case EditorState::View:
    {
        window.setView(mapView);
        tileEngineEditor.drawMap();
    }
    break;
    case EditorState::Tile:
    {
        window.setView(tileView);

        //draw tiles
        tileEngineEditor.drawTiles();

        //get tile hover position
        utl::Vector2f mousePos = Data_Desktop::getInstance().getScaledMousePosition(window);
        mousePos = (mousePos * tileZoomRatio) - (utl::Vector2f(1920/2, 1080/2) * tileZoomRatio) + utl::Vector2f(tileView.getCenter());
        mousePos = mousePos / 64.f;
        selectedTile = utl::Vector2i(mousePos.x, mousePos.y);
        if(selectedTile.x >= 0 && selectedTile.y >= 0)
        {
            tileEngineEditor.hoverTile(selectedTile.x, selectedTile.y);
        }

        //show selected tile
        if(currentTile == nullptr)
        {
            guiManager.setButtonAtr("selectedTile", "text", gui::ButtonAtrCharacteristic::text, std::string("Selected: \"") + "NONE" + "\"");
        }
        else
        {
            guiManager.setButtonAtr("selectedTile", "text", gui::ButtonAtrCharacteristic::text, std::string("Selected: \"") + currentTile->source + "\"");
            sf::Sprite tempSprite = sf::Sprite(resourceManager.getTexture(currentTile->source));
        }

        //debug
        guiManager.setButtonAtr("fpsText", "fps", gui::ButtonAtrCharacteristic::text, utl::asString(Data_Desktop::getInstance().get_FPS()));
    }
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
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        //gui elements
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
                guiManager.setListAtr("layers", gui::ButtonCharacteristic::isVisible, false);
            }
        }
        for(unsigned int layerIt = 0; layerIt != layerData.size(); layerIt++)
        {
            LayerData& layer = layerData.at(layerIt);

            if(guiManager.isClicked(layer.bottomButton))
            {
                setLayerSelection(layerIt);
                break;
            }
        }

        //tile change
        if(currentTileID != -7 && Data_Desktop::getInstance().getScaledMousePosition(window).y > 30 && Data_Desktop::getInstance().getScaledMousePosition(window).y < (1080-30))
        {
            tileEngineEditor.replaceTile(currentTileID, selectedTile.x, selectedTile.y, selectedLayer);
        }
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        for(unsigned int layerIt = 0; layerIt != layerData.size(); layerIt++)
        {
            LayerData& layer = layerData.at(layerIt);

            if(guiManager.isClicked(layer.bottomButton))
            {
                advanceLayerState(layerIt);
                break;
            }
        }

        if(Data_Desktop::getInstance().getScaledMousePosition(window).y > 30 && Data_Desktop::getInstance().getScaledMousePosition(window).y < (1080-30))
        {
            tileEngineEditor.replaceTile(0, selectedTile.x, selectedTile.y, selectedLayer);
        }
    }

    //handle movement and zoom
    moveCamera_map();
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
                guiManager.setListAtr("layers", gui::ButtonCharacteristic::isVisible, true);
            }
        }

        //tiles
        if(tileEngineEditor.getTile_tileState(selectedTile.x, selectedTile.y) != nullptr)
        {
            if(!overlayToggler.getState() ||
                    (overlayToggler.getState() && Data_Desktop::getInstance().getScaledMousePosition(window).y > 30 && Data_Desktop::getInstance().getScaledMousePosition(window).y < (1080-30)))
            {
                currentTile = tileEngineEditor.getTile_tileState(selectedTile.x, selectedTile.y);
                currentTileID = tileEngineEditor.getTileID(currentTile->source);
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

    //get ratio
    mapZoomRatio = (mapView.getSize().x / 1920.f);

    //calculate movement speed
    moveSpeedModifier = std::max(mapZoomRatio, 0.5f);
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

    //get ratio
    tileZoomRatio = (tileView.getSize().x / 1920.f);

    //calculate movement speed
    moveSpeedModifier = std::max(tileZoomRatio, 0.5f);
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
                guiManager.setListAtr("layers", gui::ButtonCharacteristic::isVisible, true);
            }
        });
    }
    else
    {
        executor.tryDelete("overlayOpen");
        guiManager.setButtonAtr(buttonName, "buttonSprite", gui::ButtonAtrCharacteristic::flip, 'y');
        guiManager.setGroupAtr("overlayGroup", gui::ButtonCharacteristic::isVisible, false);
        guiManager.setListAtr("layers", gui::ButtonCharacteristic::isVisible, false);

        executor.addTask("overlayClose", utl::Executor::TaskType::Continuous, utl::Ticker(animationTicks), [&](float taskPercentage)
        {
            guiManager.setButtonAtr("overlay_up",   "sprite", gui::ButtonAtrCharacteristic::percentage, 100 - static_cast<int>(100.f * taskPercentage));
            guiManager.setButtonAtr("overlay_down", "sprite", gui::ButtonAtrCharacteristic::percentage, 100 - static_cast<int>(100.f * taskPercentage));
        });
    }
}

int State_TileMapEditor::advanceLayerState(unsigned int layer)
{
    LayerData& changeLayer = layerData.at(layer);

    if(changeLayer.ticker.isDone())
    {
        changeLayer.alpha = getNextLayerState(changeLayer.alpha);
        if(changeLayer.alpha == 35)
        {
            guiManager.setButtonAtr(changeLayer.topButton, "buttonSprite", gui::ButtonAtrCharacteristic::percentage, 50);
        }
        else
        {
            guiManager.setButtonAtr(changeLayer.topButton, "buttonSprite", gui::ButtonAtrCharacteristic::percentage, changeLayer.alpha);
        }
    }
}

int State_TileMapEditor::getNextLayerState(int alpha)
{
    if(alpha == 100)
    {
        return 35;
    }
    else if(alpha == 35)
    {
        return 0;
    }
    else
    {
        return 100;
    }
}

void State_TileMapEditor::resetLayerStates()
{
    for(LayerData& layer : layerData)
    {
        layer.alpha = 100;
        guiManager.setButtonAtr(layer.topButton, "buttonSprite", gui::ButtonAtrCharacteristic::percentage, 100);
    }
    for(unsigned int it = 0; it != layerData.size(); it++)
    {
        tileEngineEditor.drawLayer(it, 100);
    }
}

void State_TileMapEditor::setLayerSelection(unsigned int layer)
{
    if(selectedLayer != layer)
    {
        LayerData& previousLayer = layerData.at(selectedLayer);
        LayerData& changeLayer = layerData.at(layer);

        selectedLayer = layer;

        guiManager.setButtonAtr(previousLayer.topButton, "buttonSprite", gui::ButtonAtrCharacteristic::color, sf::Color(255,255,0,38));
        guiManager.setButtonAtr(changeLayer.topButton,   "buttonSprite", gui::ButtonAtrCharacteristic::color, sf::Color(0,255,0,38));
    }
}
