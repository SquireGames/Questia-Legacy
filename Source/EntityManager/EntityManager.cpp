#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

#include "EntityManager/EntityManager.h"

#include "Entity_Chicken.h"
#include "EntityManager/Entity/Collidable/Living/Hostile/Hostile_Goblin.h"

#include "EntityManager/Entity/Collidable/Attack/Melee/Attack_Slash.h"
#include "EntityManager/Entity/Collidable/Attack/Ranged/Attack_Arrow.h"
#include "EntityManager/Entity/Collidable/Living/Player/Entity_Playable.h"

#include "EntityManager/Entity/Collidable/Living/Player/Entity_Player.h"

#include "EntityManager/Entity/Collidable/Interactable/Interact_Roof.h"
#include "EntityManager/Entity/Collidable/Interactable/Interact_Door.h"

#include "EntityManager/Entity.h"
#include "EntityManager/Entity/Collidable/Entity_Collidable.h"
#include "ResourceManager.h"

#include "Utl.h"

EntityManager::EntityManager(ManagerType _type, sf::RenderWindow &mWindow, ResourceManager &res, LightManager& _lightManager):
    window (mWindow)
    , spawnTick(0)
    , entityNumber(0)
    , timer1(25)
    , resourceManager(res)
    , lightManager(_lightManager)
    , playerID(-1)
    , type(_type)
    , last_entityID(0)
    , last_playerID(0)
{
    std::cout<<"DEBUG: Entity Manager Initialized"<<std::endl;
}

EntityManager::~EntityManager()
{
    for(int x = 0; x < entityStack.size(); x++)
    {
        delete entityStack[x];
    }
    std::cout<<"DEBUG: Destroyed Entity Manager"<<std::endl;
}

int EntityManager::getIDNumber(EntityType entityType)
{
    int IDNumber;

    switch (type)
    {
    case ManagerType::singleplayer:
    {
        std::vector<int> entityList;
        for(int x = 0; x < entityStack.size(); x++)
        {
            entityList.push_back(entityStack[x]->returnID());
        }

        std::sort(entityList.begin(),entityList.end());
        if(entityList.size() > 0)
        {
            if(entityStack.size() != entityList[entityList.size()-1]+1)
            {
                if(entityStack.size()>1)
                {
                    for(int x = 0; x < entityList.size(); x++)
                    {
                        if (entityList[x]+1 != entityList[x+1])
                        {
                            IDNumber = entityList[x]+1;
                            x = 99999;
                        }
                    }
                }
                else
                {
                    entityNumber = entityList[entityList.size()-1]+1;
                    IDNumber = entityNumber;
                }
            }
            else
            {
                entityNumber =  entityList[entityList.size()-1]+1;
                IDNumber = entityNumber;
            }
        }
        else
        {
            entityNumber =  0;
            IDNumber = entityNumber;
        }
        return IDNumber;
    }
    break;

    case ManagerType::multiplayer:
    {

    }
    break;

    case ManagerType::server:
    {
        switch (entityType)
        {
        case EntityType::entity:
            last_entityID++;
            return last_entityID;
            break;
        case EntityType::player:
            last_playerID--;
            return last_playerID;
            break;
        default:
            break;
        }
    }
    break;
    default:
    {

    }
    break;
    }
}

int EntityManager::createEntity(int entity, sf::Vector2f coordinates)
{
    spawnTick = 35;

    int IDNumber = getIDNumber(EntityType::entity);

    switch (entity)
    {
    case 1:
    {
        Entity_Chicken* entity= new Entity_Chicken(resourceManager, *this, coordinates, IDNumber, "chicken");

        std::cout<<"DEBUG: Created entity: " << "Chicken     ID: " << IDNumber <<std::endl;


        entityStack.push_back(entity);
        entityCollidableStack.push_back(entity);
        entityLivingStack.push_back(entity);
        break;
    }
    case 2:
    {
        Hostile_Goblin* entity= new Hostile_Goblin(resourceManager, *this, coordinates, IDNumber, "goblin");

        std::cout<<"DEBUG: Created entity: " << "Goblin     ID: " << IDNumber <<std::endl;


        entityStack.push_back(entity);
        entityCollidableStack.push_back(entity);
        entityLivingStack.push_back(entity);
        break;
    }

    default:
    {
        break;
    }
    }

    //std::cout<<"-----------------" <<std::endl;
    for(int x = 0; x < entityStack.size(); x++)
    {
        //std::cout<<"Live entity: " << entityStack[x]->returnID()<<std::endl;
    }

    //std::cout<<"-----------------" <<std::endl;

    return IDNumber;
}


