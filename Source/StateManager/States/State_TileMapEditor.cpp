#include "State_TileMapEditor.h"
#include "StateManager/States/State_Transition.h"
#include "StateManager/StateManager.h"
#include "ResourceManager.h"
#include "TileEngine/TileEngine_Editor.h"

#include <iostream>

State_TileMapEditor::State_TileMapEditor(sf::RenderWindow &mWindow):
    window(mWindow)
    , resourceManager()
    , tileEngineEditor(mWindow, Data_Desktop::getInstance().getMapSelection())
    , guiManager(mWindow, resourceManager, false)

    , mIsMovingUp(false)
    , mIsMovingDown(false)
    , mIsMovingLeft(false)
    , mIsMovingRight(false)

    , velocity(32,32)
    , coordinates(960,540)
    , coordinates_t(960,540)

    , selectionSize(1)
    , scrollMultiplier(1)
    , selectedLayer(3)
{
    mapView.setSize(1920,1080);
    mapView.setCenter(960,540);
    mapView.zoom(1);

    overlayView.setSize(1920,1080);
    overlayView.setCenter(960,540);
}

State_TileMapEditor::~State_TileMapEditor()
{
    //dtor
}

void State_TileMapEditor::processImput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::M)
    {
        StateManager::getInstance().changeState(new State_Transition(window, 1));
    }
    else if(key == sf::Keyboard::W || key == sf::Keyboard::Up)
    {
        mIsMovingUp = isPressed;
    }
    else if(key == sf::Keyboard::S || key == sf::Keyboard::Down)
    {
        mIsMovingDown = isPressed;
    }
    else if(key == sf::Keyboard::A || key == sf::Keyboard::Left)
    {
        mIsMovingLeft = isPressed;
    }
    else if(key == sf::Keyboard::D || key == sf::Keyboard::Right)
    {
        mIsMovingRight = isPressed;
    }
    else if(key == sf::Keyboard::T )
    {
        tIsMovingUp = isPressed;
    }
    else if(key == sf::Keyboard::G)
    {
        tIsMovingDown = isPressed;
    }
    else if(key == sf::Keyboard::F)
    {
        tIsMovingLeft = isPressed;
    }
    else if(key == sf::Keyboard::H )
    {
        tIsMovingRight = isPressed;
    }
    else if(key == sf::Keyboard::R)
    {
        tileEngineEditor.saveCurrentMap();
    }

    else if (key == sf::Keyboard::Num1)
    {
        selectedLayer = 0;
    }
    else if(key == sf::Keyboard::Num2)
    {
        selectedLayer = 1;
    }
    else if(key == sf::Keyboard::Num3)
    {
        selectedLayer = 3;
    }
    else if(key == sf::Keyboard::Dash)
    {
        selectionSize = 1;
    }
    else if(key == sf::Keyboard::Equal)
    {
        selectionSize = 3;
    }
}

