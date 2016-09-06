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
        //set origin for rotations and flips
        tileOriginOffset = utl::Vector2f(tileSprite.getLocalBounds().width / 2.f, tileSprite.getLocalBounds().height / 2.f);
        tileSprite.setOrigin(tileOriginOffset.x, tileOriginOffset.y);
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
        tileSprite.setPosition(x * 64 + 2 * tileOriginOffset.x, y * 64 + 2 * tileOriginOffset.y);
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
        //set origin for rotations and flips
        tileOriginOffset = utl::Vector2f(tilesWidth * 32, tilesHeight * 32);
        tileSprite.setOrigin(tileOriginOffset.x, tileOriginOffset.y);
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
        tileSprite.setRotation(_degrees);
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
    {
        const int& width  = tileSprite.getLocalBounds().width;
        const int& height = tileSprite.getLocalBounds().height;
        switch (direction)
        {
        case 'x':
            tileSprite.setTextureRect(sf::IntRect(width, 0, -width, height));
            break;
        case 'y':
            tileSprite.setTextureRect(sf::IntRect(0, height, width, -height));
            break;
        case 'b':
            tileSprite.setTextureRect(sf::IntRect(width, height, -width, -height));
            break;
        default:
            break;
        }
    }
    break;
    case TileType::texture:
        flip = direction;
        break;
    }
}
void Tile::setCollisionRect(int x, int y, int width, int height)
{
    collisionRect = utl::IntRect(x, y, width, height);
}
utl::IntRect& Tile::getCollisionRect()
{
    return collisionRect;
}
