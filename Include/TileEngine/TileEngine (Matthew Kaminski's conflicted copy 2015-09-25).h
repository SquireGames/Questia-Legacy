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
    TileEngine(ResourceManager& _resourceManager);
    ~TileEngine();

    void drawMap(sf::RenderWindow &window, sf::Vector2f coordinates);
    int getMapCollision(sf::Vector2i mapCoordinates,sf::Vector2f playerCoordinates, sf::Vector2f getSideRadius, sf::Vector2f velocity, int (&returnCollision)[4]);
    void loadTiles(int x, int y, int index, int id, sf::RenderWindow &window);
    void loadMap(std::string mapName);

    std::map <int, std::map <int, sf::Sprite > > tileIndex;
    int mapHeight, mapWidth;

    //Map layers
    std::string mapDir;
    std::string mapDir2;

    // EDITOR ONLY
    void setMapVector (std::vector<std::vector <sf::Vector2i> > MapVector, int layer);
    std::vector<std::vector <sf::Vector2i> > getMapVector(int layer);

private:
    bool tileIsUsed(int index, int id);
    void local_loadMap(std::string mapName, int layer);
    std::map <int,std::vector <std::vector <sf::Vector2i> > > tileMap;

    ResourceManager& resourceManager;
};

#endif // TILEENGINE_H
