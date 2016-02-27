#ifndef STRUCT_ITEMCONTAINER_H
#define STRUCT_ITEMCONTAINER_H

#include <string>
#include <SFML/Graphics.hpp>
#include <map>

#include "ItemManager/Struct_Item.h"

//enum ContainerHolder {inventory, equiptmnet};

struct Struct_ItemContainer
{
    std::vector <Struct_Item*> itemContainer;
    std::map <int,std::map <int, bool> > usedSlotsVector;

    unsigned int height;
    unsigned int width;


//    ContainerHolder containerHolder;
};

#endif // STRUCT_ITEMCONTAINER_H

  /*
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
    */
