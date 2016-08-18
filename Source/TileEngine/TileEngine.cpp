#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <utility>

#include "TileEngine/TileEngine.h"

TileEngineNew::TileEngineNew(sf::RenderWindow& _window, ResourceManager& _resourceManager):
    resourceManager(_resourceManager)
    , window(_window)
{
    /*
    tileStorage.emplace(std::make_pair(1,1), Tile(window, resourceManager));
    tileStorage.at(std::make_pair(1,1)).setTexture("Media/Image/Game/Tiles/01/01.png");
    tileStorage.at(std::make_pair(1,1)).setSize(1,1);

    tileStorage.emplace(std::make_pair(4,21), Tile(window, resourceManager));
    tileStorage.at(std::make_pair(4,21)).setTexture("Media/Image/Game/Tiles/04/21.png");
    tileStorage.at(std::make_pair(4,21)).setSize(1,1);

    tileStorage.emplace(std::make_pair(75,1), Tile(window, resourceManager));
    tileStorage.at(std::make_pair(75,1)).setTexture("Media/Image/Game/Tiles/75/01.png");
    tileStorage.at(std::make_pair(75,1)).setSize(1,1);
    */
}

TileEngineNew::~TileEngineNew()
{

}

void TileEngineNew::loadMap(std::string _mapName)
{
    //get info
    MapData mapData = saveFile.openMap(_mapName, window, resourceManager);

    //set info
    mapWidth = mapData.width;
    mapHeight = mapData.height;
    mapLayers = mapData.layers;
    maxTileSize_x = mapData.maxTileSize_x;
    maxTileSize_y = mapData.maxTileSize_y;

    //overriding the map fixes the need to clear it
    tileMap = std::move(mapData.tileMap);
    tileStorage = std::move(mapData.tileStorage);

    mapName = _mapName;
}

void TileEngineNew::drawMap()
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

    //iterate map
    for(int layerIt = 0; layerIt != mapLayers; layerIt++)
    {
        for(int tileIt_x = drawMin_x; tileIt_x <= drawMax_x; tileIt_x++)
        {
            for(int tileIt_y = drawMin_y; tileIt_y <= drawMax_y; tileIt_y++)
            {
                //get tile index and id
                const utl::Vector2ui& currentTileIndex = tileMap[getTile(tileIt_x, tileIt_y, layerIt)];

                //make sure its visible
                if(currentTileIndex.x != 0)
                {
                    //get actual tile
                    Tile& currentTile = tileStorage.at(std::make_pair(currentTileIndex.x, currentTileIndex.y));

                    //move to correct position and draw
                    currentTile.setPosition(tileIt_x, tileIt_y);
                    currentTile.drawTile();
                    //no sprite batching because of tile scaling and animations
                }
            }
        }
    }
}

void TileEngineNew::setPosition(int x, int y)
{
    cameraPosition.x = x;
    cameraPosition.y = y;
}

//helper
int TileEngineNew::getTile(unsigned int x, unsigned int y, unsigned int layer)
{
    return x + (mapWidth * y) + (layer * mapWidth * mapHeight);
}


////////////////////////////////
////////////////////////////////
/////////////OLD TILE ENGINE////
////////////////////////////////
////////////////////////////////
////////////////////////////////

TileEngine::TileEngine(sf::RenderWindow &_window, ResourceManager& _resourceManager):
    resourceManager(_resourceManager)
    , window(_window)
    , mapWidth(0)
    , mapHeight(0)
{
    std::cout<<"DEBUG: TileEngine Initialized"<<std::endl;
}

TileEngine::~TileEngine()
{
    std::cout<<"DEBUG: Destroyed Tile Engine"<<std::endl;
}

