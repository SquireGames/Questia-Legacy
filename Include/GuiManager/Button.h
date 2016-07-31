#ifndef BUTTON_H
#define BUTTON_H

#include <tuple>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

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
                                 isVisible,
                                 isTemplate,
                                 coords_group
                                };
enum ButtonAtr {Sprite,
                Percent,
                Hover,
                Text
               };

enum class ButtonAtrCharacteristic {sprite,
                                    texture,
                                    flip,
                                    coords,
                                    color,
                                    charSize,
                                    text,
                                    transparency
                                   };
};


//{ class attributeTypes
struct RegularSprite
{
    sf::Sprite normalSprite;
    std::pair <int, int> position;

    bool isChanged;
};

struct ButtonText
{
    sf::Text text;
    std::pair <int, int> position;

    bool isChanged;
};

struct OverlaySprite
{
    sf::RectangleShape rectOverlay;
    //sf::Sprite spriteOverlay;

    std::pair <int, int> position;

    bool isChanged;
    bool isHoveredOver;
    //enum OverlayMode {rect, spr};
    //OverlayMode overlayMode;
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
    Button(sf::RenderWindow& _window, ResourceManager &_resourceManager, sf::Font& _buttonFont, bool _isTemplate, int _buttonID);
    ~Button();

    Button(const Button& oldButton, int _buttonID);
    void copyToThisButton(Button& newButton, const Button& oldButton);

    sf::RenderWindow& window;
    ResourceManager& resourceManager;
    sf::Font& buttonFont;

    // variables
    std::pair <int, int> buttonPosition;
    std::pair <int, int> buttonBounds;
    bool isCoordsChanged;
    int scrollAmount_x;
    int scrollAmount_y;
    bool isVisible;
    bool isTemplate;

    //used by editor
    int layer = 1;
    int buttonID;
    std::string buttonName = "none";

    // holds attributes
    std::map<std::string, RegularSprite*> heldSprites;
    std::map<std::string, ButtonText*> heldText;
    std::map<std::string, OverlaySprite*> heldOverlaySprites;
    std::map<std::string, PercentSprite*> heldPercentSprites;

    void setButton(gui::ButtonCharacteristic buttonChar, std::string value);
    void setButton(gui::ButtonCharacteristic buttonChar, const char* value);
    void setButton(gui::ButtonCharacteristic buttonChar, bool value);
    void setButton(gui::ButtonCharacteristic buttonChar, int value);
    void setButton(gui::ButtonCharacteristic buttonChar, std::pair <int, int> value);

    void setButtonAtr(std::string atrName, gui::ButtonAtrCharacteristic atrChar, std::string value);
    void setButtonAtr(std::string atrName, gui::ButtonAtrCharacteristic atrChar, std::pair<int, int> value);
    void setButtonAtr(std::string atrName, gui::ButtonAtrCharacteristic atrChar, sf::Color color);
    void setButtonAtr(std::string atrName, gui::ButtonAtrCharacteristic atrChar, int value);
    void setButtonAtr(std::string atrName, gui::ButtonAtrCharacteristic atrChar, char value);

    void addButtonAtr (std::string atrName, gui::ButtonAtr buttonAtr);

    void update(std::pair <int, int> mouseCoords);
    void drawButton();
};



#endif // BUTTON_H
