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
    std::stringstream ss;
    std::string naturalSpawnSt;
    ss << "Maps/";
    ss << mapName;
    ss << "/spawn.txt";
    ss >> naturalSpawnSt;
    ss.clear();

    std::ifstream openfile;

    openfile.open(naturalSpawnSt);

    if (!openfile.is_open())
    {
        std::cout<<"DEBUG: Map "<<naturalSpawnSt<<"Spawns failed to load"<<std::endl;
        std::cout<<"DEBUG: Creating spawn file: "<< naturalSpawnSt <<std::endl;
        std::ofstream newFile;
        newFile.open(naturalSpawnSt, std::ofstream::out);
    }

    if(openfile.is_open())
    {
        std::vector<std::tuple<int, sf::Vector2i> > spawns;
        while(!openfile.eof())
        {
            std::string entity;
            std::string x;
            std::string y;
            std::string type;
            std::string subType;


            char line[200];
            for(int y = 0; y!= 200; y++)
            {
                line[y] = ' ';
            }
            openfile.getline(line, 200);

            int character = 0;
            for(char it = '?'; it != ' ';)
            {
                it = line[character];
                ss << line[character];
                character++;
            }
            ss >> entity;
            ss.clear();

            for(char it = '?'; it != ' ';)
            {
                it = line[character];
                ss << line[character];
                character++;
            }

            ss >> x;
            ss.clear();

            for(char it = '?'; it != ' ';)
            {
                it = line[character];
                ss << line[character];
                character++;
            }

            ss >> y;
            ss.clear();

            for(char it = '?'; it != ' ';)
            {
                it = line[character];
                ss << line[character];
                character++;
            }

            ss >> type;
            ss.clear();

            for(char it = '?'; it != ' ' && it != '\0';)
            {
                it = line[character];
                ss << line[character];
                character++;
            }

            ss >> subType;
            ss.clear();

            int entityInt, xInt, yInt;

            if(entity == "chicken")
            {
                entityInt = 1;
            }
            else if(entity == "goblin")
            {
                entityInt = 2;
            }

            else if(entity == "roof")
            {
                entityInt = 0;
                entityManager.createInteravtiveEntity(1, std::atoi(x.c_str()) * 32,std::atoi(y.c_str()) * 32,std::atoi(type.c_str()), std::atoi(subType.c_str()));
            }
            else if(entity == "door")
            {
                entityInt = 0;
                entityManager.createInteravtiveEntity(2, std::atoi(x.c_str()) * 32,std::atoi(y.c_str()) * 32,std::atoi(type.c_str()), std::atoi(subType.c_str()));
            }

            else
            {
                entityInt = 0;
            }

            if(entityInt != 0)
            {
                spawns.push_back(std::make_tuple(entityInt, sf::Vector2i((std::atoi(x.c_str())* 32) +15,(std::atoi(y.c_str())* 32) +15)));
            }
        }
        setNaturalSpawns(spawns);
    }
}

void SpawnManager::setNaturalSpawns(std::vector<std::tuple<int, sf::Vector2i> > naturalSpawns)
{
    for(int x = 0; x < naturalSpawns.size(); x++)
    {
        int entity;
        sf::Vector2i coords;

        std::tie(entity, coords) = naturalSpawns[x];

        spawnInfo info;
        info.entity = entity;
        info.coordinates = coords;
        info.cooldown = 0;
        info.ID = -1;
        info.dead = false;

        spawningInfo.push_back(info);
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
        if(spawningInfo[x].cooldown == 0)
        {
            if(std::abs(coords.x - spawningInfo[x].coordinates.x) < 3000 )
            {
                if(std::abs(coords.y - spawningInfo[x].coordinates.y) < 2000 )
                {
                    switch(spawningInfo[x].entity)
                    {
                    case 1:
                        spawningInfo[x].dead = false;
                        spawningInfo[x].cooldown = 500;
                        spawningInfo[x].ID = entityManager.createEntity(1, sf::Vector2f(spawningInfo[x].coordinates.x,spawningInfo[x].coordinates.y));
                        //std::cout<<"SPAWNMAMAGER -- LIFE  "<< spawningInfo[x].ID  << std::endl;
                        break;
                    case 2:
                        spawningInfo[x].dead = false;
                        spawningInfo[x].cooldown = 500;
                        spawningInfo[x].ID = entityManager.createEntity(2, sf::Vector2f(spawningInfo[x].coordinates.x,spawningInfo[x].coordinates.y));
                        break;
                    default:
                        std::cout<<"No entity: " <<spawningInfo[x].entity<< std::endl;
                        break;
                    }
                }
            }
        }
        else
        {
            if(spawningInfo[x].dead == true)
            {
                spawningInfo[x].cooldown =  spawningInfo[x].cooldown - 1;
            }
        }
    }
}

