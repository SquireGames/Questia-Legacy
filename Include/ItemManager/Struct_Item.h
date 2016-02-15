#ifndef STRUCT_ITEM_H
#define STRUCT_ITEM_H

#include <string>
#include <SFML/Graphics.hpp>
#include <map>

enum ItemUsage {ground, invetory, equipped, inUse};
enum AttackType {none, sword, bow};
enum ItemType {use, combat, inactive};

struct Struct_Item
{
    int itemID;
    int storageID;

    ItemType itemType;
    AttackType attackType;
    ItemUsage itemUsage;

    std::string itemName;
    std::string itemDescription;

    sf::Sprite itemSprite;
    int coord_x;
    int coord_y;

    //inv grid
    int grid_x;
    int grid_y;

    //std::map <int, std::map < > >

    //future implementation
    int quality;
    int subType;
    int price;
};

#endif // STRUCT_ITEM_H