void State_TileMapEditor::update(sf::Time)
{
    if(mapView.getSize().x < 1920)
    {
        mapView.setSize(1920, 1080);
        scrollMultiplier = 1;
    }

    if(mIsMovingUp)
    {
        coordinates.y = coordinates.y - (velocity.y);
    }
    if(mIsMovingDown)
    {
        coordinates.y = coordinates.y + (velocity.y);
    }
    if(mIsMovingLeft)
    {
        coordinates.x = coordinates.x - (velocity.x);
    }
    if(mIsMovingRight)
    {
        coordinates.x = coordinates.x + (velocity.x);
    }

    if(tIsMovingUp)
    {
        coordinates_t.y = coordinates_t.y - (velocity.y);
    }
    if(tIsMovingDown)
    {
        coordinates_t.y = coordinates_t.y + (velocity.y);
    }
    if(tIsMovingLeft)
    {
        coordinates_t.x = coordinates_t.x - (velocity.x);
    }
    if(tIsMovingRight)
    {
        coordinates_t.x = coordinates_t.x + (velocity.x);
    }

    switch (Data_Desktop::getInstance().getMouseWheelDelta())
    {
    case 0:
        break;
    case -1:
        scrollMultiplier = scrollMultiplier + 0.1;
        mapView.zoom(1.1);
        break;
    case 1:
        scrollMultiplier = scrollMultiplier - 0.1;
        mapView.zoom(0.9);
        break;
    }

    mapView.setCenter(coordinates.x,coordinates.y);

    player_MapCoordinates.x = coordinates.x/32 + 1;
    player_MapCoordinates.y = coordinates.y/32 + 1;

    guiManager.addStats(std::string("FPS: "), Data_Desktop::getInstance().get_FPS());
    //guiManager.addStats(std::string("Coordinates: "),Data_Desktop::getInstance().getScaledMousePosition(window).x + coordinates.x - 960, " , ",Data_Desktop::getInstance().getScaledMousePosition(window).y + coordinates.y - 540);
    guiManager.addStats(std::string("Tile: "),(int)((Data_Desktop::getInstance().getScaledMousePosition(window).x + coordinates.x - 960)/32), " , ",(int)((Data_Desktop::getInstance().getScaledMousePosition(window).y + coordinates.y - 540)/32));
    guiManager.addStats(std::string("Layer: "), selectedLayer);
    guiManager.addStats(std::string("Width, Height: "), tileEngineEditor.tileEngine.mapWidth, " , ", tileEngineEditor.tileEngine.mapHeight);
}

void State_TileMapEditor::displayTextures()
{
    window.setView(mapView);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        mapView.setCenter(coordinates_t.x, coordinates_t.y);
        window.setView(mapView);
        tileEngineEditor.returnIDList(window);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            tileEngineEditor.tileSelection(Data_Desktop::getInstance().getScaledMousePosition(window), coordinates_t);
        }

        tileEngineEditor.tile_hover(Data_Desktop::getInstance().getScaledMousePosition(window),  selectionSize, coordinates_t);
    }
    else
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(selectedLayer != 3)
            {
                tileEngineEditor.replaceTile(Data_Desktop::getInstance().getScaledMousePosition(window), selectionSize, coordinates, selectedLayer);
            }
            tileEngineEditor.reLoadMap();
        }
        switch (selectedLayer)
        {
        case 0:
        {
            tileEngineEditor.drawTileMap(window, player_MapCoordinates, scrollMultiplier, 0, true);
            tileEngineEditor.drawTileMap(window, player_MapCoordinates, scrollMultiplier, 1, 100);
            tileEngineEditor.tile_hover(Data_Desktop::getInstance().getScaledMousePosition(window) , selectionSize, coordinates);
        }
        break;
        case 1:
        {
            tileEngineEditor.drawTileMap(window, player_MapCoordinates, scrollMultiplier, 0, true);

            window.setView(overlayView);
            sf::RectangleShape screenCover;
            screenCover.setSize(sf::Vector2f(1920, 1080));
            screenCover.setPosition(0,0);
            screenCover.setFillColor(sf::Color(200,200,200,111));
            window.draw(screenCover);
            window.setView(mapView);

            tileEngineEditor.drawTileMap(window, player_MapCoordinates, scrollMultiplier, 1, true);
            tileEngineEditor.tile_hover(Data_Desktop::getInstance().getScaledMousePosition(window), selectionSize, coordinates);
        }
        break;
        case 3:
        {
            tileEngineEditor.drawTileMap(window, player_MapCoordinates, scrollMultiplier, 0, false);
            tileEngineEditor.drawTileMap(window, player_MapCoordinates, scrollMultiplier, 1, false);
        }
        break;
        default:
        {
            tileEngineEditor.tile_hover(Data_Desktop::getInstance().getScaledMousePosition(window),  selectionSize, coordinates);
        }
        break;
        }
    }
    window.setView(overlayView);
    guiManager.buttonCheck();
    guiManager.drawGui();
}

