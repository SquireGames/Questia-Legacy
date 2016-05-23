#include "CharacterManager/CharacterManager.h"

CharacterManager::CharacterManager(sf::RenderWindow &_window, EntityManager& _entityManager, GuiManager& _guiManager):
    window(_window)
    , entityManager(_entityManager)
    , guiManager (_guiManager)
{

}

CharacterManager::~CharacterManager()
{

}


void CharacterManager::handleInput(int actionType, bool isPressed, int player)
{
    if(isPressed == true)
    {

    }
}
