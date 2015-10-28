#include "ResourceManager.h"
#include <iostream>

ResourceManager::ResourceManager():
    textureMap()
    , firstTime(true)
{

}

ResourceManager::~ResourceManager()
{
    textureMap.clear();
}

sf::Texture& ResourceManager::getTexture(std::string filename)
{
    if(firstTime)
    {
        firstTime = false;
        textureMap.clear();
    }
    //auto is cool
    for(auto it = textureMap.begin(); it != textureMap.end(); it++)
    {
        if(filename == it->first)
        {
            return it->second;
        }
    }

    // if not loaded
    sf::Texture tex;
    if(tex.loadFromFile(filename))
    {
        textureMap.insert(std::make_pair(filename, tex));
        std::cout<< "DEBUG: Texture '" << filename << "' was loaded"<< std::endl;
        return textureMap[filename];
    }

    std::cout<< "DEBUG: Texture '" << filename << "' was not found"<< std::endl;
    textureMap[filename] = tex;
    return textureMap[filename];
}
