#include "EntityManager/SpawnManager.h"
#include <sstream>
#include <fstream>

SpawnManager::SpawnManager(bool game, EntityManager &entityManage):
    entityManager(entityManage)
{

}

SpawnManager::~SpawnManager()
{

}

void SpawnManager::loadSpawnFile(std::string mapName)
{
    std::vector <spawnInfo> spawns;

    SaveFile save_spawn;

    std::stringstream sStream;
    sStream << "Maps/" << mapName << "/spawn.txt";
    save_spawn.setFilePath(sStream.str());
    sStream.str(std::string());

    if(save_spawn.readFile())
    {
        std::vector <std::pair <std::string, std::string> > spawnVector = save_spawn.getSaveList();
        for(int it = 0; it != spawnVector.size(); it++)
        {
            std::vector <std::string> entityData = save_spawn.separateString(spawnVector[it].second);

            if(spawnVector[it].first != "entityName")
            {
                spawnInfo entitySpawn;
                entitySpawn.entityType = spawnVector[it].first;
                entitySpawn.coords_x = (save_spawn.asNumber(entityData[0]) * 32) + 15;
                entitySpawn.coords_y = (save_spawn.asNumber(entityData[1]) * 32) + 15;
                entitySpawn.cooldown = save_spawn.asNumber(entityData[2]);
                // Temporary
                entitySpawn.ID = -1;
                entitySpawn.dead = false;
                entitySpawn.cooldown_current = 0;

                std::cout << "Spawn:" << entitySpawn.entityType << "," << entitySpawn.coords_x << "," << entitySpawn.coords_y << std::endl;

                spawns.push_back(entitySpawn);
            }
        }
    }
    else
    {
        save_spawn.saveItem("entityName","tile_x,tile_y,cooldown");
        save_spawn.writeFile();
    }
    spawningInfo = spawns;

    SaveFile save_interactive;

    sStream << "Maps/" << mapName << "/interactive.txt";
    save_interactive.setFilePath(sStream.str());
    sStream.str(std::string());

    if(save_interactive.readFile())
    {
        std::vector <std::pair <std::string, std::string> > spawnVector = save_interactive.getSaveList();
        for(int it = 0; it != spawnVector.size(); it++)
        {
            std::vector <std::string> entityData = save_interactive.separateString(spawnVector[it].second);

            std::string entityType = spawnVector[it].first;
            int coord_x = save_interactive.asNumber(entityData[0]) * 32;
            int coord_y = save_interactive.asNumber(entityData[1]) * 32;

            if(entityType != "objectName")
            {
                //Do stuff
                //entityManager.createInteravtiveEntity(1, std::atoi(x.c_str()) * 32,std::atoi(y.c_str()) * 32,std::atoi(type.c_str()), std::atoi(subType.c_str()));
            }
        }
    }
    else
    {
        save_interactive.saveItem("objectName","tile_x,tile_y");
        save_interactive.writeFile();
    }
}

void SpawnManager::checkSpawns()
{
    std::vector<int> deadID = entityManager.getDeadIDs();
    for(int x = 0; x < deadID.size(); x++)
    {
        for(int y = 0; y < spawningInfo.size(); y++)
        {
            if(spawningInfo[y].ID == deadID[x])
            {
                spawningInfo[y].dead = true;
            }
        }
    }

    sf::Vector2i coords = sf::Vector2i(entityManager.getPlayerCoordinates().x, entityManager.getPlayerCoordinates().y);

    for(int x = 0; x < spawningInfo.size(); x++)
    {
        if(spawningInfo[x].cooldown_current == 0)
        {
            if(std::abs(coords.x - spawningInfo[x].coords_x) < 3000 )
            {
                if(std::abs(coords.y - spawningInfo[x].coords_y) < 2000 )
                {
                    spawningInfo[x].dead = false;
                    spawningInfo[x].cooldown_current = spawningInfo[x].cooldown;
                    spawningInfo[x].ID = entityManager.createEntity(spawningInfo[x].entityType,sf::Vector2f(spawningInfo[x].coords_x,spawningInfo[x].coords_y));
                }
            }
        }
        else
        {
            if(spawningInfo[x].dead == true)
            {
                spawningInfo[x].cooldown_current =  spawningInfo[x].cooldown_current - 1;
            }
        }
    }
}