void TileEngine::local_loadMap(std::string mapName, int layer, bool isLimitingTextures)
{
    mapHeight = 0;
    mapWidth = 0;

    std::ifstream openfile;
    openfile.open(mapName);

    std::string dummyLine;
    std::getline(openfile, dummyLine);

    if (!openfile.is_open())
    {
        std::cout<<"DEBUG: Map "<<mapName<<" Failed to load"<<std::endl;
    }

    if(openfile.is_open())
    {
        std::cout<<"DEBUG: Map "<<mapName<<" Opened"<<std::endl;

        std::vector <std::vector <sf::Vector2i> > tileVector;
        std::vector<sf::Vector2i> tempMap;

        std::vector<std::string> tilesIndexName = Data_Desktop::getInstance().getFiles("Media/Image/Game/Tiles", false);
        for(std::string& tileIndexSt : tilesIndexName)
        {
            std::map<int, sf::Sprite> tileID;
            std::stringstream ss;
            std::string tileIDDir;
            ss << "Media/Image/Game/Tiles/" << tileIndexSt;
            ss >> tileIDDir;
            std::vector<std::string> tilesIDName = Data_Desktop::getInstance().getFiles(tileIDDir, false);

            for(std::string& tileIDSt : tilesIDName)
            {
                if(tileIsUsed(std::atoi(tileIndexSt.c_str()), std::atoi(tileIDSt.c_str()), isLimitingTextures))
                {
                    ss.clear();
                    if(tileIndexSt.length() < 2)
                    {
                        ss << "Media/Image/Game/Tiles/0" << tileIndexSt;
                    }
                    else
                    {
                        ss << "Media/Image/Game/Tiles/" << tileIndexSt;
                    }

                    if(std::atoi(tileIDSt.c_str()) < 10)
                    {
                        ss << "/0" << std::atoi(tileIDSt.c_str())<< ".png";
                    }
                    else
                    {
                        ss << "/" <<std::atoi(tileIDSt.c_str())<< ".png";
                    }

                    ss >> tileIDDir;

                    sf::Sprite tileSprite;
                    tileSprite.setTexture(resourceManager.getTexture(tileIDDir));

                    //If text file
                    if(tileSprite.getLocalBounds().height + tileSprite.getLocalBounds().width < 3)
                    {
                        std::ifstream openTile;
                        sf::Sprite tileSpriteCopy;
                        openTile.open(tileIDDir);
                        if(openTile.is_open())
                        {
                            while(!openTile.eof())
                            {
                                std::stringstream ss2;
                                std::string command;
                                std::string var;
                                std::string var2;

                                char line[200];
                                for(int y = 0; y!= 200; y++)
                                {
                                    line[y] = ' ';
                                }
                                openTile.getline(line, 200);
                                int character = 0;

                                for(char it = '?'; it != ' ';)
                                {
                                    it = line[character+1];
                                    ss2 << line[character];
                                    character++;
                                }
                                ss2 >> command;
                                ss2.clear();

                                for(char it = '?'; it != ' ';)
                                {
                                    it = line[character+1];
                                    ss2 << line[character];
                                    character++;
                                }
                                ss2 >> var;
                                ss2.clear();

                                for(char it = '?'; it != ' ' && it != '\0';)
                                {
                                    it = line[character+1];
                                    ss2 << line[character];
                                    character++;
                                }
                                ss2 >> var2;
                                ss2.clear();

                                if(command == "texture:")
                                {
                                    std::string textureLocation;
                                    ss2 << "Media/Image/Game/Tiles/" << var << "/" << var2 << ".png";
                                    ss2 >> textureLocation;
                                    std::cout<< textureLocation <<std::endl;
                                    tileSpriteCopy.setTexture(resourceManager.getTexture(textureLocation));
                                    ss2.clear();
                                }
                                else if(command == "origin:")
                                {
                                    tileSpriteCopy.setOrigin(std::atoi(var.c_str()), std::atoi(var2.c_str()));
                                }
                                else if(command == "rotate:")
                                {
                                    tileSpriteCopy.rotate(std::atoi(var.c_str()));
                                }
                                else if(command == "scale:")
                                {
                                    tileSpriteCopy.scale(std::atoi(var.c_str()), std::atoi(var2.c_str()));
                                }
                            }
                        }
                        tileID[std::atoi(tileIDSt.c_str())] = tileSpriteCopy;
                    }
                    else
                    {
                        tileID[std::atoi(tileIDSt.c_str())] = tileSprite;
                    }
                }
            }
            tileIndex[std::atoi(tileIndexSt.c_str())] = tileID;
            ss.clear();
        }

        while(!openfile.eof())
        {
            std::string str, value;
            std::getline(openfile, str);
            std::stringstream stringStream(str);

            while (std::getline(stringStream, value, '|'))
            {
                if(value.length() > 0)
                {
                    std::string x_a = value.substr(0, value.find(','));
                    std::string x_b = value.substr(value.find(',')+1);

                    int x, y, a, b;

                    for (a = 0; a < x_a.length(); a++)
                    {
                        if(x_a[a]== '00')
                        {
                            break;
                        }
                    }
                    for (b = 0; b < x_b.length(); b++)
                    {
                        if(x_b[b]== '00')
                        {
                            break;
                        }
                    }
                    if (a==x_a.length())
                    {
                        x = atoi(x_a.c_str());
                    }
                    if (b==x_b.length())
                    {
                        y = atoi(x_b.c_str());
                    }
                    mapWidth++;
                    tempMap.push_back(sf::Vector2i(x, y));
                }
            }
            tileVector.push_back(tempMap);
            tempMap.clear();
            mapHeight++;
        }
        mapWidth = mapWidth / mapHeight;

        tileMap[layer] = tileVector;
    }

    for(auto& it1 : tileIndex)
    {
        for(auto& it2 : it1.second)
        {
            it2.second.scale(2,2);
        }
    }
}