int EntityManager::createPlayer(std::string playerName, sf::Vector2f coordinates,
                                int hp, int maxHp,
                                int mp, int maxMp,
                                int st, int maxSt)
{
    int IDNumber = getIDNumber(EntityType::player);

    Entity_Player* entity= new Entity_Player(resourceManager, *this, lightManager, coordinates, IDNumber, "player", hp, maxHp, mp, maxMp, st, maxSt);
    std::cout<<"DEBUG: Created entity: " << "Player     ID: " << IDNumber <<std::endl;
    if(playerID == -1)
    {
        playerID = IDNumber;
    }
    else
    {
        playerID_2 = IDNumber;
    }

    entityStack.push_back(entity);
    entityCollidableStack.push_back(entity);
    entityLivingStack.push_back(entity);
    entityPlayableStack.push_back(entity);

    return IDNumber;
}

int EntityManager::createEntity(std::string entityName, sf::Vector2f coordinates)
{
    spawnTick = 35;
    int IDNumber = getIDNumber(EntityType::entity);
    //Temporary way

    if(entityName == "chicken")
    {
        Entity_Chicken* entity= new Entity_Chicken(resourceManager, *this, coordinates, IDNumber, "chicken");

        std::cout<<"DEBUG: Created entity: " << "Chicken     ID: " << IDNumber <<std::endl;


        entityStack.push_back(entity);
        entityCollidableStack.push_back(entity);
        entityLivingStack.push_back(entity);
    }
    else if(entityName == "goblin")
    {
        Hostile_Goblin* entity= new Hostile_Goblin(resourceManager, *this, coordinates, IDNumber, "goblin");

        std::cout<<"DEBUG: Created entity: " << "Goblin     ID: " << IDNumber <<std::endl;

        entityStack.push_back(entity);
        entityCollidableStack.push_back(entity);
        entityLivingStack.push_back(entity);
    }
    else
    {
        return -1;
    }

    return IDNumber;
}


int EntityManager::createSpecialEntity(int entity, int _attackerID, std::string _attackerName,
                                       sf::Vector2f _coordinates, sf::Vector2f _velocity, float _angle,
                                       int _duration, int _attackDamage, float _sizeMultiplier, float _timeMultiplier,
                                       int _extra)
{
    spawnTick = 35;
    int IDNumber = getIDNumber(EntityType::entity);

    switch (entity)
    {
    case 1:
    {
        Attack_Slash* entity = new Attack_Slash(resourceManager,IDNumber,_attackerID, _attackerName,
                                                _coordinates,  _velocity, _angle,
                                                _duration,  _attackDamage, _sizeMultiplier, _timeMultiplier,
                                                _extra);

        std::cout<<"DEBUG: Created entity: " << "Attack_Slash     ID: " << IDNumber <<std::endl;


        entityStack.push_back(entity);
        entityDamageStack.push_back(entity);
        break;
    }
    case 2:
    {
        Attack_Arrow* entity = new Attack_Arrow(resourceManager, *this, IDNumber, _attackerID, _attackerName,
                                                _coordinates,  _velocity, _angle,
                                                _duration,  _attackDamage, _sizeMultiplier, _timeMultiplier,
                                                _extra);

        std::cout<<"DEBUG: Created entity: " << "Attack_Arrow     ID: " << IDNumber <<std::endl;


        entityStack.push_back(entity);
        entityDamageStack.push_back(entity);
        entityCollidableStack.push_back(entity);
        break;
    }
    default:
    {
        break;
    }
    }

    // std::cout<<"-----------------" <<std::endl;
    for(int x = 0; x < entityStack.size(); x++)
    {
        // std::cout<<"Live entity: " << entityStack[x]->returnID()<<std::endl;
    }
    // std::cout<<"-----------------" <<std::endl;

    // }
    return IDNumber;
}

