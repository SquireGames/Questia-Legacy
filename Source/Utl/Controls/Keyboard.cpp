#include "Keyboard.h"

sf::Keyboard::Key ctr::getKey(const char& key)
{
    if(ctr::KeyboardBinds.count(key))
    {
        return ctr::KeyboardBinds.at(key);
    }
    return sf::Keyboard::Unknown;
}

char ctr::getCharacter(const sf::Keyboard::Key& key)
{
    for(auto& it : ctr::KeyboardBinds)
    {
        if(it.second == key)
        {
            return it.first;
        }
    }
    return 0;
}

std::string ctr::getKeyName(const char& key)
{
    if(key < 31)
    {
        switch (key)
        {
        case 1:
            return "Backspace";
            break;
        case 2:
            return "Tab";
            break;
        case 3:
            return "Enter";
            break;
        case 4:
            return "LShift";
            break;
        case 5:
            return "RShift";
            break;
        case 6:
            return "LControl";
            break;
        case 7:
            return "LAlt";
            break;
        case 8:
            return "RAlt";
            break;
        case 9:
            return "RControl";
            break;
        case 10:
            return "Up";
            break;
        case 11:
            return "Down";
            break;
        case 12:
            return "Left";
            break;
        case 13:
            return "Right";
            break;
        case 14:
            return "Insert";
            break;
        case 15:
            return "Home";
            break;
        case 16:
            return "Delete";
            break;
        case 17:
            return "End";
            break;
        case 18:
            return "PageUp";
            break;
        case 19:
            return "PageDown";
            break;
        }
    }
    return std::string(1,key);
}