void TileEngine::loadMap(std::string mapName, bool isLimitingTextures)//, SpawnManager& spawnManager)
{
    std::string mapSt;
    std::stringstream ss;
    ss << "Maps/";
    ss << mapName;
    ss << "/map_0.txt";
    ss >> mapSt;
    mapDir = mapSt;

    std::string mapSt2;
    ss.clear();
    ss << "Maps/";
    ss << mapName;
    ss << "/map_1.txt";
    ss >> mapSt2;
    mapDir2 = mapSt2;

    std::string tiles;
    ss.clear();
    ss << "Maps/";
    ss << mapName;
    ss << "/tiles.txt";
    ss >> tiles;
    mapTiles = tiles;

    updateUsedTileList();
    local_loadMap(mapSt, 0, isLimitingTextures);
    local_loadMap(mapSt2, 1, isLimitingTextures);
}

void TileEngine::drawMap(sf::Vector2f coordinates)
{
    //std::cout<<"Map Width:"<<mapWidth<<std::endl;
    //std::cout<<"Map Height:"<<mapHeight<<std::endl;

    unsigned int layers = tileMap.size();

    for(unsigned int it = 0; it != layers; it++)
    {
        for (float x =(coordinates.y-13); x < (coordinates.y+6); x++)
        {
            for (float y =(coordinates.x-20); y < (coordinates.x+20); y++)
            {
                if (x>-1 && y > -1 && x < mapHeight && y < mapWidth)
                {
                    loadTiles(x, y, tileMap[it][x][y].x, tileMap[it][x][y].y);
                }
            }
        }
    }
}

void TileEngine::loadTiles(float x, float y, int index, int id)
{
    sf::Sprite& sprite = tileIndex[index][id];
    sprite.setPosition(y * 64.f, x * 64.f);
    window.draw(sprite);
}

void TileEngine::loadTiles(float x, float y, int index, int id, int transparency)
{
    sf::Sprite& sprite = tileIndex[index][id];
    sprite.setPosition(y * 64.f, x * 64.f);
    sf::Color tempColor = sprite.getColor();
    sprite.setColor(sf::Color(0,0,0,transparency));
    window.draw(sprite);
    sprite.setColor(tempColor);
}