void EntityManager::createInteravtiveEntity(std::string entity, int x, int y, int type, int subtype)
{
    int IDNumber = getIDNumber(EntityType::entity);

    if(entity == "roof")
    {
        Interact_Roof* entity = new Interact_Roof(resourceManager, IDNumber, x, y, type, subtype);
        std::cout<<"DEBUG: Created entity: " << "Item     ID: " << IDNumber <<std::endl;

        entityStack.push_back(entity);
        entityInteractStack.push_back(entity);
    }
    else if(entity == "door")
    {
        Interact_Door* entity = new Interact_Door(resourceManager, IDNumber, x, y, type, subtype);
        std::cout<<"DEBUG: Created entity: " << "Item     ID: " << IDNumber <<std::endl;

        entityStack.push_back(entity);
        entityInteractStack.push_back(entity);
    }
}


void EntityManager::destroyEntity(int entityID)
{
    deadID.push_back(entityID);

    std::cout<<"DEBUG: Deleting entity: " << entityID<<std::endl;
    int e = 0;
    int eC = 0;
    int eD = 0;
    int eL = 0;
    int eP = 0;
    int eI = 0;

    for(int x = 0; x < entityCollidableStack.size(); x++)
    {
        if(entityCollidableStack[x]->returnID()==entityID)
        {
            eC = x;
            eC++;
        }
    }
    for(int x = 0; x < entityInteractStack.size(); x++)
    {
        if(entityInteractStack[x]->returnID()==entityID)
        {
            eI = x;
            eI++;
        }
    }
    for(int x = 0; x < entityDamageStack.size(); x++)
    {
        if(entityDamageStack[x]->returnID()==entityID)
        {
            eD = x;
            eD++;
        }
    }
    for(int x = 0; x < entityStack.size(); x++)
    {
        if(entityStack[x]->returnID()==entityID)
        {
            e = x;
            e++;
        }
    }

    for(int x = 0; x < entityLivingStack.size(); x++)
    {
        if(entityLivingStack[x]->returnID()==entityID)
        {
            eL = x;
            eL++;
        }
    }

    for(int x = 0; x < entityPlayableStack.size(); x++)
    {
        if(entityPlayableStack[x]->returnID()==entityID)
        {
            eP = x;
            eP++;
        }
    }

    if(e>0)
    {
        e--;
        delete entityStack[e];
        entityStack.erase(e + entityStack.begin());
    }
    if(eC>0)
    {
        eC--;
        entityCollidableStack.erase(eC + entityCollidableStack.begin());
    }
    if(eI>0)
    {
        eI--;
        entityInteractStack.erase(eI + entityInteractStack.begin());
    }
    if(eD>0)
    {
        eD--;
        entityDamageStack.erase(eD + entityDamageStack.begin());
    }
    if(eL>0)
    {
        eL--;
        entityLivingStack.erase(eL + entityLivingStack.begin());
        for(int x = 0; x < entityDamageStack.size(); x++)
        {
            if(entityDamageStack[x]->getAttackerID() == entityID)
            {
                destroyEntity(entityDamageStack[x]->returnID());
            }
        }
    }
    if(eP>0)
    {
        eP--;
        playerID = -1;
        entityPlayableStack.erase(eP + entityPlayableStack.begin());
    }
}

void EntityManager::handleInput(int actionType,bool isPressed, int player)
{
    for(int x = 0; x < entityPlayableStack.size(); x++)
    {
        switch (player)
        {
        case 0:
            if(entityPlayableStack[x]->returnID()==playerID)
            {
                entityPlayableStack[x]->handleImput(actionType,isPressed);
            }
        case 1:
            if(entityPlayableStack[x]->returnID()==playerID_2)
            {
                entityPlayableStack[x]->handleImput(actionType,isPressed);
            }
        }
    }
}

