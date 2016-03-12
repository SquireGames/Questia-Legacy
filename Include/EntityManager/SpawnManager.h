#ifndef SPAWNMANAGER_H
#define SPAWNMANAGER_H

#include <SFML/Graphics.hpp>
#include <tuple>

#include "SaveFile.h"
#include "EntityManager/EntityManager.h"

class SpawnManager
{
public:
    SpawnManager(bool game, EntityManager &entityManage);
    ~SpawnManager();

    void checkSpawns();
    void loadSpawnFile(std::string mapName);

private:
    ///Natural spawns
    struct spawnInfo
    {
        std::string entityType;
        int coords_x;
        int coords_y;
        int ID;
        int cooldown;
        int cooldown_current;
        bool dead;
    };
    std::vector <spawnInfo> spawningInfo;

    ///references
    EntityManager &entityManager;
};

#endif // SPAWNMANAGER_H
