#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

#include <SFML/Graphics.hpp>
#include <tuple>

#include "EntityManager/Entity/Collidable/Living/Player/Entity_Playable.h"
#include "ResourceManager.h"
#include "EntityManager/EntityManager.h"
#include "Struct_Animation.h"


class Entity_Player : public Entity_Playable
{
public:
    Entity_Player(ResourceManager &res,EntityManager &entityManager, LightManager& _lightManager,
                sf::Vector2f coordinates, int ID, std::string _entityType,
                int _hp, int _maxHp,
                int _mp, int _maxMp,
                int _st, int _maxSt);
    ~Entity_Player();

    ///default
    void drawEntity(sf::RenderWindow &mWindow);
    void handleImput(int actionType, bool isPressed);
    void update(int effect, int (&returnCollision)[4]);

    void saveEntity() {};

    ///get's
    int returnID();

    unsigned char getClass() {return playerClass;}
    std::string getName();
    void getNumb(int a, sf::Vector2i entityCoords);
    sf::Vector2f getCoordinates();
    sf::Vector2i getMapCoordinates();
    sf::Vector2f getSideRadius();
    sf::Vector2f getVelocity();
    std::tuple<int, int, int, int, int, int> getStats();
    int getHP(){return hp;}
    int getMP(){return mp;}
    int getST(){return stamina;}
    int getMaxHP(){return maxHP;}
    int getMaxMP(){return maxMP;}
    int getMaxST(){return maxST;}
    std::string getEntityType(){return entityType;}
    EntityCategory getCategory(){return entityCategory;}

    std::vector <std::pair <std::string, std::string> > characteristics;
    ///saved characteristics
    std::vector <std::pair <std::string, std::string> > getCharacteristics() {return characteristics;}
    std::string getCharacteristic(std::string characteristic) {}
    void setCharacteristics( std::vector <std::pair <std::string, std::string> > getCharacteristics()) {};

    ///set's
    void setAngleToMouse(float angle);
    void setMouseCoordinates(sf::Vector2f gottenMouseCoordinates);
    void setHP(int HP){hp = HP;}
    void setMP(int MP){mp = MP;}
    void setST(int ST){stamina = ST;}
    void setCoordinates(sf::Vector2f coords) {coordinates = coords;}

    ///temp server crap
    int getPlayerStep(){return playerStep;}

private:
    ///default
    int ID;
    sf::Sprite entitySprite_HP;
    sf::Sprite entitySprite;
    sf::Vector2f coordinates;
    sf::Vector2i mapCoordinates;
    sf::Vector2f mouseCoordinates;
    float angleToMouse;
    sf::Vector2f velocity;
    const sf::Vector2f sideRadius;

    std::string entityType;
    EntityCategory entityCategory;


    ///layers
    Struct_Animation animation;//Temp
    //Struct_Animation skin;
    //Struct_Animation hair;
    //Struct_Animation under;



    ///class
    enum PlayerClass{rogue, archer};
    PlayerClass playerClass;

    ///stats
    int baseHP;
    int hp;
    int maxHP;
    int baseMP;
    int mp;
    int maxMP;
    int baseST;
    int stamina;
    int maxST;

     ///timing
    unsigned short tick;

    ///animation timing
    int count_playerStep;
    int playerStep;
    int direction_facing;
    int animationStep;
    int animationDirection;
    float previousVelocity;

    ///controls
    bool shiftIsPressed;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;

    ///temp running
    bool wasRunning;
    int runningTick;

    ///lights
    int lightID;

    ///references
    ResourceManager &res;
    EntityManager& entityManager;
    LightManager& lightManager;

    ///collision visual
    sf::RectangleShape colRect;
};

#endif // ENTITY_PLAYER_H
