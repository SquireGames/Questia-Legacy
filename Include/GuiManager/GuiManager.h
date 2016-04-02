#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <tuple>
#include <SFML/Graphics.hpp>

#include <sstream>
#include <iostream>
#include <vector>
#include <map>

#include "StateManager/State.h"
#include "ResourceManager.h"
#include "Data_Desktop.h"


namespace gui
{
enum Direction {none = 0, up = 1, right = 2, down = 3, left = 4};

enum class ButtonCharacteristic {coords,
                                 bounds,
                                 scroll_x, scroll_y,
                                 addToScroll_x, addToScroll_y,
                                 isVisible
                                };
enum ButtonAtr {Sprite,
                Percent,
                Hover,
                Text
               };

enum class ButtonAtrCharacteristic {sprite,
                                    visibilityPercentage,
                                    resLocation,
                                    coords,
                                    color
                                   };
};

//{ class attributeTypes
struct RegularSprite
{
    sf::Sprite normalSprite;
    std::pair <int, int> position;

    bool isChanged;
};

struct Text
{
    sf::Text text;
    std::pair <int, int> position;

    bool isChanged;
};

struct OverlaySprite
{
    sf::Sprite normalSprite;
    sf::RectangleShape rectOverlay;

    float overlayPercentage;
    gui::Direction directionOfOverlay;

    std::pair <int, int> position;

    bool isChanged;
};

struct PercentSprite
{
    sf::Sprite normalSprite;

    float spritePercentage;
    gui::Direction directionOfGap;

    std::pair <int, int> position;

    bool isChanged;
};
//}


struct Button
{
    //{ Button() + copy constructors
    Button(sf::RenderWindow& _window, ResourceManager &_resourceManager, bool _isTemplate):
        window(_window)
        , resourceManager(_resourceManager)
        , scrollAmount_x (0)
        , scrollAmount_y (0)
        , buttonPosition (std::make_pair(0,0))
        , buttonBounds (std::make_pair(0,0))
        , isCoordsChanged(true)
        , isVisible(true)
        , isTemplate(_isTemplate)
    {}

    // copy constructor
    Button(const Button& oldButton): // const to make sure there are no changes to the original
        window(oldButton.window)
        , resourceManager(oldButton.resourceManager)
        , scrollAmount_x (0)
        , scrollAmount_y (0)
        , buttonPosition (std::make_pair(0,0))
        , buttonBounds (oldButton.buttonBounds)
        , isCoordsChanged(true)
        , isVisible(oldButton.isVisible)
        , isTemplate(false)
    {
        copyToThisButton(*this, oldButton);

        if(oldButton.isTemplate)
        {
            isVisible = true;
        }
    }

    // copies attributes
    void copyToThisButton(Button& newButton, const Button& oldButton)
    {
        for(std::map<std::string, RegularSprite*>::const_iterator it = oldButton.heldSprites.begin(); it != oldButton.heldSprites.end(); ++it)
        {
            newButton.addButtonAtr(it->first, gui::ButtonAtr::Sprite);
            newButton.heldSprites[it->first]->normalSprite = oldButton.heldSprites.at(it->first)->normalSprite;
            newButton.heldSprites[it->first]->position =     oldButton.heldSprites.at(it->first)->position;
            newButton.heldSprites[it->first]->isChanged =    oldButton.heldSprites.at(it->first)->isChanged;
        }
        for(std::map<std::string, Text*>::const_iterator it = oldButton.heldText.begin(); it != oldButton.heldText.end(); ++it)
        {

        }
        for(std::map<std::string, OverlaySprite*>::const_iterator it = oldButton.heldOverlaySprites.begin(); it != oldButton.heldOverlaySprites.end(); ++it)
        {

        }
        for(std::map<std::string, PercentSprite*>::const_iterator it = oldButton.heldPercentSprites.begin(); it != oldButton.heldPercentSprites.end(); ++it)
        {

        }
    }


    //}

    // deletes attributes
    ~Button()
    {
        for(std::map<std::string, RegularSprite*>::iterator it = heldSprites.begin(); it != heldSprites.end(); ++it)
        {
            delete it->second;
        }
        for(std::map<std::string, Text*>::iterator it = heldText.begin(); it != heldText.end(); ++it)
        {
            delete it->second;
        }
        for(std::map<std::string, OverlaySprite*>::iterator it = heldOverlaySprites.begin(); it != heldOverlaySprites.end(); ++it)
        {
            delete it->second;
        }
        for(std::map<std::string, PercentSprite*>::iterator it = heldPercentSprites.begin(); it != heldPercentSprites.end(); ++it)
        {
            delete it->second;
        }
    }

