#include "GuiManager.h"
#include <iostream>


GuiManager::GuiManager(sf::RenderWindow &_window,  ResourceManager &res, bool gameOverlay):
    statLayers(0)
    , window(_window)
    , overlayVisible(false)
    , timer(25)
    , res(res)
    , gameOverlay(gameOverlay)
{
    if(gameOverlay)
    {
        if(!guiTexture.loadFromFile("Media/Image/Game/Gui/playerGui.png")) {}
        guiSprite.setTexture(guiTexture);
        guiSprite.setPosition(0,973);

        statisticsTextHP.setFont(Data_Desktop::getInstance().font1);
        statisticsTextHP.setCharacterSize(25);
        statisticsTextHP.setColor(sf::Color::Black);
        statisticsTextHP.setPosition(260,1047);

        statisticsTextMP.setFont(Data_Desktop::getInstance().font1);
        statisticsTextMP.setCharacterSize(25);
        statisticsTextMP.setColor(sf::Color::Black);
        statisticsTextMP.setPosition(900,1047);

        statisticsTextStamina.setFont(Data_Desktop::getInstance().font1);
        statisticsTextStamina.setCharacterSize(25);
        statisticsTextStamina.setColor(sf::Color::Black);
        statisticsTextStamina.setPosition(1469,1047);
    }
    else
    {
        overlayVisible = true;
    }
}

void GuiManager::toggleOverlay()
{
    if(buttonTimer())
    {
        if(overlayVisible)
        {
            overlayVisible = false;
        }
        else
        {
            overlayVisible = true;
        }
    }
}

bool GuiManager::buttonTimer()
{
    if(timer == 25)
    {
        timer = 0;
        return true;
    }
    else
    {
        return false;
    }
}


void GuiManager::setStats(std::tuple<int, int, int, int, int, int> statsTuple)
{
    int HP, MP, ST;
    int maxHP, maxMP, maxST;
    float HPP, MPP, STP;

    std::tie(HP,MP,ST,maxHP,maxMP,maxST) = statsTuple;

    HPP = (float)HP/(float)maxHP;
    MPP = (float)MP/(float)maxMP;
    STP = (float)ST/(float)maxST;

    hpSprite.setTextureRect(sf::IntRect(0,0,394*(HPP),13));
    mpSprite.setTextureRect(sf::IntRect(0,0,394*(MPP),13));
    stSprite.setTextureRect(sf::IntRect(0,0,394*(STP),13));

    //HP, MP, Stamina
    os << HP << " / " << maxHP;
    statisticsTextHP.setString(os.str());
    os.str(std::string());
    os << MP << " / " << maxMP;
    statisticsTextMP.setString(os.str());
    os.str(std::string());
    os << ST << " / " << maxST;
    statisticsTextStamina.setString(os.str());
    os.str(std::string());
}

void GuiManager::drawGui()
{
    if(timer!=25)
    {
        timer++;
    }

    if(gameOverlay)
    {
        window.draw(guiSprite);

        window.draw(hpSprite);
        window.draw(mpSprite);
        window.draw(stSprite);

        window.draw(statisticsTextHP);
        window.draw(statisticsTextMP);
        window.draw(statisticsTextStamina);

    }

    if(overlayVisible)
    {
        for(auto mapIterator = gameDebuggerStrings.begin(); mapIterator!= gameDebuggerStrings.end(); mapIterator++)
        {
            window.draw(mapIterator->second);
        }
    }

    for(auto mapIterator = buttonMap.begin(); mapIterator!= buttonMap.end(); mapIterator++)
    {
        bool transparent;
        sf::Sprite buttonSprite;
        sf::Vector2i bounds;
        sf::Text buttonText;
        bool overlay;
        sf::RectangleShape rect;

        std::tie(transparent, buttonSprite, buttonText, rect, overlay) = mapIterator->second;

        if(!transparent)
        {
            window.draw(buttonSprite);
            window.draw(buttonText);
            if(overlay)
            {
                window.draw(rect);
            }
        }
    }
}

