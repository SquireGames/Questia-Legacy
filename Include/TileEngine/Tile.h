#ifndef TILE_H
#define TILE_H

#include <SFML/Window.hpp>

#include "Utl.h"
#include "ResourceManager.h"

///not stored in actual map but moved and drawn to screen or used to find texture coords
class Tile
{
public:
    //ctor + dtor
    Tile(sf::RenderWindow& _window, ResourceManager& _resourceManager);
    ~Tile() = default;

    //tile single tile or texture (for sprite batching)
    enum class TileType {sprite, texture};
    TileType tileType = TileType::texture;

    //draws tile
    void drawTile();

    //only sprite
    void setTexture(std::string filePath);
    void setPosition(int x, int y);

    //spite and texture
    void setSize(unsigned int tilesWidth, unsigned int tilesHeight);
    void setRotate(int _degrees);
    void setFlip(char direction);

    //for 0,0 tiles
    utl::IntRect texturePosition = utl::IntRect(0,0,0,0);
    //(-1, -1) means sprite size
    utl::Vector2i tileSize = utl::Vector2i(-1, -1);
    //only 0, 90, 180, 270 are valid
    int degrees = 0;
    //only x, y, b(both), and n are valid
    char flip = 'n';

private:
    //not always used
    sf::Sprite tileSprite;
    utl::Vector2f tileOriginOffset = utl::Vector2f(0,0);

    //default
    sf::RenderWindow& window;
    ResourceManager& resourceManager;
};


#endif // TILE_H
