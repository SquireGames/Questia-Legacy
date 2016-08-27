#include "Tile.h"

Tile::Tile(sf::RenderWindow& _window, ResourceManager& _resourceManager):
    window(_window)
    , resourceManager(_resourceManager)
{

}

void Tile::drawTile()
{
    switch(tileType)
    {
    case TileType::sprite:
        window.draw(tileSprite);
        break;
    case TileType::texture:
        break;
    }
}

void Tile::setTexture(std::string filePath)
{
    switch(tileType)
    {
    case TileType::sprite:
        tileSprite.setTexture(resourceManager.getTexture(filePath));
        break;
    case TileType::texture:
        break;
    }
}
void Tile::setPosition(int x, int y)
{
    switch(tileType)
    {
    case TileType::sprite:
        tileSprite.setPosition(x * 64, y * 64);
        break;
    case TileType::texture:
        break;
    }
}
void Tile::setSize(unsigned int tilesWidth, unsigned int tilesHeight)
{
    switch(tileType)
    {
    case TileType::sprite:
        tileSprite.setScale(64.f / tileSprite.getLocalBounds().width * tilesWidth, 64 / tileSprite.getLocalBounds().height * tilesHeight);
    case TileType::texture:
        tileSize = utl::Vector2i(tilesHeight, tilesHeight);
        break;
    }
}
void Tile::setRotate(int _degrees)
{
    switch(tileType)
    {
    case TileType::sprite:
        break;
    case TileType::texture:
        degrees = _degrees;
        break;
    }
}
void Tile::setFlip(char direction)
{
    switch(tileType)
    {
    case TileType::sprite:
        break;
    case TileType::texture:
        flip = direction;
    break;
    }
}