void GuiManager::addButton(unsigned short buttonID, bool transparent, unsigned short x_b, unsigned short y_b, std::string filePath,
                           std::string text, unsigned short x_t, unsigned short y_t, unsigned short textStyle, unsigned short textSize, sf::Color textColor,
                           sf::Color overlayColor)
{
    sf::Sprite buttonSprite;
    buttonSprite.setTexture (res.getTexture(filePath));
    buttonSprite.setPosition (x_b, y_b);

    sf::Text buttonText;
    buttonText.setString(text);
    buttonText.setPosition(x_t, y_t);
    switch (textStyle)
    {
    case 0:
        break;
    case 1:
        buttonText.setFont(Data_Desktop::getInstance().font1);
        break;
    }
    buttonText.setCharacterSize(textSize);
    buttonText.setColor(textColor);

    sf::RectangleShape rect;

    rect.setFillColor(overlayColor);
    rect.setPosition(x_b, y_b);
    rect.setSize(sf::Vector2f(buttonSprite.getGlobalBounds().width ,buttonSprite.getGlobalBounds().height));

    buttonMap[buttonID] = std::make_tuple(transparent, buttonSprite,  buttonText, rect, false);
}

void GuiManager::buttonCheck()
{
    sf::Vector2f  mouse = Data_Desktop::getInstance().getScaledMousePosition(window);
    for(auto mapIterator = buttonMap.begin(); mapIterator!= buttonMap.end(); mapIterator++)
    {
        bool transparent;
        sf::Sprite buttonSprite;
        sf::Vector2i bounds;
        sf::Text buttonText;
        bool overlay;
        sf::RectangleShape rect;

        std::tie(transparent, buttonSprite, buttonText, rect, overlay) = mapIterator->second;

        if (buttonSprite.getGlobalBounds().contains(mouse))
        {
            overlay = true;
        }
        else
        {
            overlay = false;
        }
        mapIterator->second = std::make_tuple(transparent, buttonSprite,  buttonText, rect, overlay);
    }
}

bool GuiManager::testButton(unsigned short buttonID)
{
    sf::Vector2f  mouse = Data_Desktop::getInstance().getScaledMousePosition(window);

    bool transparent;
    sf::Sprite buttonSprite;
    sf::Vector2i bounds;
    sf::Text buttonText;
    bool overlay;
    sf::RectangleShape rect;

    std::tie(transparent, buttonSprite, buttonText, rect, overlay) =  buttonMap[buttonID];

    if(!transparent)
    {
        if (buttonSprite.getGlobalBounds().contains(mouse))
        {
            if(buttonID >= 1000)
            {
                return true;
            }
            else if(buttonTimer())
            {
                return true;
            }
        }
    }
    return false;
}

void GuiManager::changeVisibility(int button, bool transparent)
{
    bool transparentTemp;
    sf::Sprite buttonSprite;
    sf::Vector2i bounds;
    sf::Text buttonText;
    bool overlay;
    sf::RectangleShape rect;

    std::tie(transparentTemp, buttonSprite, buttonText, rect, overlay) = buttonMap[button];

    if(transparentTemp != transparent)
    {
        buttonMap[button] = std::make_tuple(transparent, buttonSprite,  buttonText, rect, false);
    }
}

void GuiManager::rotateSprite(int button, int degrees)
{
    bool transparent;
    sf::Sprite sprite;
    sf::Vector2i bounds;
    sf::Text buttonText;
    bool overlay;
    sf::RectangleShape rect;

    std::tie(transparent, sprite, buttonText, rect, overlay) = buttonMap[button];

    sprite.setOrigin(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    sprite.setRotation(degrees);

    buttonMap[button] = std::make_tuple(transparent, sprite,  buttonText, rect, false);
}

void GuiManager::moveSprite(int button, int x, int y)
{
    bool transparent;
    sf::Sprite sprite;
    sf::Vector2i bounds;
    sf::Text buttonText;
    bool overlay;
    sf::RectangleShape rect;

    std::tie(transparent, sprite, buttonText, rect, overlay) = buttonMap[button];

    sf::Vector2f textOffset;
    textOffset.x = x + (buttonText.getPosition().x - sprite.getPosition().x);
    textOffset.y = y + (buttonText.getPosition().y - sprite.getPosition().y);

    buttonText.setPosition(textOffset);

    sprite.setPosition(x, y);

    sf::Vector2f rectOffset;
    rectOffset.x = sprite.getPosition().x;
    rectOffset.y = sprite.getPosition().y;

    rect.setPosition(rectOffset);

    buttonMap[button] = std::make_tuple(transparent, sprite,  buttonText, rect, false);
}

sf::Vector2i GuiManager::getButtonCoords(int button)
{
    bool transparent;
    sf::Sprite sprite;
    sf::Vector2i bounds;
    sf::Text buttonText;
    bool overlay;
    sf::RectangleShape rect;

    std::tie(transparent, sprite, buttonText, rect, overlay) = buttonMap[button];

    return sf::Vector2i(sprite.getPosition());
}

void GuiManager::deleteButton(int button)
{
    buttonMap.erase(button);
}


