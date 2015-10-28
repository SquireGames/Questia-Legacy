#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <map>
#include "ItemManager/Struct_Item.h"

#include "ResourceManager.h"

class ItemManager
{
public:
    ItemManager(sf::RenderWindow &_window, ResourceManager& _resourceManager);
    ~ItemManager();

    void spawnItem();
    void destroyItem(int item);

    void drawItems();

private:
    std::map <int, std::string> itemMap;
    std::vector <Struct_Item*> itemVector;

    ResourceManager& resourceManager;
    sf::RenderWindow &window;
};

#endif // ITEMMANAGER_H
