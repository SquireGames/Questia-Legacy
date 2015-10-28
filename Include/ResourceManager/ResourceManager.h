#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();
    sf::Texture& getTexture(std::string filename);

private:
    std::map <std::string, sf::Texture> textureMap;
    bool firstTime;
};

#endif // RESOURCEMANAGER_H
