#include "ItemManager/ItemManager.h"

ItemManager::ItemManager(sf::RenderWindow &_window, ResourceManager& _resourceManager):
    resourceManager(_resourceManager)
    , window(_window)
{

}

ItemManager::~ItemManager()
{

}

void ItemManager::spawnItem()
{
    int IDNumber;

    std::vector<int> itemList;
    for(int x = 0; x < itemVector.size(); x++)
    {
        itemList.push_back(itemVector[x]->vectorID);
    }

    std::sort(itemList.begin(),itemList.end());
    if(itemList.size() > 0)
    {
        if(itemVector.size() != itemList[itemList.size()-1]+1)
        {
            if(itemVector.size()>1)
            {
                for(int x = 0; x < itemList.size(); x++)
                {
                    if (itemList[x]+1 != itemList[x+1])
                    {
                        IDNumber = itemList[x]+1;
                        x = 99999;
                    }
                }
            }
            else
            {
                IDNumber = itemList[itemList.size()-1]+1;
            }
        }
        else
        {
            IDNumber = itemList[itemList.size()-1]+1;
        }
    }
    else
    {
        IDNumber = 0;
    }

    Struct_Item* item = new Struct_Item();

    item->itemID = 0;
    item->vectorID = IDNumber;
    item->itemType = combat;
    item->attackType = sword;
    item->itemUsage = ground;
    item->itemString = "Wooden Club";
    item->itemSprite.setTexture(resourceManager.getTexture("1.png"));
    item->coord_x = 0;
    item->coord_y = 0;
    item->grid_x = 1;
    item->grid_y = 2;
    item->quality = 50;
    item->subType = 0;
    item->price = 0;

    itemVector.push_back(item);
}

void ItemManager::destroyItem(int item)
{
    int e = 0;

    for(int x = 0; x < itemVector.size(); x++)
    {
        if(itemVector[x]->vectorID == item)
        {
            e = x;
            e++;
        }
    }
    if(e>0)
    {
        e--;
        delete itemVector[e];
        itemVector.erase(e + itemVector.begin());
    }
}

void ItemManager::drawItems()
{
    for(int x = 0; x < itemVector.size(); x++)
    {
        switch (itemVector[x]->itemUsage)
        {
        case ground:
            window.draw(itemVector[x]->itemSprite);
            break;
        case invetory:
            break;
        case equipped:
            break;
        case inUse:
            break;
        default:
            break;

        }
    }
}

