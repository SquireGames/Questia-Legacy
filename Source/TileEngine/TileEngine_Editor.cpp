#include "TileEngine_Editor.h"

//ctor
TileEngine_Editor::TileEngine_Editor(sf::RenderWindow& _window, ResourceManager& _resourceManager):
    TileEngine(_window, _resourceManager)
    , gridLines()
    , saveFile(_resourceManager)
{
    gridLines.setPrimitiveType(sf::PrimitiveType::Lines);
}

void TileEngine_Editor::createMap(std::string mapName, unsigned int width, unsigned int height, unsigned int layers)
{
    saveFile.createMap(mapName, width, height, layers);
}

void TileEngine_Editor::loadMap(std::string _mapName)
{
    TileEngine::loadMap(_mapName, SaveFile_TileEngine::TextureMode::All, SaveFile_TileEngine::TileMode::Sprite);
    //2 vertices
    gridLines.resize((mapWidth + 1) * 2 + ((mapHeight + 1) * 2));
    //vertex count
    unsigned int vertexCount = 0;
    //vertex
    sf::Vertex vertex;
    vertex.color = sf::Color::Black;
    //horizontal lines
    for(unsigned int it = 0; it != (mapHeight + 1); it++)
    {
        vertex.position = sf::Vector2f(0, it * 64);
        gridLines[vertexCount] = vertex;
        vertexCount++;
        vertex.position = sf::Vector2f(mapWidth * 64, it * 64);
        gridLines[vertexCount] = vertex;
        vertexCount++;
    }
    //vertical lines
    for(unsigned int it = 0; it != (mapWidth + 1); it++)
    {
        vertex.position = sf::Vector2f(it * 64, 0);
        gridLines[vertexCount] = vertex;
        vertexCount++;
        vertex.position = sf::Vector2f(it * 64, mapHeight * 64);
        gridLines[vertexCount] = vertex;
        vertexCount++;
    }

    //iterate through tiles, sort by folders
    for(auto& it : tileStorage)
    {
        Tile& tile = it.second;
        std::string& folder = tile.folder;

        std::pair<std::string, std::vector<Tile*> >& tileDir = getFolder(folder);
        tileDir.second.push_back(&tile);
    }
}
std::pair<std::string, std::vector<Tile*> >& TileEngine_Editor::getFolder(const std::string& dir)
{
    for(auto& it : sortedTiles)
    {
        std::string& tileDir = it.first;
        if(dir == tileDir)
        {
            return it;
        }
    }
    sortedTiles.push_back(std::make_pair(dir, std::vector<Tile*>()));
    return sortedTiles.back();
}

void TileEngine_Editor::drawMap()
{
    TileEngine::drawTiles();
    drawGridLines();
}

void TileEngine_Editor::drawTiles()
{
    for(unsigned int it_folder = 0; it_folder != sortedTiles.size(); it_folder++)
    {
        std::string& tileDir = sortedTiles[it_folder].first;
        std::vector<Tile*>& tiles = sortedTiles[it_folder].second;
        for(unsigned int it_tile = 0; it_tile != tiles.size(); it_tile++)
        {
            Tile& tile = *tiles[it_tile];
            tile.setPosition(it_tile, it_folder);
            tile.drawTile();
        }
    }
}

void TileEngine_Editor::drawGridLines()
{
    window.draw(gridLines);
}

void TileEngine_Editor::displayTiles()
{
    std::cout << "-------------------" << std::endl;

    for(auto& it : sortedTiles)
    {
        std::string& tileDir = it.first;
        std::vector<Tile*>& tiles = it.second;

        std::cout << "Folder: " << tileDir << std::endl;
        for(auto& tile : tiles)
        {
            std::cout << "  -" << tile->tileName << std::endl;
        }
    }
    std::cout << "-------------------" << std::endl;
}

unsigned int TileEngine_Editor::getMapWidth()
{
    return mapWidth;
}
unsigned int TileEngine_Editor::getMapHeight()
{
    return mapHeight;
}
unsigned int TileEngine_Editor::getMapLayers()
{
    return mapLayers;
}
