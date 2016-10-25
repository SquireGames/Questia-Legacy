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

    //gets called instead of base class
    void loadMap(std::string _mapName);
    void drawMap();

private:
    //grid to know where invisible tiles are
    void drawGridLines();
    sf::VertexArray gridLines;

    //save
    SaveFile_TileEngine saveFile;
};

#endif // TILEENGINE_EDITOR_H
