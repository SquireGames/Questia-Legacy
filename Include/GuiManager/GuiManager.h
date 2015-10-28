#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <tuple>
#include <SFML/Graphics.hpp>

#include <sstream>
#include <iostream>
#include <vector>

#include "StateManager/State.h"
#include "ResourceManager.h"
#include "Data_Desktop.h"


class GuiManager
{
public:
    GuiManager(sf::RenderWindow &_window, ResourceManager &resourceManager, bool gameOverlay);
    ResourceManager &res;

//In game overlay

    bool gameOverlay;
    void setStats(std::tuple<int, int, int, int, int, int> statsTuple);
    void toggleOverlay();
    bool buttonTimer();
    void drawGui();

    int statLayers;

    template <class T> void addStats(std::string statName, T stat)
    {
        bool dupe = false;
        for(auto mapIterator = gameDebuggerStrings.begin(); mapIterator!= gameDebuggerStrings.end(); mapIterator++)
        {
            if(mapIterator->first == statName)
            {
                os << statName << stat;
                mapIterator->second.setString(os.str());
                os.str(std::string());
                dupe = true;
            }
        }

        if(!dupe)
        {
            os << statName  << stat;
            sf::Text statText;
            statText.setString(os.str());
            statText.setFont(Data_Desktop::getInstance().font1);
            statText.setCharacterSize(30);
            statText.setColor(sf::Color::Yellow);
            statText.setPosition(10,(statLayers* 50)+10);
            gameDebuggerStrings[statName] = statText;

            statLayers++;

            os.str(std::string());
        }
    }

    template <class T1, class T2> void addStats(std::string statName1, T1 stat1, std::string statName2, T2 stat2)
    {
        bool dupe = false;
        for(auto mapIterator = gameDebuggerStrings.begin(); mapIterator!= gameDebuggerStrings.end(); mapIterator++)
        {
            if(mapIterator->first == statName1)
            {
                os << statName1 << stat1 <<statName2 << stat2;
                mapIterator->second.setString(os.str());
                os.str(std::string());
                dupe = true;
            }
        }
        if(!dupe)
        {
            os << statName1 << stat1 <<statName2 << stat2;
            sf::Text statText;
            statText.setString(os.str());
            statText.setFont(Data_Desktop::getInstance().font1);
            statText.setCharacterSize(30);
            statText.setColor(sf::Color::Yellow);
            statText.setPosition(10,(statLayers* 50)+10);
            gameDebuggerStrings[statName1] = statText;

            statLayers++;

            os.str(std::string());
        }

    }
    template <class T1, class T2, class T3> void addStats(std::string statName1, T1 stat1, std::string statName2, T2 stat2, std::string statName3, T3 stat3)
    {
        bool dupe = false;
        for(auto mapIterator = gameDebuggerStrings.begin(); mapIterator!= gameDebuggerStrings.end(); mapIterator++)
        {
            if(mapIterator->first == statName1)
            {
                os << statName1 << stat1 <<  statName2 << stat2<< statName3 << stat3;
                mapIterator->second.setString(os.str());
                os.str(std::string());
                dupe = true;
            }
        }
        if(!dupe)
        {
            os << statName1 << stat1 <<  statName2 << stat2<< statName3 << stat3;
            sf::Text statText;
            statText.setString(os.str());
            statText.setFont(Data_Desktop::getInstance().font1);
            statText.setCharacterSize(30);
            statText.setColor(sf::Color::Yellow);
            statText.setPosition(10,(statLayers* 10)+90);
            gameDebuggerStrings[statName1] = statText;

            statLayers++;

            os.str(std::string());
        }
    }

private:
    sf::RenderWindow &window;
    bool overlayVisible;
    int timer;

    sf::Sprite guiSprite;
    sf::Texture guiTexture;
    sf::Sprite hpSprite;
    sf::Texture hpTexture;
    sf::Sprite mpSprite;
    sf::Texture mpTexture;
    sf::Sprite stSprite;
    sf::Texture stTexture;

    sf::Text statisticsTextHP;
    sf::Text statisticsTextMP;
    sf::Text statisticsTextStamina;

    std::ostringstream os;
    std::map <std::string, sf::Text> gameDebuggerStrings;

//Normal GUI
public:
    void addButton (unsigned short buttonID,bool transparent, unsigned short x_b, unsigned short y_b, std::string filePath,
                    std::string text,unsigned short x_t, unsigned short y_t, unsigned short textStyle, unsigned short textSize, sf::Color textColor,
                    sf::Color overlayColor);

    void buttonCheck();
    bool testButton(unsigned short buttonID);
    void changeVisibility(int button, bool transparent);
    void rotateSprite(int button, int degrees);
    sf::Vector2i getButtonCoords(int button);
    void moveSprite(int button, int x, int y);
    void deleteButton(int button);

private:
    std::map<unsigned short, std::tuple<bool, sf::Sprite, sf::Text,  sf::RectangleShape, bool> > buttonMap;


};


#endif // GUIMANAGER_H