void EntityManager::drawEntity()
{
    sf::Vector2f playerCoordinates;
    for(int x = 0; x < entityPlayableStack.size(); x++)
    {
        if(entityPlayableStack[x]->returnID()==playerID)
        {
            playerCoordinates = entityPlayableStack[x]->getCoordinates();
        }
    }

    for(int x = 0; x < entityStack.size(); x++)
    {
        if(std::abs(entityStack[x]->getCoordinates().x - playerCoordinates.x) < 3000 )
        {
            if(std::abs(entityStack[x]->getCoordinates().y - playerCoordinates.y) < 2000 )
            {
                entityStack[x]->drawEntity(window);
            }
        }
    }
    for(int x = 0; x < entityDamageStack.size(); x++)
    {
        if(std::abs(entityDamageStack[x]->getCoordinates().x - playerCoordinates.x) < 3000 )
        {
            if(std::abs(entityDamageStack[x]->getCoordinates().y - playerCoordinates.y) < 2000 )
            {
                entityDamageStack[x]->drawLayer2(window);
            }
        }
    }

    for(int x = 0; x < entityInteractStack.size(); x++)
    {
        if(std::abs(entityInteractStack[x]->getCoordinates().x - playerCoordinates.x) < 5000 )
        {
            if(std::abs(entityInteractStack[x]->getCoordinates().y - playerCoordinates.y) < 4000 )
            {
                entityInteractStack[x]->drawLayer3(window);
            }
        }
    }
}


void EntityManager::attackCheck()
{
    for(int x = 0; x < entityLivingStack.size(); x++)
    {
        if(entityLivingStack[x]->getCategory() == hostile)
        {
            sf::Vector2f coords (-1000, -1000);
            int distance = 1000000;

            int X1, Y1;
            X1 = entityLivingStack[x]->getCoordinates().x;
            Y1 = entityLivingStack[x]->getCoordinates().y;

            for(int y = 0; y < entityLivingStack.size(); y++)
            {
                if(entityLivingStack[y]->getCategory() == passive || entityLivingStack[y]->getCategory() == player)
                {
                    int X2, Y2;
                    int distanceTemp;

                    X2 = entityLivingStack[y]->getCoordinates().x;
                    Y2 = entityLivingStack[y]->getCoordinates().y;
                    /// Distance
                    distanceTemp = std::sqrt(std::pow(X1-X2,2)+(std::pow(Y1-Y2,2)));
                    if(distanceTemp < distance)
                    {
                        distance = distanceTemp;
                        coords = entityLivingStack[y]->getCoordinates();
                    }
                }
            }
            sf::Vector2i intCoords(coords.x,coords.y);
            entityLivingStack[x]->getNumb(distance, intCoords);
        }
    }


    int Y1, Y2;
    int X1, X2;
    int distance;
    int ID;

    sf::Vector2f coords;

    for(int x = 0; x < entityDamageStack.size(); x++)
    {
        for(int y = 0; y < entityLivingStack.size(); y++)
        {
            if(entityDamageStack[x]->getAttackerID() == entityLivingStack[y]->returnID())
            {
                entityDamageStack[x]->update(entityLivingStack[y]->getCoordinates());
                y = entityLivingStack.size() + 1;
            }
        }


        if(entityDamageStack[x]->isActive())
        {
            X1 = entityDamageStack[x]->getCoordinates().x;
            Y1 = entityDamageStack[x]->getCoordinates().y;
            for(int y = 0; y < entityLivingStack.size(); y++)
            {
                X2 = entityLivingStack[y]->getCoordinates().x;
                Y2 = entityLivingStack[y]->getCoordinates().y;
                /// Distance
                distance = std::sqrt(std::pow(X1-X2,2)+(std::pow(Y1-Y2,2)));

                if(distance<2000 && (entityLivingStack[y]->returnID() !=  entityDamageStack[x]->getAttackerID())) //&& (entityDamageStack[x]->getAttacker() != entityLivingStack[y]->getName())
                {
                    if(entityDamageStack[x]->checkCollision(entityLivingStack[y]->getCoordinates(), entityLivingStack[y]->getSideRadius()))
                    {
                        if(entityDamageStack[x]->getAttackerID() == playerID || entityLivingStack[y]->returnID() == playerID)
                        {
                            entityLivingStack[y]->setHP(entityLivingStack[y]->getHP() - entityDamageStack[x]->getDamage(entityLivingStack[y]->returnID()));
                        }
                        if(entityLivingStack[y]->getCategory() == passive)
                        {
                            for(int z = 0; z < entityLivingStack.size(); z++)
                            {
                                if(entityDamageStack[x]->getAttackerID() == entityLivingStack[z]->returnID())
                                {
                                    if(entityLivingStack[z]->getCategory() == hostile)
                                    {
                                        entityLivingStack[y]->setHP(entityLivingStack[y]->getHP() - entityDamageStack[x]->getDamage(entityLivingStack[y]->returnID()));
                                    }
                                }
                            }
                        }



                        if(entityLivingStack[y]->getHP() <= 0 && entityLivingStack[y]->returnID() != playerID)
                        {
                            std::cout<<"DEBUG: Entity: "<< entityLivingStack[y]->getName()<< " ID: " <<entityLivingStack[y]->returnID()<< "   Has been killed by: "<< entityDamageStack[x]->getAttacker() <<std::endl;
                            destroyEntity(entityLivingStack[y]->returnID());
                        }
                        else if(entityLivingStack[y]->getHP() <= 0 && entityLivingStack[y]->returnID() == playerID)
                        {
                            entityLivingStack[y]->setHP(100);
                            entityLivingStack[y]->setMP(50);
                            entityLivingStack[y]->setST(100);
                            entityLivingStack[y]->setCoordinates(sf::Vector2f(800,2400));

                        }
                    }
                }
            }
        }
        else
        {
            destroyEntity(entityDamageStack[x]->returnID());
        }
    }
}

