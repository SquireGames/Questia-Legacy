#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <set>

#include "TileEngine_Editor.h"

TileEngine_Editor::TileEngine_Editor(sf::RenderWindow &_window, std::string mapName):
    window(_window)
    , tileEngine(_window, resourceManager)
{
    std::cout<<"DEBUG: TileEngine_Editor Initialized"<<std::endl;
    tileEngine.loadMap(mapName, false);

    editTileMap[0] = tileEngine.getMapVector(0);
    editTileMap[1] = tileEngine.getMapVector(1);

    //tile_Texture_overlay.loadFromFile("Media/Image/Editor/tile_overlay.png");
    tile_Sprite_overlay.setTexture(tile_Texture_overlay);
}

TileEngine_Editor::~TileEngine_Editor()
{
    std::cout<<"DEBUG: TileEngine_Editor Destroyed"<<std::endl;
    saveCurrentMap();
}

void TileEngine_Editor::reLoadMap()
{
    int layers = editTileMap.size();
    for(int it = 0; it != layers; it++)
    {
        tileEngine.setMapVector(editTileMap[it], it);
    }
}


void TileEngine_Editor::tile_hover(sf::Vector2f mousePosition,  int selectionSize, sf::Vector2f coordinates)
{
    mousePosition.x = (int)mousePosition.x/32;
    mousePosition.y = (int)mousePosition.y/32;

    mousePosition.x = mousePosition.x*32 + (coordinates.x - 960);
    mousePosition.y = mousePosition.y*32 + (coordinates.y - 540);

    currentTileLocation.x = mousePosition.x/32+1;
    currentTileLocation.y = mousePosition.y/32+1;

    if (selectionSize == 1)
    {
        tile_Sprite_overlay.setPosition(mousePosition.x , mousePosition.y);
        tile_Sprite_overlay.setScale(1,1);
    }
    if (selectionSize == 3)
    {
        tile_Sprite_overlay.setPosition(mousePosition.x-32, mousePosition.y-32);
        tile_Sprite_overlay.setScale(3,3);
    }
    window.draw(tile_Sprite_overlay);
}

void TileEngine_Editor::returnIDList(sf::RenderWindow &window)
{
    for(auto it = tileEngine.tileIndex.begin(); it != tileEngine.tileIndex.end(); it++)
    {
        for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            tileEngine.loadTiles(it->first, it2->first,it->first, it2->first);
        }
    }
}

void TileEngine_Editor::replaceTile(sf::Vector2f mousePosition,  int selectionSize,sf::Vector2f coordinates,int layer)
{
    mousePosition.x = (int)mousePosition.x/32;
    mousePosition.y = (int)mousePosition.y/32;

    mousePosition.x = mousePosition.x*32 + (coordinates.x - 960);
    mousePosition.y = mousePosition.y*32 + (coordinates.y - 540);

    if (selectionSize == 1)
    {
        if(currentTileLocation.y>=1&&currentTileLocation.x>=0&& currentTileLocation.x<tileEngine.mapWidth+1&& currentTileLocation.y<tileEngine.mapHeight+1)
        {
            editTileMap[layer][currentTileLocation.y-1][currentTileLocation.x-1].y = newTileSelection.x+1;
            editTileMap[layer][currentTileLocation.y-1][currentTileLocation.x-1].x = newTileSelection.y;
        }
    }
    else if (selectionSize == 3)
    {
        if(currentTileLocation.y>=1&&currentTileLocation.x>=1&& currentTileLocation.x<tileEngine.mapWidth&& currentTileLocation.y<tileEngine.mapHeight-1)
        {
            editTileMap[layer][currentTileLocation.y-2][currentTileLocation.x-2].y = newTileSelection.x+1;
            editTileMap[layer][currentTileLocation.y-2][currentTileLocation.x-2].x = newTileSelection.y;

            editTileMap[layer][currentTileLocation.y-2][currentTileLocation.x-1].y = newTileSelection.x+1;
            editTileMap[layer][currentTileLocation.y-2][currentTileLocation.x-1].x = newTileSelection.y;

            editTileMap[layer][currentTileLocation.y-2][currentTileLocation.x].y = newTileSelection.x+1;
            editTileMap[layer][currentTileLocation.y-2][currentTileLocation.x].x = newTileSelection.y;

            editTileMap[layer][currentTileLocation.y-1][currentTileLocation.x-2].y = newTileSelection.x+1;
            editTileMap[layer][currentTileLocation.y-1][currentTileLocation.x-2].x = newTileSelection.y;

            editTileMap[layer][currentTileLocation.y-1][currentTileLocation.x-1].y = newTileSelection.x+1;
            editTileMap[layer][currentTileLocation.y-1][currentTileLocation.x-1].x = newTileSelection.y;

            editTileMap[layer][currentTileLocation.y-1][currentTileLocation.x].y = newTileSelection.x+1;
            editTileMap[layer][currentTileLocation.y-1][currentTileLocation.x].x = newTileSelection.y;

            editTileMap[layer][currentTileLocation.y][currentTileLocation.x-2].y = newTileSelection.x+1;
            editTileMap[layer][currentTileLocation.y][currentTileLocation.x-2].x = newTileSelection.y;

            editTileMap[layer][currentTileLocation.y][currentTileLocation.x-1].y = newTileSelection.x+1;
            editTileMap[layer][currentTileLocation.y][currentTileLocation.x-1].x = newTileSelection.y;

            editTileMap[layer][currentTileLocation.y][currentTileLocation.x].y = newTileSelection.x+1;
            editTileMap[layer][currentTileLocation.y][currentTileLocation.x].x = newTileSelection.y;
        }
    }
}


