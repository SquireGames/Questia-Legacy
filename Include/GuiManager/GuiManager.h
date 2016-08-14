#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <tuple>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <map>


#include "StateManager/State.h"
#include "ResourceManager.h"
#include "Data_Desktop.h"

#include "GuiManager/Button.h"


class GuiManagerNew
{
public:
    GuiManagerNew(sf::RenderWindow &_window, ResourceManager &_resourceManager);
    ~GuiManagerNew();

    void createButton(std::string buttonName);
    void createButton(std::string buttonName, int layer);
    void createButton(std::string copyName, std::string originalName);
    void createButtonTemplate(std::string buttonName);
    void createButtonTemplate(std::string buttonName, int layer);
    void createButtonTemplate(std::string copyName, std::string originalName);
    void createButtonAtr(std::string atrName, gui::ButtonAtr buttonAtr);
    void createButtonAtr(std::string buttonName, std::string atrName, gui::ButtonAtr buttonAtr);
    void setButtonLayer(std::string buttonName, int layer);
    void setButtonLayer(int layer);

    void createGroup(std::string groupName);
    void createGroupTemplate(std::string groupName);
    void createGroupFromTemplate(std::string groupName, std::string templateName);
    void addToGroup (std::string groupName, std::string entryName);
    void addToGroup (std::string entryName);
    std::string getGroupEntry(std::string groupName, std::string buttonName);

    void createList(std::string listName);
    void setListSpacing(std::string listName, int spacing);
    void setListSpacing(int spacing);
    void setListTemplate(std::string listName, std::string groupTemplate);
    void setListTemplate(std::string groupTemplate);
    void setListPosition(std::string listName, std::pair<int, int> position);
    void setListPosition(std::pair<int, int> position);
    std::string createListEntry(std::string listName);
    std::string createListEntry();


    bool isClicked(std::string buttonName);
    void drawButtons();
    void deleteButton(std::string buttonName);
    void setMousePosition(std::pair <float, float> _mouseCoords);
    void setFont(sf::Font _buttonFont);

    template <class T>
    void setButton(std::string buttonName, gui::ButtonCharacteristic buttonChar, T value)
    {
        buttonMap[buttonName]->setButton(buttonChar, value);
    }
    template <class T>
    void setButton(gui::ButtonCharacteristic buttonChar, T value)
    {
        buttonMap[currentButtonEdit]->setButton(buttonChar, value);
    }
    template <class T>
    void setButtonAtr(std::string buttonName, std::string atrName, gui::ButtonAtrCharacteristic atrChar, T value)
    {
        buttonMap[buttonName]->setButtonAtr(atrName, atrChar, value);
    }
    template <class T>
    void setButtonAtr(gui::ButtonAtrCharacteristic atrChar, T value)
    {
        buttonMap[currentButtonEdit]->setButtonAtr(currentButtonAtrEdit, atrChar, value);
    }


    template <class T>
    void setGroupAtr(std::string groupName, gui::ButtonCharacteristic buttonChar, T value)
    {
        if(buttonChar == gui::ButtonCharacteristic::coords)
        {
            buttonChar = gui::ButtonCharacteristic::coords_group;
        }
        if(groupMap.count(groupName))
        {
            const std::vector <std::string>& buttonVec = groupMap[groupName];
            for(unsigned int it = 0; it != buttonVec.size(); it++)
            {
                buttonMap[buttonVec[it]]->setButton(buttonChar, value);
            }
        }
    }
    template <class T>
    void setGroupAtr(gui::ButtonCharacteristic buttonChar, T value)
    {
        if(buttonChar == gui::ButtonCharacteristic::coords)
        {
            buttonChar = gui::ButtonCharacteristic::coords_group;
        }
        if(groupMap.count(currentGroupEdit))
        {
            const std::vector <std::string>& buttonVec = groupMap[currentGroupEdit];
            for(unsigned int it = 0; it != buttonVec.size(); it++)
            {
                buttonMap[buttonVec[it]]->setButton(buttonChar, value);
            }
        }
    }
    template <class T>
    void setListAtr(std::string listName, gui::ButtonCharacteristic buttonChar, T value)
    {
        for(const std::string& groupIt : listMap[listName].second)
        {
            setGroupAtr(groupIt, buttonChar, value);
        }
    }
    template <class T>
    void setListAtr(gui::ButtonCharacteristic buttonChar, T value)
    {
        for(const std::string& groupIt : listMap[currentListEdit].second)
        {
            setGroupAtr(groupIt, buttonChar, value);
        }
    }

private:
    sf::RenderWindow& window;
    ResourceManager &resourceManager;

    std::string currentButtonEdit;
    std::string currentButtonAtrEdit;
    std::string currentGroupEdit;
    std::string currentListEdit;

    std::pair <float, float> mouseCoords;

    std::map <std::string, Button*> buttonMap;
    std::list <Button*> buttonDrawList;
    void placeInDrawList(Button* button);

    std::map <std::string, std::vector <std::string> > groupMap;
    std::map <std::string, std::vector <std::string> > groupTemplateMap;

    std::map <std::string, std::pair <std::pair <std::string, std::pair <std::pair <int, int>, int>>,std::vector <std::string > > > listMap;

    sf::Font buttonFont;
    int buttonCount = 0;
};





















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

    template <class T>
    void addStats(std::string statName, T stat)
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

    template <class T1, class T2>
    void addStats(std::string statName1, T1 stat1, std::string statName2, T2 stat2)
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
    template <class T1, class T2, class T3>
    void addStats(std::string statName1, T1 stat1, std::string statName2, T2 stat2, std::string statName3, T3 stat3)
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
