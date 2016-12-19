#ifndef TILEENGINE_EDITOR_H
#define TILEENGINE_EDITOR_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "TileEngine.h"
#include "ResourceManager.h"

#include "Utl.h"

#include "SaveFile_TileEngine.h"

class TileEngine_Editor : public TileEngine
{
public:
    //ctor + dtor
    TileEngine_Editor(sf::RenderWindow& _window, ResourceManager& _resourceManager);
    ~TileEngine_Editor() = default;

    void createMap(std::string mapName, unsigned int width, unsigned int height, unsigned int layers);

    ///gets called instead of base class
    void loadMap(std::string _mapName);
    //draws map with sprites
    void drawMap();
    //draws out all tiles
    void drawTiles();

    //get map data
    unsigned int getMapWidth();
    unsigned int getMapHeight();
    unsigned int getMapLayers();

    //debugging
    void displayTiles();

private:
    //stores all tiles for drawing
    std::vector<std::pair<std::string, std::vector<Tile*> > > sortedTiles;

    //grid to know where invisible tiles are
    void drawGridLines();
    sf::VertexArray gridLines;

    //save
    SaveFile_TileEngine saveFile;

    //helpers
    std::pair<std::string, std::vector<Tile*> >& getFolder(const std::string& dir);
};

#endif // TILEENGINE_EDITOR_H
