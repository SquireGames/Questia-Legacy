#include "LightManager.h"

LightManager::LightManager(sf::RenderWindow &mWindow,TimeManager& _timeManager, ResourceManager& _resourceManager):
    window(mWindow)
    , timeManager(_timeManager)
    , resourceManager(_resourceManager)
{
    lightingOverlayTexture.create(960,540);
    lightingOverlaySprite.setTexture(lightingOverlayTexture.getTexture());
    lightingOverlaySprite.setOrigin(480,270);
    lightingOverlaySprite.setPosition(0,0);
    lightingOverlaySprite.setTextureRect(sf::IntRect(0,0,960,540));

    blackwhiteOverlay = sf::Color(0,0,0,255);
    colorOverlay      = sf::Color(0,0,0,0);

    blackwhiteRect.setSize(sf::Vector2f(960,540));
    blackwhiteRect.setPosition(0,0);
    blackwhiteRect.setFillColor(blackwhiteOverlay);

    colorRect.setSize(sf::Vector2f(960,540));
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

    brightness = brightness - 100;
    if(brightness < 0)
    {
        brightness *= -1;
    }
    if(brightness > 100)
    {
        brightness = 100;
    }
    else if(brightness < 0)
    {
        brightness = 0;
    }
    brightness = brightness / 100 * 255;

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
        lightSource->circle.setPosition(coordinates.x + 480, coordinates.y + 270);
    }
    break;
    case 2:
    {
        lightSource->lightShape = 2;

        lightSource->rect;
        lightSource->rect.setSize(sideRadius);
        lightSource->rect.setOrigin(0, 0);

        sf::Color filling = sf::Color::Transparent;
        filling.a = brightness;

        lightSource->rect.setFillColor(filling);
        lightSource->rect.setPosition(coordinates.x + 480, coordinates.y + 270);
    }
    break;
    case 3:
    {
        lightSource->lightShape = 3;

        lightSource->lightSprite;
        lightSource->lightSprite.setTexture(resourceManager.getTexture(std::string("Media/Image/Game/Lighting/Light_Circle_1.png")));
        lightSource->lightSprite.setScale((sideRadius.x*2.f)/ lightSource->lightSprite.getLocalBounds().width,(sideRadius.y*2.f)/ lightSource->lightSprite.getLocalBounds().height);
        lightSource->lightSprite.setOrigin(lightSource->lightSprite.getLocalBounds().width/2, lightSource->lightSprite.getLocalBounds().height/2);

        lightSource->lightSprite.setPosition(coordinates.x + 480, coordinates.y + 270);
    }
    break;
    case 4:
    {
        lightSource->lightShape = 3;

        lightSource->lightSprite;
        lightSource->lightSprite.setTexture(resourceManager.getTexture(std::string("Media/Image/Game/Lighting/Light_Circle_1.png")));
        lightSource->lightSprite.setScale((sideRadius.x*2.f)/ lightSource->lightSprite.getLocalBounds().width,(sideRadius.y*2.f)/ lightSource->lightSprite.getLocalBounds().height);
        lightSource->lightSprite.setOrigin(lightSource->lightSprite.getLocalBounds().width/2, lightSource->lightSprite.getLocalBounds().height/2);

        lightSource->lightSpriteColor;
        lightSource->lightSpriteColor.setTexture(resourceManager.getTexture(std::string("Media/Image/Game/Lighting/Light_Circle_2.png")));
        lightSource->lightSpriteColor.setScale((sideRadius.x*3.f)/ lightSource->lightSprite.getLocalBounds().width,(sideRadius.y*3.f)/ lightSource->lightSprite.getLocalBounds().height);
        lightSource->lightSpriteColor.setOrigin(lightSource->lightSprite.getLocalBounds().width/2, lightSource->lightSprite.getLocalBounds().height/2);
        lightSource->lightSpriteColor.setColor(sf::Color(255,215,0,0));


        lightSource->lightSprite.setPosition(coordinates.x + 480, coordinates.y + 270);
        lightSource->lightSpriteColor.setPosition(coordinates.x + 480, coordinates.y + 270);
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
                lightingList[x]->circle.setPosition(coordinates.x + 480, coordinates.y + 270);
            }
            else if(lightingList[x]->lightShape == 2)
            {
                lightingList[x]->rect.setPosition(coordinates.x + 480, coordinates.y + 270);
            }
            else if(lightingList[x]->lightShape == 3)
            {
                lightingList[x]->lightSprite.setPosition(coordinates.x + 480, coordinates.y + 270);
                lightingList[x]->lightSpriteColor.setPosition(coordinates.x + 480, coordinates.y + 270);
            }
            return;
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

