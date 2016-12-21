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
}

void TileEngine_Editor::drawTiles()
{
    for(unsigned int it_folder = 0; it_folder != sortedTiles.size(); it_folder++)
    {
        std::string& tileDir = sortedTiles[it_folder].first;
        std::vector<Tile*>& tiles = sortedTiles[it_folder].second;

        sf::Text dirText = sf::Text(tileDir, Data_Desktop::getInstance().font1, 20);
        dirText.setColor(sf::Color::Black);
        dirText.setPosition(0, (64 * (it_folder * 3)) - 30);
        window.draw(dirText);

        for(unsigned int it_tile = 0; it_tile != tiles.size(); it_tile++)
        {
            Tile& tile = *tiles[it_tile];
            tile.setPosition(it_tile, it_folder * 3);
            tile.drawTile();
        }
    }
}

void TileEngine_Editor::drawLayer(int layer, int transparency)
{
    //find boundaries
    int drawMin_x = (cameraPosition.x / 64.f) - (0.5 * tileFit_x) - (maxTileSize_x - 1);
    int drawMin_y = (cameraPosition.y / 64.f) - (0.5 * tileFit_y) - (maxTileSize_x - 1);
    int drawMax_x = (cameraPosition.x / 64.f) + (0.5 * tileFit_x);
    int drawMax_y = (cameraPosition.y / 64.f) + (0.5 * tileFit_y);

    //make sure they are within the map
    if(drawMin_x < 0)
    {
        drawMin_x = 0;
    }
    if(drawMin_y < 0)
    {
        drawMin_y = 0;
    }
    if(drawMax_x > (mapWidth-1))
    {
        drawMax_x = (mapWidth-1);
    }
    if(drawMax_y > (mapHeight-1))
    {
        drawMax_y = (mapHeight-1);
    }

    //changed transparency list
    std::vector<int> modifiedTiles = std::vector<int>();

    //iterate map
    for(int tileIt_x = drawMin_x; tileIt_x <= drawMax_x; tileIt_x++)
    {
        for(int tileIt_y = drawMin_y; tileIt_y <= drawMax_y; tileIt_y++)
        {
            //get tile index and id
            const int& currentTileIndex = tileMap[getTile(tileIt_x, tileIt_y, layer)];

            //make sure its visible
            if(currentTileIndex != 0)
            {
                //get actual tile
                Tile& currentTile = tileStorage.at(currentTileIndex);

                //change transparency if tile not yet changed
                if(std::find(modifiedTiles.begin(), modifiedTiles.end(), currentTileIndex) == modifiedTiles.end())
                {
                    modifiedTiles.push_back(currentTileIndex);
                    currentTile.setTransparency(transparency);
                }

                //move to correct position and draw
                currentTile.setPosition(tileIt_x, tileIt_y);
                currentTile.drawTile();
            }
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

void TileEngine_Editor::hoverTile(int x, int y)
{
    sf::RectangleShape hover = sf::RectangleShape(sf::Vector2f(64, 64));
    hover.setFillColor(sf::Color(255,0,255, 40));
    hover.setPosition(x*64, y*64);
    window.draw(hover);
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