void TileEngine_Editor::tileSelection(sf::Vector2f mousePosition, sf::Vector2f coordinates)
{
    mousePosition.x -= 32;

    mousePosition.x = (int)mousePosition.x/32;
    mousePosition.y = (int)mousePosition.y/32;

    mousePosition.x = mousePosition.x*32 + (coordinates.x - 960);
    mousePosition.y = mousePosition.y*32 + (coordinates.y - 540);

    newTileSelection.x = mousePosition.x/32;
    newTileSelection.y = mousePosition.y/32;
}

void TileEngine_Editor::saveCurrentMap()
{
    std::set<std::pair<int, int> > tileSet;

    // Overwrite Layer 0
    std::ofstream overWrite_map;
    overWrite_map.open(tileEngine.mapDir, std::ofstream::out);
    overWrite_map << std::endl;

    for (unsigned int x=0; x < editTileMap[0].size(); x++)
    {
        if(x>0)
        {
            overWrite_map << std::endl;
        }

        for (unsigned int y=0; y < editTileMap[0][x].size(); y++)
        {
            overWrite_map << editTileMap[0][x][y].x << "," << editTileMap[0][x][y].y << "|";
            std::pair <int, int> tile = std::make_pair(editTileMap[0][x][y].x, editTileMap[0][x][y].y);
            tileSet.insert(tile);
        }
    }

    // Overwrite Layer 1
    std::ofstream overWrite_map2;
    overWrite_map2.open(tileEngine.mapDir2, std::ofstream::out);
    overWrite_map2 << std::endl;

    for (unsigned int x=0; x < editTileMap[1].size(); x++)
    {
        if(x>0)
        {
            overWrite_map2 << std::endl;
        }

        for (unsigned int y=0; y < editTileMap[1][x].size(); y++)
        {
            overWrite_map2 << editTileMap[1][x][y].x << "," << editTileMap[1][x][y].y << "|";
            std::pair <int, int> tile = std::make_pair(editTileMap[1][x][y].x, editTileMap[1][x][y].y);
            tileSet.insert(tile);
        }
    }

    //Iterate through list of tiles
    std::vector <sf::Vector2i> tileVector;
    for(std::set<std::pair<int, int> >::iterator it = tileSet.begin(); it != tileSet.end(); it++)
    {
        std::pair <int, int> tile;
        tile = *it;
        sf::Vector2i tileVec(tile.first, tile.second);
        tileVector.push_back(tileVec);
    }

    //Overwrite used tiles
    std::ofstream overWrite_tiles;
    overWrite_tiles.open(tileEngine.mapTiles, std::ofstream::out);
    for(unsigned int x = 0; x != tileVector.size(); x++)
    {
        if(tileVector[x].x != 0)
        {
            overWrite_tiles << tileVector[x].x << "," << tileVector[x].y << std::endl;
        }
    }
}

void TileEngine_Editor::drawTileMap(sf::RenderWindow &window, sf::Vector2f coordinates, float scaler,int layer, bool isDrawingCollision)
{
    scaler = ((scaler - 1) * 30) + 12;

    for (int x=(coordinates.y-13 -scaler); x < (coordinates.y+10 + scaler); x++)
    {
        for (int y=(coordinates.x-20 - scaler); y < (coordinates.x+18 + scaler); y++)
        {
            if (x>-1 && y > -1 && x < tileEngine.mapHeight && y < tileEngine.mapWidth)
            {
                if(isDrawingCollision)
                {
                    tileEngine.loadTiles(x, y, editTileMap[layer][x][y].x, editTileMap[layer][x][y].y);
                    if(editTileMap[layer][x][y].x == 60)
                    {
                        tileEngine.loadTiles(x, y, 50, 1);
                    }
                }
                else
                {
                    if(!(editTileMap[layer][x][y].x == 50 && editTileMap[layer][x][y].y == 1))
                    {
                        tileEngine.loadTiles(x, y, editTileMap[layer][x][y].x, editTileMap[layer][x][y].y);
                    }
                }
            }
        }
    }
}

void TileEngine_Editor::drawTileMap(sf::RenderWindow &window, sf::Vector2f coordinates, float scaler,int layer, int transparency)
{
    scaler = ((scaler - 1) * 30) + 12;

    for (int x=(coordinates.y-13 -scaler); x < (coordinates.y+10 + scaler); x++)
    {
        for (int y=(coordinates.x-20 - scaler); y < (coordinates.x+18 + scaler); y++)
        {
            if (x>-1 && y > -1 && x < tileEngine.mapHeight && y < tileEngine.mapWidth)
            {
                if(!(editTileMap[layer][x][y].x == 50 && editTileMap[layer][x][y].y == 1))
                {
                    tileEngine.loadTiles(x, y, editTileMap[layer][x][y].x, editTileMap[layer][x][y].y, transparency);
                }
            }
        }
    }
}