void EntityManager::update(TileEngine& tileEngine, sf::Vector2f player_MapCoordinates, sf::Vector2f mouseCoordinates, float angle)
{
    for(int x = 0; x < entityPlayableStack.size(); x++)
    {
        if(entityPlayableStack[x]->returnID()==playerID)
        {
            entityPlayableStack[x]->setAngleToMouse(angle);
            entityPlayableStack[x]->setMouseCoordinates(mouseCoordinates);

            // Interactions with player
            for(int y = 0; y < entityInteractStack.size(); y++)
            {
                entityInteractStack[y]->checkInteraction(entityPlayableStack[x]->getCoordinates().x, entityPlayableStack[x]->getCoordinates().y, entityPlayableStack[x]->getSideRadius().x, entityPlayableStack[x]->getSideRadius().y);
            }
            x = entityPlayableStack.size() + 1;
        }
    }

    if(spawnTick>0)
    {
        spawnTick--;
    }

    timer1++;


    int returnCollision[4] = {0,0,0,0};
    for(int x = 0; x < entityCollidableStack.size(); x++)
    {
        entityCollidableStack[x]->update(tileEngine.getMapCollision(entityCollidableStack[x]->getMapCoordinates(), entityCollidableStack[x]->getCoordinates(), entityCollidableStack[x]->getSideRadius(), entityCollidableStack[x]->getVelocity(), returnCollision), returnCollision);
    }

    attackCheck();
}

sf::Vector2f EntityManager::getPlayerVelocity()
{
    for(int x = 0; x < entityPlayableStack.size(); x++)
    {
        if(entityPlayableStack[x]->returnID()==playerID)
        {
            return entityPlayableStack[x]->getVelocity();
        }
    }
}

sf::Vector2f EntityManager::getPlayerCoordinates()
{
    for(int x = 0; x < entityPlayableStack.size(); x++)
    {
        if(entityPlayableStack[x]->returnID()==playerID)
        {
            return entityPlayableStack[x]->getCoordinates();
        }
    }
}

