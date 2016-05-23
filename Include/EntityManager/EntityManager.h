#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <iostream>
#include <vector>
#include <list>

#include "EntityManager/Entity.h"
#include "EntityManager/Entity/Collidable/Entity_Collidable.h"
#include "EntityManager/Entity/Collidable/Attack/Entity_Attack.h"
#include "EntityManager/Entity/Collidable/Living/Player/Entity_Playable.h"
#include "Entity_Interactable.h"

#include "SaveFile.h"

#include "ResourceManager.h"
#include "TileEngine.h"
#include "LightManager.h"

class EntityManager
{
public:
    enum ManagerType {singleplayer, multiplayer, server};
    enum EntityType  {player, entity};

    EntityManager(ManagerType _type, sf::RenderWindow &mWindow, ResourceManager &res, LightManager& _lightManager);
    ~EntityManager();

    void handleInput(int actionType,bool isPressed,int player);
    void update(TileEngine& tileEngine, sf::Vector2f player_MapCoordinates,sf::Vector2f mouseCoordinates, float angle);

    void console_displayEntities();

    sf::Vector2f getPlayerVelocity();
    sf::Vector2f getPlayerCoordinates();
    void setPlayerCoordinates(sf::Vector2f coords);
    void setPlayerCoordinates2(sf::Vector2f coords);
    std::tuple<int, int, int,int, int, int> getPlayerStats();
    int getPlayerID()
    {
        return playerID;
    }
    int getPlayerID_2()
    {
        return playerID_2;
    }

    void saveEntities(SaveFile& save_entity);
    void setCharacteristic(int ID, std::string characteristic, int amount);

    int getEntityCount();

    int createEntity(int entity, sf::Vector2f coordinates);
    int createEntity(std::string entityName, sf::Vector2f coordinates);

    int createPlayer(std::string playerName, sf::Vector2f coordinates,
                     int hp, int maxHp,
                     int mp, int maxMp,
                     int st, int maxSt);

    int createSpecialEntity(int entity, int _attackerID, std::string _attackerName,
                            sf::Vector2f _coordinates, sf::Vector2f _velocity, float _angle,
                            int _duration, int _attackDamage, float _sizeMultiplier, float _timeMultiplier,
                            int _extra);
    void createInteravtiveEntity(std::string entity, int x, int y, int type, int subtype);

    void destroyEntity(int entityID);
    void drawEntity();
    void attackCheck();

    int timer1;

    void doAttack(int attack, float angle, int ID, float x, float y);

    std::vector <int> getDeadIDs();

private:
    ManagerType type;

    int getIDNumber(EntityType entityType);

    int spawnTick;

    sf::RenderWindow& window;
    ResourceManager& resourceManager;
    LightManager& lightManager;

    int entityNumber;

    std::vector <Entity*> entityStack;
    std::vector <Entity_Collidable*> entityCollidableStack;
    std::vector <Entity_Living*> entityLivingStack;
    std::vector <Entity_Playable*> entityPlayableStack;
    std::vector <Entity_Attack*> entityDamageStack;
    std::vector <Entity_Interactable*> entityInteractStack;

    std::vector <int> deadID;

    ///singleplayer
    int playerID;
    int playerID_2;

    ///multiplayer
    int last_entityID;
    int last_playerID;
};

#endif // ENTITYMANAGER_H