    // required
    sf::RenderWindow& window;
    ResourceManager& resourceManager;

    // variables
    std::pair <int, int> buttonPosition;
    std::pair <int, int> buttonBounds;
    bool isCoordsChanged;
    int scrollAmount_x;
    int scrollAmount_y;
    bool isVisible;
    bool isTemplate;

    // holds attributes
    std::map<std::string, RegularSprite*> heldSprites;
    std::map<std::string, Text*> heldText;
    std::map<std::string, OverlaySprite*> heldOverlaySprites;
    std::map<std::string, PercentSprite*> heldPercentSprites;

    //{ setButton()
    void setButton(gui::ButtonCharacteristic buttonChar, std::string value)
    {
        switch (buttonChar)
        {
        case gui::ButtonCharacteristic::bounds:
        {
            if(heldSprites.count(value))
            {
                buttonBounds = std::make_pair(heldSprites[value]->normalSprite.getLocalBounds().width, heldSprites[value]->normalSprite.getLocalBounds().height);
            }
        }
        break;
        default:
            break;
        }
    }
    void setButton(gui::ButtonCharacteristic buttonChar, const char* value)
    {
        std::string atrName = static_cast <std::string> (value);
        switch (buttonChar)
        {
        case gui::ButtonCharacteristic::bounds:
        {
            if(heldSprites.count(value))
            {
                buttonBounds = std::make_pair(heldSprites[value]->normalSprite.getLocalBounds().width, heldSprites[value]->normalSprite.getLocalBounds().height);
            }
        }
        break;
        default:
            break;
        }
    }
    void setButton(gui::ButtonCharacteristic buttonChar, bool value)
    {
        switch (buttonChar)
        {
        case gui::ButtonCharacteristic::isVisible:
            isVisible = value;
            break;
        default:
            break;
        }
    }
    void setButton(gui::ButtonCharacteristic buttonChar, int value)
    {
        switch (buttonChar)
        {
        case gui::ButtonCharacteristic::addToScroll_x:
            scrollAmount_x += value;
            break;
        case gui::ButtonCharacteristic::addToScroll_y:
            scrollAmount_y += value;
            break;
        case gui::ButtonCharacteristic::scroll_x:
            scrollAmount_x = value;
            break;
        case gui::ButtonCharacteristic::scroll_y:
            scrollAmount_y = value;
            break;
        default:
            break;
        }
    }
    void setButton(gui::ButtonCharacteristic buttonChar, std::pair <int, int> value)
    {
        switch (buttonChar)
        {
        case gui::ButtonCharacteristic::coords:
            isCoordsChanged = true;
            buttonPosition = value;
            break;
        case gui::ButtonCharacteristic::bounds:
            buttonBounds = value;
            break;
        default:
            break;
        }
    }
    //}

    //{ setButtonAtr()
    void setButtonAtr(std::string atrName, gui::ButtonAtrCharacteristic atrChar, std::string value)
    {
        if(heldText.count(atrName))
        {
            switch (atrChar)
            {
            default:
                break;
            }
        }
        else if(heldSprites.count(atrName))
        {
            switch (atrChar)
            {
            case gui::ButtonAtrCharacteristic::resLocation:
                heldSprites[atrName]->normalSprite.setTexture(resourceManager.getTexture(value));
                break;
            default:
                break;
            }

        }
        else if(heldOverlaySprites.count(atrName))
        {
            switch (atrChar)
            {
            default:
                break;
            }

        }
        else if(heldPercentSprites.count(atrName))
        {
            switch (atrChar)
            {
            default:
                break;
            }
        }
    }
    void setButtonAtr(std::string atrName, gui::ButtonAtrCharacteristic atrChar, std::pair<int, int> value)
    {
        if(heldText.count(atrName))
        {
            switch (atrChar)
            {
            default:
                break;
            }
        }
        else if(heldSprites.count(atrName))
        {
            switch (atrChar)
            {
            case gui::ButtonAtrCharacteristic::coords:
                heldSprites[atrName]->position = value;
                break;

            default:
                break;
            }

        }
        else if(heldOverlaySprites.count(atrName))
        {
            switch (atrChar)
            {
            default:
                break;
            }

        }
        else if(heldPercentSprites.count(atrName))
        {
            switch (atrChar)
            {
            default:
                break;
            }
        }
    }