void LightManager::updateLighting()
{
    float brightness = (100 * std::sin(   (timeManager.getDecimalTime() - 6.f) * 0.26179f   )) + 90;

    if(brightness > 100)
    {
        brightness = 100;
    }
    else if(brightness < 0)
    {
        brightness = 0;
    }

    brightness = brightness - 100;
    if(brightness < 0)
    {
        brightness = brightness * -1;
    }

    brightness = brightness / 100.f * 255.f;

    blackwhiteOverlay.a = brightness;

    for(int x = 0; x != lightingList.size(); x++)
    {
        if(lightingList[x]->lightShape == 3)
        {
            sf::Color tempColor = lightingList[x]->lightSpriteColor.getColor();

            if(brightness < 120)
            {
                tempColor.a = brightness;
            }
            else
            {
                tempColor.a = 120;
            }
            lightingList[x]->lightSpriteColor.setColor(tempColor);
        }
    }
}

void LightManager::drawLighting()
{
    updateLighting();

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

            if(std::abs(lightingList[x]->circle.getPosition().x - 480) < 2000 &&  std::abs(lightingList[x]->circle.getPosition().y - 270) < 1500)
            {
                lightingOverlayTexture.draw(lightingList[x]->circle, sf::BlendMultiply);
            }


            lightingList[x]->circle.setPosition(temp);
        }
        else if(lightingList[x]->lightShape == 2)
        {
            sf::Vector2f temp = lightingList[x]->rect.getPosition();
            lightingList[x]->rect.setPosition(lightingList[x]->rect.getPosition().x - playerCoordinates.x,
                                              lightingList[x]->rect.getPosition().y - playerCoordinates.y);

            if(std::abs(lightingList[x]->rect.getPosition().x - 480) < 3000 &&  std::abs(lightingList[x]->rect.getPosition().y - 270) < 2000)
            {
                lightingOverlayTexture.draw(lightingList[x]->rect, sf::BlendMultiply);
            }

            lightingList[x]->rect.setPosition(temp);
        }
        else if(lightingList[x]->lightShape == 3)
        {
            sf::Vector2f temp = lightingList[x]->lightSprite.getPosition();

            lightingList[x]->lightSprite.setPosition(lightingList[x]->lightSprite.getPosition().x - playerCoordinates.x,
                                                     lightingList[x]->lightSprite.getPosition().y - playerCoordinates.y);

            if(std::abs(lightingList[x]->lightSprite.getPosition().x - 480) < 2000 &&  std::abs(lightingList[x]->lightSprite.getPosition().y - 270) < 1500)
            {
                lightingOverlayTexture.draw(lightingList[x]->lightSprite, sf::BlendMultiply);
            }

            lightingList[x]->lightSprite.setPosition(temp);
        }
    }
    for(int x = 0; x != lightingList.size(); x++)
    {
        if(lightingList[x]->lightShape == 3)
        {
            sf::Vector2f temp = lightingList[x]->lightSpriteColor.getPosition();

            lightingList[x]->lightSpriteColor.setPosition(lightingList[x]->lightSpriteColor.getPosition().x - playerCoordinates.x,
                                                          lightingList[x]->lightSpriteColor.getPosition().y - playerCoordinates.y);

            if(std::abs(lightingList[x]->lightSpriteColor.getPosition().x - 480) < 2000 &&  std::abs(lightingList[x]->lightSpriteColor.getPosition().y - 270) < 1500)
            {
                lightingOverlayTexture.draw(lightingList[x]->lightSpriteColor);
            }

            lightingList[x]->lightSpriteColor.setPosition(temp);
        }
    }

    lightingOverlayTexture.display();
    window.draw(lightingOverlaySprite);
    lightingOverlayTexture.clear(sf::Color::Transparent);
}
