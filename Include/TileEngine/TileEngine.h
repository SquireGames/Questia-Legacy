#ifndef TILEENGINE_H
#define TILEENGINE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <utility>
#include <map>

#include "Data_Desktop.h"
#include "ResourceManager.h"

#include "Utl.h"
#include "SpriteSheet.h"

#include "SaveFile_TileEngine.h"

#include "Tile.h"

class TileEngine
{
public:
    //ctor and dtor
    TileEngine(sf::RenderWindow& _window, ResourceManager& _resourceManager);
    ~TileEngine();

    void loadMap(std::string _mapName);

    //draws chunks
    void drawMap();
    //draws separate tiles
    void drawTiles();

    void setViewportSize(float width, float height);

    //set tiles drawn from player position
    void setPosition(int x, int y);

    //collision detection
    //utl::Direction

protected:
    ///map
    //stores tiles
    std::map <std::pair <int, int>, Tile> tileStorage;

    //stores map
    std::vector <utl::Vector2ui> tileMap;
    //stores map dimensions
    unsigned int mapWidth = 0, mapHeight = 0, mapLayers = 0;
    //largest tile in map for tile culling
    unsigned int maxTileSize_x = 1, maxTileSize_y = 1;

    //tiles fit on screen
    unsigned int tileFit_x = (1920.f / 64.f) + 2; // +2 for transitioning tiles
    unsigned int tileFit_y = (1080.f / 64.f) + 2; // +2 for transitioning tiles

    ///data
    utl::Vector2i cameraPosition {utl::Vector2i(0,0)};
    SaveFile_TileEngine saveFile;
    std::string mapName = "nil";

    ///helpers
    //for map
    int getTile(unsigned int x, unsigned int y, unsigned int layer);
    int getChunk(unsigned int x, unsigned int y);

    ///default
    sf::RenderWindow &window;
    ResourceManager& resourceManager;

    ///chunk renderer
    //chunk size is 8x8 tiles
    std::vector <sf::VertexArray> chunkVector;
    //chunks
    unsigned int chunks_x = 0, chunks_y = 0;
    //texture
    sf::Texture* textureAtlas = nullptr;
};

#endif // TILEENGINE_H
