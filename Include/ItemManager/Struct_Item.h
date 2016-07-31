#ifndef STRUCT_ITEM_H
#define STRUCT_ITEM_H

#include <string>
#include <SFML/Graphics.hpp>
#include <map>

#include "Utl/SpriteSheet.h"

enum ItemUsage {ground, inventory, equipped};
enum ItemType {use, combat, inactive};
enum AttackType {none, sword, bow};


struct Struct_Item
{
    Struct_Item(ResourceManager& _resourceManager,
                int _storageID, std::string _itemID,
                std::string _itemName, std::string _itemDescription,
                int _coord_x, int _coord_y,
                int _gridSize_x, int _gridSize_y,
                std::string _inventorySpriteLoc, std::string _usageSpriteLoc,
                ItemUsage _itemUsage, ItemType _itemType, AttackType _attackType):
        itemID(_itemID)
        , storageID(_storageID)

        , itemName(_itemName)
        , itemDescription(_itemDescription)

        , itemUsage (_itemUsage)
        , itemType (_itemType)
        , attackType(_attackType)

        , coord_x(_coord_x)
        , coord_y(_coord_y)

        , gridSize_x(_gridSize_x)
        , gridSize_y(_gridSize_y)

        , usageSprite(_resourceManager, _usageSpriteLoc, 1, 1)
        , inventorySprite(_resourceManager, _inventorySpriteLoc, 1, 1)

    {

    }

    std::string itemID;             // item identification
    int storageID;          // item ID for the system

    std::string itemName;
    std::string itemDescription;

    ItemUsage itemUsage;
    ItemType itemType;
    AttackType attackType;

    int coord_x;
    int coord_y;

    //inv grid, management handled by the container
    int gridSize_x;
    int gridSize_y;

    //std::map <int, std::map < > >

    SpriteSheet usageSprite;
    SpriteSheet inventorySprite;



    //future implementation
    int quality;
    int subType;
    int price;
};

#endif // STRUCT_ITEM_H
