#ifndef STRUCT_ANIMATION_H
#define STRUCT_ANIMATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
#include "ResourceManager.h"

#include <iostream>

class SpriteSheet
{
public:
    SpriteSheet(ResourceManager& _resourceManager, std::string imageLocation, unsigned int slides_x, unsigned int slides_y);

    sf::Sprite& getSprite(unsigned int map_x, unsigned int map_y);

    unsigned int getSheetWidth();
    unsigned int getSheetHeight();

    void setSize(int width, int height);
    void setOrigin(float x, float y);

private:
    ResourceManager &res;
    std::map<int, std::map<int, sf::Sprite> > spriteMap;
    unsigned int size_x;
    unsigned int size_y;
};

class SpriteSheetNew
{
public:
    SpriteSheetNew();

    sf::Sprite& getSprite(unsigned int map_x, unsigned int map_y);

    unsigned int getSheetWidth();
    unsigned int getSheetHeight();

    void setSize(int width, int height);
    void setOrigin(float x, float y);

private:
    sf::Texture* texture = nullptr;
    //std::map<int, std::map<int, sf::Sprite> > spriteMap;
    unsigned int size_x;
    unsigned int size_y;
};

#endif // STRUCT_ANIMATION_H
