#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Struct_LightSource.h"
#include "TimeManager/TimeManager.h"
#include "ResourceManager.h"

class LightManager
{
public:
    LightManager(sf::RenderWindow &mWindow, TimeManager& _timeManager, ResourceManager& _resourceManager);
    ~LightManager();

    void setLightOverlay_Coords(sf::Vector2f coords)      {lightingOverlaySprite.setPosition(coords); playerCoordinates = coords;}
    void setLightOverlay_White_Trans(float transparency);
    void setLightOverlay_Color_Shade(sf::Color);
    void setLightOverlay_Color_Trans(float transparency);

    int create_lightSource(sf::Vector2f coordinates, float brightness, unsigned char shapeType, sf::Vector2f sideRadius);
    int delete_lightSource(int id);

    void moveLightSource(int id, sf::Vector2f coordinates);

    void updateLighting();
    void drawLighting();

private:
    sf::Vector2f playerCoordinates;

    sf::RenderTexture lightingOverlayTexture;
    sf::Sprite        lightingOverlaySprite;

    sf::Color         blackwhiteOverlay;
    sf::Color         colorOverlay;

    sf::RectangleShape blackwhiteRect;
    sf::RectangleShape colorRect;

    int count_lightSources;
    std::vector <Struct_LightSource*> lightingList;

    sf::RenderWindow& window;
    TimeManager& timeManager;
    ResourceManager& resourceManager;
};

#endif // LIGHTMANAGER_H
