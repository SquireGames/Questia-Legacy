#include "ItemManager/ItemManager.h"

ItemManager::ItemManager(sf::RenderWindow &_window, ResourceManager& _resourceManager):
    resourceManager(_resourceManager)
    , window(_window)
{

}

ItemManager::~ItemManager()
{

}



// Items
int ItemManager::getStorageID()
{
    int IDNumber = 0;

    std::vector<int> itemList;
    for(unsigned int x = 0; x < itemVector.size(); x++)
    {
        itemList.push_back(itemVector[x]->storageID);
    }

    std::sort(itemList.begin(),itemList.end());
    if(itemList.size() > 0)
    {
        if(itemVector.size() != static_cast <unsigned int> (itemList[itemList.size()-1]+1))
        {
            if(itemVector.size()>1)
            {
                for(unsigned int x = 0; x < itemList.size(); x++)
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

    return IDNumber;
}

void ItemManager::createItem(Struct_Item* item, int IDNumber, std::string itemName, ItemUsage itemUsage, int coord_x, int coord_y)
{
    bool isItem = true;
    if(itemName == "item:test")
    {
        item = new Struct_Item(resourceManager,
                               IDNumber, itemName,
                               "Item Name", "Item Desc",
                               coord_x, coord_y,   //coords
                               1, 1,   //grid size
                               "Media/Image/Game/Items/Test/Test_Inv.png", "Media/Image/Game/Items/Test/Test_Inv.png", //sprite loc
                               itemUsage, ItemType::inactive, AttackType::none);
    }
    else
    {
        isItem = false;
    }

    if(isItem)
    {
        // Inventory Sprite
        item->inventorySprite.getSprite(0,0).setOrigin(item->inventorySprite.getSheetWidth()/2.f,item->inventorySprite.getSheetHeight()/2.f);
        item->inventorySprite.getSprite(0,0).setScale(0.25,0.25);
        item->inventorySprite.getSprite(0,0).setPosition(coord_x, coord_y);
        itemVector.push_back(item);
    }
    else
    {
        item = nullptr;
    }
}

void ItemManager::spawnItem(std::string itemName, ItemUsage itemUsage, int coord_x, int coord_y)
{
    int IDNumber = getStorageID();

    Struct_Item* item = nullptr;

    createItem(item, IDNumber, itemName, itemUsage, coord_x, coord_y);

    if(item == nullptr)
    {
        delete item;
    }
    return;
}

void ItemManager::destroyItem(int item)
{
    int e = 0;

    for(unsigned int x = 0; x < itemVector.size(); x++)
    {
        if(itemVector[x]->storageID == item)
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

// Container

void ItemManager::createContainer(ContainerHolder containerHolder, int size_x, int size_y)
{
    Struct_ItemContainer itemContainer(containerHolder, size_x, size_y);
}

// Draw

void ItemManager::drawItems()
{
    for(unsigned int x = 0; x < itemVector.size(); x++)
    {
        switch (itemVector[x]->itemUsage)
        {
        case ground:
            window.draw(itemVector[x]->inventorySprite.getSprite(0,0));
            break;
        case inventory:
            break;
        case equipped:
            break;
        default:
            break;
        }
    }
}