int TileEngine::getMapCollision(sf::Vector2i mapCoordinates, sf::Vector2f playerCoordinates, sf::Vector2f getSideRadius, sf::Vector2f velocity, int (&returnCollision)[4])
{
    for(int a = 0; a<4; a++)
    {
        returnCollision[a] = 0;
    }

    int layers = tileMap.size();

    float tileTop, tileLeft;

    sf::FloatRect playerRectUp(playerCoordinates.x-getSideRadius.x,playerCoordinates.y-getSideRadius.y-velocity.y, getSideRadius.x*2,getSideRadius.y*2);
    sf::FloatRect playerRectDown(playerCoordinates.x-getSideRadius.x,playerCoordinates.y-getSideRadius.y+velocity.y, getSideRadius.x*2,getSideRadius.y*2);
    sf::FloatRect playerRectLeft(playerCoordinates.x-getSideRadius.x-velocity.x,playerCoordinates.y-getSideRadius.y, getSideRadius.x*2,getSideRadius.y*2);
    sf::FloatRect playerRectRight(playerCoordinates.x-getSideRadius.x+velocity.x,playerCoordinates.y-getSideRadius.y, getSideRadius.x*2,getSideRadius.y*2);

    for (int x=(mapCoordinates.y-2); x < (mapCoordinates.y+2); x++)
    {
        for (int y=(mapCoordinates.x-2); y < (mapCoordinates.x+2); y++)
        {
            if (x>-1 && y > -1 && x < mapHeight && y < mapWidth)
            {
                for(int it = 0; it != layers; it++)
                {
                    if(tileMap[it][x][y].x != 0 &&tileMap[it][x][y].y != 0 &&tileMap[it][x][y].x >= 50 && tileMap[it][x][y].x <75)
                    {
                        tileTop = x * 32.f;
                        tileLeft = y * 32.f;

                        sf::FloatRect tileRect(tileLeft, tileTop, 32.f, 32.f);

                        if(playerRectUp.intersects(tileRect))
                        {
                            returnCollision[0] = 1;
                        }
                        if(playerRectDown.intersects(tileRect))
                        {
                            returnCollision[2] = 1;
                        }
                        if(playerRectLeft.intersects(tileRect))
                        {
                            returnCollision[3] = 1;
                        }
                        if(playerRectRight.intersects(tileRect))
                        {
                            returnCollision[1] = 1;
                        }
                    }
                    else if (tileMap[it][x][y].x != 0 && tileMap[it][x][y].y != 0 && tileMap[it][x][y].x == 75 && tileMap[it][x][y].y % 2 == 1) //Right wall
                    {
                        tileTop = x * 32.f;
                        tileLeft = y * 32.f;

                        sf::FloatRect tileRect(tileLeft, tileTop, 4.f, 32.f);

                        if(playerRectUp.intersects(tileRect))
                        {
                            returnCollision[0] = 1;
                        }
                        if(playerRectDown.intersects(tileRect))
                        {
                            returnCollision[2] = 1;
                        }
                        if(playerRectLeft.intersects(tileRect))
                        {
                            returnCollision[3] = 1;
                        }
                        if(playerRectRight.intersects(tileRect))
                        {
                            returnCollision[1] = 1;
                        }
                    }
                    else if (tileMap[it][x][y].x != 0 && tileMap[it][x][y].y != 0 && tileMap[it][x][y].x == 75 && tileMap[it][x][y].y % 2 == 0) //Left wall
                    {
                        tileTop = x * 32.f;
                        tileLeft = y * 32.f;

                        sf::FloatRect tileRect(tileLeft+28.f, tileTop, 4.f, 32.f);

                        if(playerRectUp.intersects(tileRect))
                        {
                            returnCollision[0] = 1;
                        }
                        if(playerRectDown.intersects(tileRect))
                        {
                            returnCollision[2] = 1;
                        }
                        if(playerRectLeft.intersects(tileRect))
                        {
                            returnCollision[3] = 1;
                        }
                        if(playerRectRight.intersects(tileRect))
                        {
                            returnCollision[1] = 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

std::vector<std::vector <sf::Vector2i> > TileEngine::getMapVector(int layer)
{
    return tileMap[layer];
}

void TileEngine::setMapVector (std::vector<std::vector <sf::Vector2i> > MapVector, int layer)
{
    tileMap[layer] = MapVector;
}

bool TileEngine::tileIsUsed(int index, int id, bool isLimitingTextures)
{
    if(isLimitingTextures)
    {
        if(index != 0 && !(index == 50 && id == 1))
        {
            for(unsigned int x = 0; x != usedTileVector.size(); x++)
            {
                if(index == usedTileVector[x].x && id == usedTileVector[x].y)
                {
                    return true;
                }
            }
        }
        return false;
    }
    else
    {
        return true;
    }
}


void TileEngine::updateUsedTileList()
{
    std::stringstream ss;
    std::ifstream openfile;
    openfile.open(mapTiles);

    if(openfile.is_open())
    {
        while(!openfile.eof())
        {
            std::string x;
            std::string y;
            sf::Vector2i usedTile;

            char line[200];
            for(int y = 0; y!= 200; y++)
            {
                line[y] = ' ';
            }
            openfile.getline(line, 200);
            int character = 0;
            for(char it = '?'; it != ',' && it != '\0';)
            {
                it = line[character];
                ss << line[character];
                character++;
            }
            ss >> x;
            ss.clear();
            for(char it = '?'; it != ',' && it != '\0';)
            {
                it = line[character];
                ss << line[character];
                character++;
            }
            ss >> y;
            ss.clear();

            usedTile.x = std::atoi(x.c_str());
            usedTile.y = std::atoi(y.c_str());
            if(usedTile.x != 0)
            {
                usedTileVector.push_back(usedTile);
                std::cout << usedTile.x << ", " << usedTile.y << std::endl;
            }
        }
    }
}