    //}

    void addButtonAtr (std::string atrName, gui::ButtonAtr buttonAtr)
    {
        switch(buttonAtr)
        {
        case gui::ButtonAtr::Sprite:
        {
            RegularSprite* newSprite = new RegularSprite;
            newSprite->isChanged = true;
            newSprite->position = std::make_pair(0,0);
            newSprite->normalSprite.setPosition(newSprite->position.first  + buttonPosition.first,
                                                newSprite->position.second + buttonPosition.second);

            heldSprites[atrName] = newSprite;
        }
        break;
        case gui::ButtonAtr::Text:
        {

        }
        break;
        case gui::ButtonAtr::Hover:
        {

        }
        break;
        case gui::ButtonAtr::Percent:
        {

        }
        break;
        default:
        {

        }
        break;
        }
    }

    void drawButton()
    {
        if(isVisible)
        {
            for(std::map<std::string, RegularSprite*>::iterator it = heldSprites.begin(); it != heldSprites.end(); it++)
            {
                if(it->second->isChanged || isCoordsChanged)
                {
                    it->second->normalSprite.setPosition(buttonPosition.first  + it->second->position.first  + scrollAmount_x,
                                                         buttonPosition.second + it->second->position.second + scrollAmount_y);
                    it->second->isChanged = false;
                    window.draw(it->second->normalSprite);
                }
                else
                {
                    window.draw(it->second->normalSprite);
                }
            }
            isCoordsChanged = false;
        }
    }
};

class GuiManagerNew
{
public:
    GuiManagerNew(sf::RenderWindow &_window, ResourceManager &_resourceManager):
        window(_window)
        , resourceManager(_resourceManager)
        , currentButtonEdit ("NOBUTTON")
        , currentButtonAtrEdit ("NOBUTTONATR")
    {

    }
    ~GuiManagerNew()
    {
        for(std::map<std::string, Button*>::iterator it = buttonMap.begin(); it != buttonMap.end(); ++it)
        {
            delete it->second;
        }
    }

    //{ createButton(), createButtonTemplate()
    void createButtonTemplate(std::string buttonName)
    {
        if(!buttonMap.count(buttonName))
        {
            Button* newButton = new Button(window, resourceManager, true);
            buttonMap[buttonName] = newButton;
            buttonMap[buttonName]->setButton(gui::ButtonCharacteristic::isVisible, false);

            currentButtonEdit = buttonName;
        }
    }

    void createButton(std::string buttonName)
    {
        if(!buttonMap.count(buttonName))
        {
            Button* newButton = new Button(window, resourceManager, false);
            buttonMap[buttonName] = newButton;

            currentButtonEdit = buttonName;
        }
    }

    void createButton(std::string copyName, std::string originalName)
    {
        if(buttonMap.count(originalName))
        {
            if(!buttonMap.count(copyName))
            {
                Button* newButton = new Button(*buttonMap[originalName]);
                buttonMap[copyName] = newButton;

                currentButtonEdit = copyName;
            }
        }
    }
    //}

    void createButtonAtr(std::string buttonName, std::string atrName, gui::ButtonAtr buttonAtr)
    {
        buttonMap[buttonName]->addButtonAtr(atrName, buttonAtr);
        currentButtonEdit = buttonName;
        currentButtonAtrEdit = atrName;
    }


    //{ setButton()
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
    //}

    //{ setButtonAtr()
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
    //}



    void createGroup(std::string groupName)
    {

    }

    void createList(std::string listName)
    {

    }

    bool isClicked(std::string buttonName)
    {
        return false;
    }

    void drawButtons()
    {
        for(std::map<std::string, Button*>::iterator it = buttonMap.begin(); it != buttonMap.end(); ++it)
        {
            it->second->drawButton();
        }
    }

    void deleteButton(std::string buttonName)
    {
        delete buttonMap[buttonName];
        buttonMap.erase(buttonName);
    }

private:
    std::string currentButtonEdit;
    std::string currentButtonAtrEdit;

    std::map <std::string, Button*> buttonMap;

    sf::RenderWindow& window;
    ResourceManager &resourceManager;
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
