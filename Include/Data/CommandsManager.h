#ifndef COMMANDSMANAGER_H
#define COMMANDSMANAGER_H

#include <SFML/Graphics.hpp>
#include <sstream>

#include "Data_Desktop.h"
#include "EntityManager/EntityManager.h"
#include "MultiplayerManager.h"
#include "TimeManager.h"

class CommandsManager
{
public:
    CommandsManager(sf::RenderWindow &_window, EntityManager& _entityManager, MultiplayerManager* _multiplayerManager, TimeManager& _timeManager);
    CommandsManager(sf::RenderWindow &_window, EntityManager& _entityManager, TimeManager& _timeManager);

    ~CommandsManager();

    void getCharImput(char input);
    void drawCommandArea();
    void update();
    bool handleImput(int actionType,bool isPressed,int player);

    void setActivity(bool _isActive);
    bool isActive();

private:
    sf::RenderWindow &window;
    EntityManager& entityManager;
    MultiplayerManager* multiplayerManager;
    TimeManager& timeManager;

    bool isCommandsActive;
    std::stringstream textImput;
    std::map <int, std::string> previousCommands;
    int currentCommand;
    std::map <int, sf::Text> visibleText;
    int timer;
    bool isGood;

    sf::Sprite   sprite_chatArea;
    sf::Texture texture_chatArea;
};

#endif // COMMANDSMANAGER_H
