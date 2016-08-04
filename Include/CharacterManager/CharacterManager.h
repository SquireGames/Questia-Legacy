#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H
#include "EntityManager.h"
#include "GuiManager.h"

class CharacterManager
{
public:
    CharacterManager(sf::RenderWindow &_window, EntityManager& _entityManager, GuiManagerNew& _guiManager);
    ~CharacterManager();

    void handleInput(int actionType, bool isPressed, int player);

private:
    sf::RenderWindow &window;
    EntityManager& entityManager;
    GuiManagerNew& guiManager;
};

#endif // CHARACTERMANAGER_H
