#ifndef STRUCT_ANIMATION_H
#define STRUCT_ANIMATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ResourceManager.h>
#include <map>

#include "iostream"

struct SpriteSheet
{
    SpriteSheet(ResourceManager& _resourceManager, std::string imageLocation, unsigned int slides_x, unsigned int slides_y):
        res(_resourceManager)
        , spriteMap()
        , size_x(0)
        , size_y(0)
    {
        sf::Texture animationSheet;

        if (!animationSheet.loadFromFile(imageLocation))
        {
            return;
        }

        sf::Vector2<unsigned int> imageSize = animationSheet.getSize();

        //regular size
        size_x = (imageSize.x - (slides_x - 1)) / slides_x;
        size_y = (imageSize.y - (slides_y - 1)) / slides_y;

        for(unsigned int it_1 = 0; it_1 < slides_x; it_1++)
        {
            for(unsigned int it_2 = 0; it_2 < slides_y; it_2++)
            {
                sf::Sprite sheet;
                sheet.setTexture(res.getTexture(imageLocation));
                sheet.setTextureRect(sf::IntRect((it_1 * size_x) + it_1 + 1,// +1 to avoid the boundary clipping
                                                 (it_2 * size_y) + it_2 + 1,
                                                 size_x - 2, //-2 to avoid the boundary clipping
                                                 size_y - 2));
                spriteMap[it_1] [it_2] = sheet;

                sf::IntRect tempRect = sheet.getTextureRect();
                std::cout << "---------------------" << std::endl;
                std::cout << "x: " << tempRect.left << std::endl;
                std::cout << "y: " << tempRect.top << std::endl;
                std::cout << "width: " << tempRect.width << std::endl;
                std::cout << "height: " << tempRect.height << std::endl;
            }
        }
        //account for boundary clipping
        size_x -= 2;
        size_y -= 2;
    }

    sf::Sprite& getSprite(unsigned int map_x, unsigned int map_y)
    {
        return spriteMap[map_x][map_y];
    }

    unsigned int getSheetWidth()
    {
        return size_x;
    }
    unsigned int getSheetHeight()
    {
        return size_y;
    }


    //Variables
    ResourceManager &res;
    std::map<int, std::map<int, sf::Sprite> > spriteMap;
    unsigned int size_x;
    unsigned int size_y;
};

#endif // STRUCT_ANIMATION_H
