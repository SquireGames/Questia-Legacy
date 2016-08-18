#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(ResourceManager& _resourceManager):
    resourceManager(_resourceManager)
{

}

TextureAtlas::~TextureAtlas()
{
    //dtor
}

bool TextureAtlas::addTexture(std::string fileLocation, std::string name)
{
    //deleted after, used for getting texture data
    sf::Texture tempTexture;
    tempTexture.loadFromFile(fileLocation);

    //check if it will fit horizontally, +1 for space between textures
    if(maxWidth + tempTexture.getSize().x + 1 < maxTextureSize)
    {
        //add width
        maxWidth += tempTexture.getSize().x + 1;
        //check height
        if(tempTexture.getSize().y > maxHeight)
        {
            maxHeight = tempTexture.getSize().y;
        }

        //add to vector for saving
        textureList.push_back(std::make_pair(name, &resourceManager.getTexture(fileLocation)));
        textureLocations.push_back(fileLocation);
        return true;
    }
    return false;
}

TextureAtlasData TextureAtlas::compileTextures(std::string textureName)
{
    TextureAtlasData textureData(&resourceManager.getBlankTexture(textureName));
    textureData.texture->create(maxWidth, maxHeight);

    //used to combine all textures
    sf::RenderTexture resultTexture;
    resultTexture.create(maxWidth, maxHeight);

    //tracks how far on the x axis it transversed
    unsigned int currentWidth = 0;

    //iterate through textures
    for(unsigned int it = 0; it != textureList.size(); it++)
    {
        //get data
        std::string& name    = textureList[it].first;
        sf::Texture* texture = textureList[it].second;

        //storing dimensions of new texture
        utl::IntRect dimensions = utl::IntRect(currentWidth, 0, texture->getSize().x, texture->getSize().y);
        textureData.textureCoords[name] = dimensions;
        //+1 for space in between
        currentWidth += texture->getSize().x + 1;

        //create sprite from texture
        sf::Sprite sprite;
        sprite.setTexture(*texture);
        sprite.setPosition(dimensions.x, dimensions.y);

        //draw sprite onto texture
        resultTexture.draw(sprite);
    }
    //finalize texture
    resultTexture.display();

    *textureData.texture = resultTexture.getTexture();
    return textureData;
}
