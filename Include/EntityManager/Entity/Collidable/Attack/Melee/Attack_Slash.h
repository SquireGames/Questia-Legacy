#ifndef ATTACK_SLASH_H
#define ATTACK_SLASH_H

#include "EntityManager/Entity/Collidable/Attack/Entity_Attack.h"
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class Attack_Slash : public Entity_Attack
{
public:
    Attack_Slash(ResourceManager &res, int _attackID,int _attackerID, std::string _attackerName,
                 sf::Vector2f _coordinates, sf::Vector2f _velocity, float _angle,
                 int _duration, int _attackDamage, float _sizeMultiplier, float _timeMultiplier,
                 int _extra);

    /*/ Entity /*/

public:
    int returnID();
    void drawEntity(sf::RenderWindow &window);
    void update(int effect, int (&returnCollision)[4]);
private:
    sf::Vector2f coordinates;
    sf::Vector2i mapCoordinates;

    sf::Sprite entitySprite;

    /*/ Collision /*/

public:
    sf::Vector2f getSideRadius();
    sf::Vector2f getVelocity();
    sf::Vector2f getCoordinates();
    sf::Vector2i getMapCoordinates();
private:
    sf::Vector2f velocity;

    /*/ Attack /*/

public:
    bool checkCollision(sf::Vector2f objectCoordinates, sf::Vector2f objectSideRadius);
    bool isActive(); //Check duration
    void update(sf::Vector2f coords); // Just for ticks and movement
    int getDamage(int ID); // ID is to make attacks only hit x per ID
    std::string getAttacker();
    int getAttackerID() {return attackerID;}
    void setCoordinates(sf::Vector2f coords) {coordinates = coords;}

private:
    int attackID;
    std::string attackerName;
    int attackerID;

    int duration;
    int initDuration;
    int attackDamage;
    float sizeMultiplier;
    float timeMultiplier;
    int extra;


    /*/ Extra /*/
    float angle;
    float angleDifference;

    std::vector <int> entityIDList;
    std::vector<sf::Vector2f> hitbox_Attack;

    sf::CircleShape circleAttack [4];
    sf::CircleShape circleTarget [4];

    sf::RectangleShape rectAttack[4];
    sf::RectangleShape rectTarget[4];

    float angleRectA[4];

    sf::Vector2f rectBox1[4];
    sf::Vector2f rectBox1_P[10];

    sf::Vector2f rectBox2[4];
    ResourceManager &res;

    void drawLayer2(sf::RenderWindow &window);
};

#endif // ATTACK_SLASH_H
