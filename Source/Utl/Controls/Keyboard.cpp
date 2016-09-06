#include "Keyboard.h"

sf::Keyboard::Key ctr::getKey(const char& key)
{
    if(ctr::KeyboardBinds.count(key))
    {
        return ctr::KeyboardBinds.at(key);
    }
    return sf::Keyboard::Unknown;
}

char getCharacter(const sf::Keyboard::Key& key)
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
