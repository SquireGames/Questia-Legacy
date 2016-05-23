#include "EntityManager/SpawnManager.h"
#include <sstream>
#include <fstream>

#include "Utl.h"

SpawnManager::SpawnManager(bool game, EntityManager &entityManage):
    entityManager(entityManage)
{

}

SpawnManager::~SpawnManager()
{

}

void SpawnManager::loadSpawnFile(std::string mapName, SaveFile& save_spawnSave, std::vector <int> savedID, std::map <int, int> newID)
{
    // vector of ID, iterator position
    std::vector <std::pair <int, int>> pastSpawn;

    std::vector<std::pair<std::string, std::string> >& spawnSaveVector = save_spawnSave.getSaveList();
    for(unsigned int it = 0; it != spawnSaveVector.size(); it++)
    {
        pastSpawn.push_back(std::make_pair(utl::asNumber(spawnSaveVector[it].first), it));
    }

    // compare ID's with saved ones, store iterator position in a vector
    std::vector <int> iteratorPosition;
    std::map <int, int> newIDMap; // iterator, newID
    for(unsigned int x = 0; x != savedID.size(); x++)
    {
        for(unsigned int y = 0; y != pastSpawn.size(); y++)
        {
            if(savedID[x] == pastSpawn[y].first)
            {
                iteratorPosition.push_back(pastSpawn[y].second);
                newIDMap[pastSpawn[y].second] = newID[savedID[x]];
            }
        }
    }

    // saveInfo map
    std::map <int, spawnInfo> pastEntities;
    for(unsigned int it = 0; it != iteratorPosition.size(); it++)
    {
        std::vector<std::string> spawnSaveInfo = utl::separateString(spawnSaveVector[iteratorPosition[it]].second, ',');
        spawnInfo entity;
        entity.ID = -1;
        entity.spawnNumber = utl::asNumber(spawnSaveInfo[0]);
        entity.cooldown_current = utl::asNumber(spawnSaveInfo[1]);
        entity.dead = static_cast<bool> (utl::asNumber(spawnSaveInfo[2]));

        pastEntities[entity.spawnNumber] = entity;
    }


    std::vector <spawnInfo> spawns;

    SaveFile save_spawn;

    std::stringstream sStream;
    sStream << "Maps/" << mapName << "/spawn.txt";
    save_spawn.setFilePath(sStream.str());
    sStream.str(std::string());

    if(save_spawn.readFile())
    {
        std::vector <std::pair <std::string, std::string> > spawnVector = save_spawn.getSaveList();
        for(unsigned int it = 0; it != spawnVector.size(); it++)
        {
            std::vector <std::string> entityData = utl::separateString(spawnVector[it].second, ',');

            if(pastEntities.count(it))
            {
                spawnInfo entitySpawn = pastEntities[it];
                entitySpawn.entityType = spawnVector[it].first;
                entitySpawn.coords_x = (utl::asNumber(entityData[0]) * 32) + 15;
                entitySpawn.coords_y = (utl::asNumber(entityData[1]) * 32) + 15;
                entitySpawn.cooldown =  utl::asNumber(entityData[2]);
                entitySpawn.spawnNumber = it;
                entitySpawn.ID = newIDMap[it];

                std::cout << "Spawn:" << entitySpawn.entityType << "," << entitySpawn.coords_x << "," << entitySpawn.coords_y << std::endl;

                spawns.push_back(entitySpawn);
            }
            else
            {
                spawnInfo entitySpawn;
                entitySpawn.entityType = spawnVector[it].first;
                entitySpawn.coords_x = (utl::asNumber(entityData[0]) * 32) + 15;
                entitySpawn.coords_y = (utl::asNumber(entityData[1]) * 32) + 15;
                entitySpawn.cooldown =  utl::asNumber(entityData[2]);
                entitySpawn.spawnNumber = it;
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
        for(unsigned int it = 0; it != spawnVector.size(); it++)
        {
            std::vector <std::string> entityData = utl::separateString(spawnVector[it].second, ',');

            std::string entityType = spawnVector[it].first;
            int coord_x = utl::asNumber(entityData[0]) * 32;
            int coord_y = utl::asNumber(entityData[1]) * 32;

            if(entityType != "objectName")
            {
                entityManager.createInteravtiveEntity(entityType, coord_x,coord_y,1, 1);
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
    for(unsigned int x = 0; x < deadID.size(); x++)
    {
        for(unsigned int y = 0; y < spawningInfo.size(); y++)
        {
            if(spawningInfo[y].ID == deadID[x])
            {
                spawningInfo[y].dead = true;
            }
        }
    }

    sf::Vector2i coords = sf::Vector2i(entityManager.getPlayerCoordinates().x, entityManager.getPlayerCoordinates().y);

    for(unsigned int x = 0; x < spawningInfo.size(); x++)
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
                if(std::abs(coords.x - spawningInfo[x].coords_x) > 500 || std::abs(coords.y - spawningInfo[x].coords_y) > 500)
                {
                    spawningInfo[x].cooldown_current =  spawningInfo[x].cooldown_current - 1;
                }
            }
        }
    }
}

void SpawnManager::saveSpawns(SaveFile& save_spawn)
{
    for(unsigned int it = 0; it < spawningInfo.size(); it++)
    {
        std::vector <std::string> spawnSave;

        spawnSave.push_back(utl::asString(spawningInfo[it].spawnNumber));
        spawnSave.push_back(utl::asString(spawningInfo[it].cooldown_current));
        spawnSave.push_back(utl::asString(spawningInfo[it].dead));

        std::string spawnSaveInfo = utl::conjoinString(spawnSave, ',');

        save_spawn.addItem(utl::asString(spawningInfo[it].ID), spawnSaveInfo);
        save_spawn.writeFile();
    }
}
