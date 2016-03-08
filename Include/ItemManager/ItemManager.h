#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <map>
#include "ItemManager/Struct_Item.h"
#include "ItemManager/Struct_ItemContainer.h"

#include "ResourceManager.h"

class ItemManager
{
public:
    ItemManager(sf::RenderWindow &_window, ResourceManager& _resourceManager);
    ~ItemManager();

    void spawnItem(std::string itemName, ItemUsage itemUsage, int coord_x, int coord_y);
    void destroyItem(int item);

    void createContainer(ContainerHolder containerHolder, int size_x, int size_y);

    void drawItems();

private:
    std::map <int, std::string> itemMap;
    std::vector <Struct_Item*> itemVector; // Stores every item pointer

    int getStorageID();
    void createItem(Struct_Item* item, int IDNumber, std::string itemName, ItemUsage itemUsage, int coord_x, int coord_y);

    ResourceManager& resourceManager;
    sf::RenderWindow &window;
};

#endif // ITEMMANAGER_H
