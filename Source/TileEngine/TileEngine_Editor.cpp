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
    TileEngine::loadMap(_mapName);
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
}

void TileEngine_Editor::drawMap()
{
    TileEngine::drawMap();
    drawGridLines();
}

void TileEngine_Editor::drawGridLines()
{
    window.draw(gridLines);
}


