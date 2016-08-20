#ifndef TILEENGINE_H
#define TILEENGINE_H

#include "Data_Desktop.h"
#include "ResourceManager.h"

#include "EntityManager/Entity/Collidable/Entity_Collidable.h"
#include <map>

#include <SFML/Graphics.hpp>

#include "Utl.h"
#include "SpriteSheet.h"

#include "SaveFile_TileEngine.h"

#include "Tile.h"

class TileEngineNew
{
public:
    //ctor and dtor
    TileEngineNew(sf::RenderWindow& _window, ResourceManager& _resourceManager);
    ~TileEngineNew();

    void loadMap(std::string _mapName);
    void drawMap();

    //set tiles drawn from player position
    void setPosition(int x, int y);

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
    const unsigned int tileFit_x = (1920.f / 64.f) + 2; // +2 for transitioning tiles
    const unsigned int tileFit_y = (1080.f / 64.f) + 2; // +2 for transitioning tiles

    ///data
    utl::Vector2i cameraPosition {utl::Vector2i(0,0)};
    SaveFile_TileEngine saveFile;
    std::string mapName = "nil";

    ///helpers
    //for map
    int getTile(unsigned int x, unsigned int y, unsigned int layer);
    int getChunk(unsigned int x, unsigned int y, unsigned int layer);

    ///default
    sf::RenderWindow &window;
    ResourceManager& resourceManager;

    ///chunk renderer
    //TODO make sure to resize for cache precision
    //chunk size is 8x8 tiles
    std::vector <sf::VertexArray> chunkVector;
    //chunks
    unsigned int chunks_x = 0, chunks_y = 0;
    //texture
    sf::Texture* textureAtlas = nullptr;
};



















class TileEngine
{
public:
    TileEngine(sf::RenderWindow &_window, ResourceManager& _resourceManager);
    ~TileEngine();
    sf::RenderWindow &window;

    void drawMap(sf::Vector2f coordinates);
    int getMapCollision(sf::Vector2i mapCoordinates,sf::Vector2f playerCoordinates, sf::Vector2f getSideRadius, sf::Vector2f velocity, int (&returnCollision)[4]);
    void loadTiles(float x, float y, int index, int id);
    void loadTiles(float x, float y, int index, int id, int transparency);
    void loadMap(std::string mapName, bool isLimitingTextures);
    std::vector <sf::Vector2i> usedTileVector;

    std::map <int, std::map <int, sf::Sprite > > tileIndex;
    int mapHeight, mapWidth;

    //File locations
    std::string mapDir;
    std::string mapDir2;
    std::string mapTiles;

    // EDITOR ONLY
    void setMapVector (std::vector<std::vector <sf::Vector2i> > MapVector, int layer);
    std::vector<std::vector <sf::Vector2i> > getMapVector(int layer);

private:
    //local functions
    bool tileIsUsed(int index, int id, bool isLimitingTextures);
    void local_loadMap(std::string mapName, int layer, bool isLimitingTextures);
    void updateUsedTileList();

    std::map <int,std::vector <std::vector <sf::Vector2i> > > tileMap;

    ResourceManager& resourceManager;
};

#endif // TILEENGINE_H
