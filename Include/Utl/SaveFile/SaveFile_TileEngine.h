#ifndef SAVEFILE_TILEENGINE_H
#define SAVEFILE_TILEENGINE_H

#include <SFML/Window.hpp>

#include "Utl.h"
#include "SaveFile.h"
#include "FileData.h"

#include "Tile.h"

#include "TextureAtlas.h"

struct MapData
{
    //map
    std::vector <utl::Vector2ui> tileMap;
    //dimensions
    unsigned int width = 0, height = 0, layers = 0;
    //tile data
    std::map <std::pair <int, int>, Tile> tileStorage;
    //tile info
    unsigned int maxTileSize_x = 1, maxTileSize_y = 1;
};

class SaveFile_TileEngine
{
public:
    //ctor + dtor
    SaveFile_TileEngine(ResourceManager& _resourceManager);
    ~SaveFile_TileEngine();

    //shared
    MapData openMap(std::string mapName, sf::RenderWindow& window);

    ///editor
    //creating map
    bool createMap(std::string mapName, unsigned int width, unsigned int height, unsigned int layers);
    void changeMapDimensions(std::string mapName, unsigned int width, unsigned int height, unsigned int layers);
    //saving map and tiles used
    void saveMap(const std::vector <utl::Vector2ui>& tileMap, unsigned int width, unsigned int height, unsigned int layers);

    //helper
    int getTile(unsigned int x, unsigned int y, unsigned int layer, unsigned int mapWidth, unsigned int mapHeight);
private:
    ///names of items
    //mapInfo
    const std::string name_width = "width";
    const std::string name_height = "height";
    const std::string name_layers = "layers";

    //for tilework
    ResourceManager& resourceManager;

    //saves textures in 1 sheet
    TextureAtlas textureAtlas;
};

#endif // SAVEFILE_TILEENGINE_H
