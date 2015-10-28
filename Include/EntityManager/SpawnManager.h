#ifndef SPAWNMANAGER_H
#define SPAWNMANAGER_H

#include <SFML/Graphics.hpp>
#include <tuple>

#include "EntityManager/EntityManager.h"

class SpawnManager
{
public:
    SpawnManager(bool game, EntityManager &entityManage);
    ~SpawnManager();

    void setNaturalSpawns(std::vector<std::tuple<int, sf::Vector2i> > naturalSpawns);
    void checkSpawns();
    void loadSpawnFile(std::string mapName);

private:
    ///Natural spawns
    struct spawnInfo
    {
        sf::Vector2i coordinates;
        int entity;
        int ID;
        int cooldown;
        bool dead;
    };
    std::vector<spawnInfo> spawningInfo;

    ///references
    EntityManager &entityManager;
};

#endif // SPAWNMANAGER_H
