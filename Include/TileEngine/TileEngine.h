#ifndef TILEENGINE_H
#define TILEENGINE_H

#include "Data_Desktop.h"
#include "ResourceManager.h"

#include "EntityManager/Entity/Collidable/Entity_Collidable.h"
#include <map>

#include <SFML/Graphics.hpp>

class TileEngine
{
public:
    TileEngine(sf::RenderWindow &_window, ResourceManager& _resourceManager);
    ~TileEngine();
    sf::RenderWindow &window;

    void drawMap(sf::Vector2f coordinates);
    int getMapCollision(sf::Vector2i mapCoordinates,sf::Vector2f playerCoordinates, sf::Vector2f getSideRadius, sf::Vector2f velocity, int (&returnCollision)[4]);
    void loadTiles(float x, float y, int index, int id);
    void loadTiles(float x, float y, int index, int id, int transparency);
    void loadMap(std::string mapName, bool isLimitingTextures);
    std::vector <sf::Vector2i> usedTileVector;

    std::map <int, std::map <int, sf::Sprite > > tileIndex;
    int mapHeight, mapWidth;

    //File locations
    std::string mapDir;
    std::string mapDir2;
    std::string mapTiles;

    // EDITOR ONLY
    void setMapVector (std::vector<std::vector <sf::Vector2i> > MapVector, int layer);
    std::vector<std::vector <sf::Vector2i> > getMapVector(int layer);

private:
    //local functions
    bool tileIsUsed(int index, int id, bool isLimitingTextures);
    void local_loadMap(std::string mapName, int layer, bool isLimitingTextures);
    void updateUsedTileList();

    std::map <int,std::vector <std::vector <sf::Vector2i> > > tileMap;

    ResourceManager& resourceManager;
};

#endif // TILEENGINE_H