void EntityManager::setPlayerCoordinates(sf::Vector2f coords)
{
    for(int x = 0; x < entityPlayableStack.size(); x++)
    {
        if(entityPlayableStack[x]->returnID()==playerID)
        {
            entityPlayableStack[x]->setCoordinates(coords);
        }
    }
}

std::tuple<int, int, int, int, int, int> EntityManager::getPlayerStats()
{
    for(int x = 0; x < entityPlayableStack.size(); x++)
    {
        if(entityPlayableStack[x]->returnID()==playerID)
        {
            return entityPlayableStack[x]->getStats();
        }
    }
}

int EntityManager::getEntityCount()
{
    return entityStack.size();
}

void EntityManager::doAttack(int attack, float angle, int ID, float x, float y)
{
    int st;
    std::ostringstream os;

    for(int x = 0; x < entityLivingStack.size(); x++)
    {
        if(entityLivingStack[x]->returnID()==ID)
        {
            os << entityLivingStack[x]->getName();
        }
    }


    for(int x = 0; x < entityPlayableStack.size(); x++)
    {
        if(entityPlayableStack[x]->returnID()==playerID)
        {
            st = entityPlayableStack[x]->getST();
        }
    }


    if(timer1>20)
    {
        timer1 = 0;
        switch (attack)
        {
        case 1:
        {
            if(st>=5)
            {
                createSpecialEntity(1,ID,os.str(),getPlayerCoordinates(),sf::Vector2f(0,0),angle,35,4,1,1,1);
                for(int x = 0; x < entityPlayableStack.size(); x++)
                {
                    if(entityPlayableStack[x]->returnID()==playerID)
                    {
                        entityPlayableStack[x]->setST(st-5);
                    }
                }
            }
            break;
        }
        case 2:
        {
            if(st>=10)
            {
                createSpecialEntity(2,ID,os.str(),getPlayerCoordinates(),sf::Vector2f(4,4),angle,150,4,1,1,1);
                for(int x = 0; x < entityPlayableStack.size(); x++)
                {
                    if(entityPlayableStack[x]->returnID()==playerID)
                    {
                        entityPlayableStack[x]->setST(st-10);
                    }
                }
            }
            break;
        }
        }
    }
}

std::vector <int> EntityManager::getDeadIDs()
{
    std::vector <int> IDs;
    IDs  = deadID;
    deadID.clear();
    return IDs;
}

void EntityManager::setCharacteristic(int ID, std::string characteristic, int amount)
{
    for(int it = 0; it != entityLivingStack.size(); it++)
    {
        if(entityLivingStack[it]->returnID() == ID)
        {
            if(characteristic == "hp")
            {
                entityLivingStack[it]->setHP(amount);
            }
        }
    }
}


void EntityManager::saveEntities(SaveFile& save_entity)
{
    for(int it = 0; it != entityLivingStack.size(); it++)
    {
        entityLivingStack[it]->saveEntity();
        std::map <std::string, std::string>& characteristicMap = entityLivingStack[it]->getSaveCharacteristics();

        if(entityLivingStack[it]->returnID() != playerID)// && entityLivingStack[it]->returnID() != playerID_2)
        {
            std::string entityType = entityLivingStack[it]->getEntityType();

            int coords_x = entityLivingStack[it]->getCoordinates().x;
            int coords_y = entityLivingStack[it]->getCoordinates().y;
            int hp = entityLivingStack[it]->getHP();

            std::vector<std::string> entityCharacteristics;
            entityCharacteristics.push_back(utl::asString(entityLivingStack[it]->returnID()));
            entityCharacteristics.push_back(utl::asString(coords_x));
            entityCharacteristics.push_back(utl::asString(coords_y));
            entityCharacteristics.push_back(utl::asString(hp));

            std::string entityString = utl::conjoinString(entityCharacteristics, ',');

            save_entity.addItem(entityType, entityString);
        }
    }
    save_entity.writeFile();
}
