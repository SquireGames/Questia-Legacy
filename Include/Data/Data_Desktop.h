#ifndef DATA_DESKTOP_H
#define DATA_DESKTOP_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Utl.h"

class Data_Desktop
{
public:
    static Data_Desktop &getInstance();
    Data_Desktop();
    ~Data_Desktop();

    void setDesktopResolution(sf::Vector2i newRes, sf::Vector2i Position);
    sf::Vector2f getScaledMousePosition(sf::RenderWindow& window);

    int get_FPS();
    void set_FPS(int f);

    void changeFont(std::string fontName);
    sf::Font font1;

    void setMostRecentChar(char c){mostRecentChar = c;}
    char getMostRecentChar(){char temp = mostRecentChar; mostRecentChar = ' ';return temp;}

    void setMouseWheelDelta(int delta){mouseWheelDelta = delta;}
    int  getMouseWheelDelta(){int tempMouseWheelDelta = mouseWheelDelta; mouseWheelDelta = 0; return tempMouseWheelDelta;}

    void setMouseReleased(bool isReleased){m_isMouseReleased = isReleased;}
    bool isMouseReleased()
    {
        bool temp = m_isMouseReleased;
        m_isMouseReleased = false;
        return temp;
    }

    void setMousePressed(bool isPressed){m_isMousePressed = isPressed;}
    bool isMousePressed()
    {
        bool temp = m_isMousePressed;
        m_isMousePressed = false;
        return temp;
    }

private:
    sf::Vector2i desktopResolution;
    sf::Vector2f scaleFactor;

    int FPS;

    char mostRecentChar;
    int mouseWheelDelta;

    bool m_isMouseReleased = false;
    bool m_isMousePressed = false;
};

#endif // DATA_DESKTOP_H
