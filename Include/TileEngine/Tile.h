#ifndef TILE_H
#define TILE_H

#include <SFML/Window.hpp>

#include "Utl.h"
#include "ResourceManager.h"

///not stored in actual map but moved and drawn to screen
class Tile
{
public:
    Tile(sf::RenderWindow& _window, ResourceManager& _resourceManager):
        window(_window)
        , resourceManager(_resourceManager)
    {

    }
    ~Tile()
    {

    }

    //tile animated or static
    enum class TileType {sprite, animation};
    TileType tileType = TileType::sprite;

    //draws tile
    void drawTile()
    {
        switch(tileType)
        {
        case TileType::sprite:
            window.draw(tileSprite);
            break;
        case TileType::animation:
            break;
        }
    }

    //tile init
    void setTexture(std::string filePath)
    {
        switch(tileType)
        {
        case TileType::sprite:
            tileSprite.setTexture(resourceManager.getTexture(filePath));
            break;
        case TileType::animation:
            break;
        }
    }
    void setPosition(int x, int y)
    {
        switch(tileType)
        {
        case TileType::sprite:
            tileSprite.setPosition(x * 64, y * 64);
            break;
        case TileType::animation:
            break;
        }
    }
    void setSize(unsigned int tilesWidth, unsigned int tilesHeight)
    {
        switch(tileType)
        {
        case TileType::sprite:
            tileSprite.setScale(64.f / tileSprite.getLocalBounds().width * tilesWidth, 64 / tileSprite.getLocalBounds().height * tilesHeight);
            break;
        case TileType::animation:
            break;
        }
    }
    void setRotate(unsigned int degrees)
    {
        switch(tileType)
        {
        case TileType::sprite:
            break;
        case TileType::animation:
            break;
        }
    }
    void setFlip(utl::Direction direction)
    {
        switch(tileType)
        {
        case TileType::sprite:
            break;
        case TileType::animation:
            break;
        }
    }

private:
    //possible types to render
    sf::Sprite tileSprite;
    //SpriteSheetNew tileSpriteSheet;

    //default
    sf::RenderWindow& window;
    ResourceManager& resourceManager;
};


#endif // TILE_H
