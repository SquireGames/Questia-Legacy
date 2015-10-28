#ifndef TILEENGINE_EDITOR_H
#define TILEENGINE_EDITOR_H

#include "TileEngine.h"
#include "ResourceManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>


class TileEngine_Editor
{
public:
    TileEngine_Editor(sf::RenderWindow &_window, std::string mapName);
    ~TileEngine_Editor();

    void reLoadMap();
    void tile_hover(sf::Vector2f mousePosition,  int selectionSize, sf::Vector2f coordinates);
    void tileSelection(sf::Vector2f mousePosition, sf::Vector2f coordinates);
    void replaceTile(sf::Vector2f mousePosition, int selectionSize, sf::Vector2f coordinates, int layer);
    void saveCurrentMap();

    void returnIDList(sf::RenderWindow &window);

    void drawTileMap(sf::RenderWindow &window, sf::Vector2f coordinates, float scaler, int layer);

    TileEngine tileEngine;
private:
    sf::RenderWindow& window;
    ResourceManager resourceManager;

    sf::Vector2i newTileSelection;
    sf::Vector2i currentTileLocation;

    sf::Texture tile_Texture_overlay;
    sf::Sprite  tile_Sprite_overlay;

    std::map<int, std::vector<std::vector <sf::Vector2i> > > editTileMap;

    int numberOfTiles;
};
#endif // TILEENGINE_EDITOR_H
