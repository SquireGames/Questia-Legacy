#include "LightManager.h"

LightManager::LightManager(sf::RenderWindow &mWindow):
    window(mWindow)
{
    lightingOverlayTexture.create(1920, 1080);
    lightingOverlaySprite.setTexture(lightingOverlayTexture.getTexture());
    lightingOverlaySprite.setOrigin(960,540);
    lightingOverlaySprite.setPosition(0,0);

    blackwhiteOverlay = sf::Color(0,0,0,255);
    colorOverlay      = sf::Color(0,0,0,0);

    blackwhiteRect.setSize(sf::Vector2f(1920,1080));
    blackwhiteRect.setPosition(0,0);
    blackwhiteRect.setFillColor(blackwhiteOverlay);

    colorRect.setSize(sf::Vector2f(1920,1080));
    colorRect.setPosition(0,0);
    colorRect.setFillColor(colorOverlay);

    playerCoordinates = sf::Vector2f(0,0);
}

LightManager::~LightManager()
{

}

int LightManager::create_lightSource(sf::Vector2f coordinates, float brightness, unsigned char shapeType, sf::Vector2f sideRadius)
{
    int IDNumber;

    std::vector<int> lightList;
    for(int x = 0; x < lightingList.size(); x++)
    {
        lightList.push_back(lightingList[x]->id);
    }

    std::sort(lightList.begin(),lightList.end());

    if(lightList.size() > 0)
    {
        if(lightingList.size() != lightList[lightList.size()-1]+1)
        {
            if(lightingList.size()>1)
            {
                for(int x = 0; x < lightList.size(); x++)
                {
                    if (lightList[x]+1 != lightList[x+1])
                    {
                        IDNumber = lightList[x]+1;
                        x = 999999;
                    }
                }
            }
            else
            {
                count_lightSources = lightList[lightList.size()-1]+1;
                IDNumber = count_lightSources;
            }
        }
        else
        {
            count_lightSources =  lightList[lightList.size()-1]+1;
            IDNumber = count_lightSources;
        }
    }
    else
    {
        count_lightSources =  0;
        IDNumber = count_lightSources;
    }

    Struct_LightSource* lightSource = new Struct_LightSource;



    switch(shapeType)
    {
    case 1:
    {
        lightSource->lightShape = 1;

        lightSource->circle;
        lightSource->circle.setRadius(sideRadius.x);
        lightSource->circle.setOrigin(sideRadius.x, sideRadius.x);

        sf::Color filling = sf::Color::Transparent;
        filling.a = brightness;

        lightSource->circle.setFillColor(filling);
        lightSource->circle.setPosition(coordinates.x + 960, coordinates.y + 540);
    }
    break;
    case 2:
    {
        lightSource->lightShape = 2;

        lightSource->rect;
        lightSource->rect.setSize(sideRadius);

        sf::Color filling = sf::Color::Transparent;
        filling.a = brightness;

        lightSource->rect.setFillColor(filling);
        lightSource->rect.setPosition(coordinates);
    }
    break;

    default:
        delete lightSource;
        return -1;
    }

    lightSource->id = IDNumber;
    lightingList.push_back(lightSource);

    std::cout << "New light src    : " << IDNumber << std::endl;

    return IDNumber;
}

void LightManager::moveLightSource(int id, sf::Vector2f coordinates)
{
    for(int x = 0; x != lightingList.size(); x++)
    {
        if(lightingList[x]->id == id)
        {
            if(lightingList[x]->lightShape == 1)
            {
                lightingList[x]->circle.setPosition(coordinates.x + 960, coordinates.y + 540);
            }
            else if(lightingList[x]->lightShape == 2)
            {
                lightingList[x]->rect.setPosition(coordinates.x + 960, coordinates.y + 540);
            }
        }
    }
}

int LightManager::delete_lightSource(int id)
{
    for(int x = 0; x < lightingList.size(); x++)
    {
        if(lightingList[x]->id==id)
        {
            delete lightingList[x];
            lightingList.erase(x + lightingList.begin());

            std::cout << "Deleted light src: " <<  id << std::endl;
        }
    }
}

void LightManager::drawLighting()
{
    blackwhiteRect.setFillColor(blackwhiteOverlay);
    colorRect.setFillColor(colorOverlay);

    lightingOverlayTexture.draw(blackwhiteRect);
    lightingOverlayTexture.draw(colorRect);

    for(int x = 0; x != lightingList.size(); x++)
    {
        if(lightingList[x]->lightShape == 1)
        {
            sf::Vector2f temp = lightingList[x]->circle.getPosition();
            lightingList[x]->circle.setPosition(lightingList[x]->circle.getPosition().x - playerCoordinates.x,
                                                lightingList[x]->circle.getPosition().y - playerCoordinates.y);
            lightingOverlayTexture.draw(lightingList[x]->circle, sf::BlendMultiply);
            lightingList[x]->circle.setPosition(temp);
        }
        else if(lightingList[x]->lightShape == 2)
        {
            //lightingOverlayTexture.draw(lightingList[x]->rect, sf::BlendMultiply);
        }
    }

    lightingOverlayTexture.display();

    window.draw(lightingOverlaySprite);
    lightingOverlayTexture.clear(sf::Color::Transparent);
}
