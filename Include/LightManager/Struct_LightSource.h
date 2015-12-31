#ifndef STRUCT_LIGHTSOURCE_H
#define STRUCT_LIGHTSOURCE_H

#include <string>
#include <SFML/Graphics.hpp>

struct Struct_LightSource
{
    int id;
    unsigned char lightShape;

    sf::CircleShape circle;
    sf::RectangleShape rect;

    sf::Color colorOverlay;
    float brighness;

    sf::Sprite lightSprite;
};

#endif // STRUCT_LIGHTSOURCE_H
