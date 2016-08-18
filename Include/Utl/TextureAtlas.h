#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include <SFML/Graphics.hpp>
#include <map>
#include <tuple>

#include "ResourceManager.h"
#include "Utl.h"

struct TextureAtlasData
{
    //ctor
    TextureAtlasData(sf::Texture* _texture) : texture(_texture) {}

    std::map<std::string, utl::IntRect> textureCoords;
    sf::Texture* texture = nullptr;
};

//1d texture atlas, only horizontal
class TextureAtlas
{
public:
    TextureAtlas(ResourceManager& _resourceManager);
    ~TextureAtlas();

    //returns if there is space, otherwise make another one
    bool addTexture(std::string fileLocation, std::string textureName);

    //returns the textures and coords of texture bounds
    TextureAtlasData compileTextures(std::string textureName);

    //clear everything
    void reset()
    {
        maxWidth = 0;
        maxHeight = 0;
        textureList.clear();
        textureLocations.clear();
    }

private:
    ResourceManager& resourceManager;

    //Depending on graphics card, game minimum being 512 x 512
    int maxTextureSize = sf::Texture::getMaximumSize();
    //used for checking layer space left
    int maxWidth = 0;
    int maxHeight = 0;

    //stores all textures
    std::vector<std::pair <std::string, sf::Texture*> > textureList;
    //stores texture locations for deleting after copying
    std::vector<std::string> textureLocations;

    sf::Texture textureResult;
};

#endif // TEXTUREATLAS_H
