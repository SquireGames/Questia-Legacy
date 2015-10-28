#ifndef COMMANDSMANAGER_H
#define COMMANDSMANAGER_H

#include <SFML/Graphics.hpp>
#include <sstream>

#include "Data_Desktop.h"
#include "EntityManager/EntityManager.h"

class CommandsManager
{
public:
    CommandsManager(sf::RenderWindow &_window, EntityManager& _entityManager);
    ~CommandsManager();

    void getCharImput(char imput);
    void drawCommandArea();
    void update();
    bool handleImput(int actionType,bool isPressed,int player);

    void setActivity(bool _isActive);
    bool isActive();

private:
    std::stringstream textImput;
    std::map <int, std::string> previousCommands;
    int currentCommand;
    std::map <int, sf::Text> visibleText;
    int timer;
    bool isGood;
    bool isCommandsActive;

    sf::Sprite   sprite_chatArea;
    sf::Texture texture_chatArea;

    EntityManager& entityManager;
    sf::RenderWindow &window;
};

#endif // COMMANDSMANAGER_H
