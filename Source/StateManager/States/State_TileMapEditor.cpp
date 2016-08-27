#include "State_TileMapEditor.h"

State_TileMapEditor::State_TileMapEditor(sf::RenderWindow &mWindow):
    window(mWindow)
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

    //verify view
    mapView.setSize(1920,1080);
    mapView.setCenter(960,540);
    //mapView.zoom(2);
    window.setView(mapView);

    //load map
    //tileEngineEditor.createMap("TEST",500,500,4);
    tileEngineEditor.loadMap("TEST");
    tileEngineEditor.setPosition(960,540);
}

State_TileMapEditor::~State_TileMapEditor()
{
    //dtor
}

void State_TileMapEditor::processImput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::Escape && isPressed == true)
    {
        window.close();
    }
}

void State_TileMapEditor::update(sf::Time)
{
    guiManager.setMousePosition(std::make_pair(Data_Desktop::getInstance().getScaledMousePosition(window).x,Data_Desktop::getInstance().getScaledMousePosition(window).y));

    //debug
    guiManager.setButtonAtr("fpsText", "text", gui::ButtonAtrCharacteristic::text, utl::asString(Data_Desktop::getInstance().get_FPS()));
}

void State_TileMapEditor::displayTextures()
{
    guiManager.drawButtons();
    tileEngineEditor.drawTiles();
}

