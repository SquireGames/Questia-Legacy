#ifndef STRUCT_ITEMCONTAINER_H
#define STRUCT_ITEMCONTAINER_H

#include <string>
#include <SFML/Graphics.hpp>
#include <map>

#include "ItemManager/Struct_Item.h"

enum ContainerHolder {inv, equipt};

struct Struct_ItemContainer
{
    Struct_ItemContainer(ContainerHolder _containerHolder, int _height, int _width):
        containerHolder(_containerHolder)
        , height(_height)
        , width (_width)
        , usedSlotsVector()
    {
        for(unsigned int x = 0; x != width; x++)
        {
            for(unsigned int y = 0; y != height; y++)
            {
                usedSlotsVector[x][y] = -1;
            }
        }
    }

    ContainerHolder containerHolder;

    unsigned int height;
    unsigned int width;

    std::vector <Struct_Item*> itemContainer;
    std::map <int,std::map <int, int> > usedSlotsVector; // TODO change to std::vector<std::vector<int> > for efficiency
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
