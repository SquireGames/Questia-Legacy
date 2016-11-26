#include "State_TileMapEditor.h"

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

    //gui view
    overlayView.setSize(1920,1080);
    overlayView.setCenter(1920/2,1080/2);

    //load map
    tileEngineEditor.createMap("test1",3,3,1);
    tileEngineEditor.loadMap("test1");
    tileEngineEditor.setPosition(0,0);
}

State_TileMapEditor::~State_TileMapEditor()
{
    //dtor
}

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
    //gui
    guiManager.setMousePosition(std::make_pair(Data_Desktop::getInstance().getScaledMousePosition(window).x,Data_Desktop::getInstance().getScaledMousePosition(window).y));

    //movement
    int moveSpeed = 3;
    if(is_key_up)
    {
        cameraPosition.y -= moveSpeed;
        mapView.setCenter(cameraPosition.x, cameraPosition.y);
        tileEngineEditor.setPosition(cameraPosition.x, cameraPosition.y);
    }
    if(is_key_down)
    {
        cameraPosition.y += moveSpeed;
        mapView.setCenter(cameraPosition.x, cameraPosition.y);
        tileEngineEditor.setPosition(cameraPosition.x, cameraPosition.y);
    }
    if(is_key_left)
    {
        cameraPosition.x -= moveSpeed;
        mapView.setCenter(cameraPosition.x, cameraPosition.y);
        tileEngineEditor.setPosition(cameraPosition.x, cameraPosition.y);
    }
    if(is_key_right)
    {
        cameraPosition.x += moveSpeed;
        mapView.setCenter(cameraPosition.x, cameraPosition.y);
        tileEngineEditor.setPosition(cameraPosition.x, cameraPosition.y);
    }

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

    //debug
    guiManager.setButtonAtr("fpsText", "text", gui::ButtonAtrCharacteristic::text, utl::asString(Data_Desktop::getInstance().get_FPS()));
}

void State_TileMapEditor::displayTextures()
{
    //tile map
    window.setView(mapView);
    tileEngineEditor.drawMap();

    //gui
    window.setView(overlayView);
    guiManager.drawButtons();
}
