#include "CommandsManager.h"
#include "Utl/Utl.h"
#include <string>

// Amount of commands saved in memory to press up to find
#define COUNT_HISTORY 10
#define POS_CHAT_X 40
#define POS_CHAT_Y 660

// Amount of lines of strings to save
#define COUNT_VISIBLE 20
#define COUNT_VISIBLE_FIT 7

CommandsManager::CommandsManager(sf::RenderWindow &_window, EntityManager& _entityManager, MultiplayerManager* _multiplayerManager, TimeManager& _timeManager):
      window(_window)
    , entityManager(_entityManager)
    , multiplayerManager(_multiplayerManager)
    , timeManager(_timeManager)

    , isCommandsActive(false)
    , textImput()
    , previousCommands()
    , currentCommand(-1)
    , visibleText()
    , timer (0)
    , isGood(true)
{
    for (int it = 0; it != COUNT_HISTORY; it++)
    {
        previousCommands[it] = "";
    }

    for (int it = 0; it != COUNT_VISIBLE; it++)
    {
        sf::Text text;
        text.setCharacterSize(20);
        text.setColor(sf::Color::White);
        text.setString(std::string());
        text.setFont(Data_Desktop::getInstance().font1);
        visibleText[it] = text;
    }

    texture_chatArea.loadFromFile("Media/Image/Game/Gui/ChatBox.png");
    sprite_chatArea.setPosition(POS_CHAT_X, POS_CHAT_Y);
    sprite_chatArea.setTexture(texture_chatArea);
}

CommandsManager::CommandsManager(sf::RenderWindow &_window, EntityManager& _entityManager, TimeManager& _timeManager):
      window(_window)
    , entityManager(_entityManager)
    , multiplayerManager(nullptr)
    , timeManager(_timeManager)

    , isCommandsActive(false)
    , textImput()
    , previousCommands()
    , currentCommand(-1)
    , visibleText()
    , timer (0)
    , isGood(true)
{
    for (int it = 0; it != COUNT_HISTORY; it++)
    {
        previousCommands[it] = "";
    }

    for (int it = 0; it != COUNT_VISIBLE; it++)
    {
        sf::Text text;
        text.setCharacterSize(20);
        text.setColor(sf::Color::White);
        text.setString(std::string());
        text.setFont(Data_Desktop::getInstance().font1);
        visibleText[it] = text;
    }

    texture_chatArea.loadFromFile("Media/Image/Game/Gui/ChatBox.png");
    sprite_chatArea.setPosition(POS_CHAT_X, POS_CHAT_Y);
    sprite_chatArea.setTexture(texture_chatArea);
}


CommandsManager::~CommandsManager()
{

}

void CommandsManager::update()
{

}

void CommandsManager::getCharImput(char input)
{
    // TODO Rebindable chat key

    /// ' ' = nothing, 'S' = shift, 'E' = enter, '_' = backspace

    if(isCommandsActive)
    {
        if(input != ' ' && input != 'S' && input != 29 && input != 30)
        {
            if(input == '_') // backspace
            {
                std::string tempSt;
                tempSt = textImput.str();
                if(tempSt.length() > 0)
                {
                    tempSt.erase(tempSt.size() - 1, 1);
                }
                textImput.str(std::string());
                textImput << tempSt;
                visibleText[0].setString(textImput.str());
            }
            else
            {
                if(input == 10)
                {
                    input = 'C';
                }
                else if(input == 11)
                {
                    input = 'S';
                }
                else if(input == 12)
                {
                    input = 'A';
                }
                else if(input == 17)
                {
                    input = 'T';
                }
                else if(input == 14)
                {
                    input = 'B';
                }
                else if(input == 15)
                {
                    input = '_';
                }
                else if(input == 16)
                {
                    input = 'E';
                }
                else if(input == 'B')
                {
                    input = ' ';
                }
                else if(input == 'E')
                {
                    isGood = false;
                }
                if(isGood)
                {
                    textImput << input;
                }
                visibleText[0].setString(textImput.str());
                isGood = true;
            }
        }
        else if(input == 29 || input == 30) // up or down
        {
            if(input == 29) // up
            {
                if(currentCommand + 1 < COUNT_HISTORY)
                {
                    currentCommand++;
                    textImput.str(std::string());
                    textImput << previousCommands[currentCommand];
                    visibleText[0].setString(textImput.str());
                }
            }
            else if(input == 30) // down
            {
                if(currentCommand -1 > -1)
                {
                    currentCommand--;
                    textImput.str(std::string());
                    textImput << previousCommands[currentCommand];
                    visibleText[0].setString(textImput.str());
                }
            }
        }
    }
}

void CommandsManager::drawCommandArea()
{
    if(isCommandsActive)
    {
        window.draw(sprite_chatArea);
        for(int it = 0; it !=COUNT_VISIBLE_FIT; it++)
        {
            visibleText[it].setPosition(20 + POS_CHAT_X, 240 + POS_CHAT_Y - (it * 40));
            window.draw(visibleText[it]);
        }
    }
}

void CommandsManager::setActivity(bool _isActive)
{
    isCommandsActive = _isActive;
}

bool CommandsManager::handleImput(int actionType, bool isPressed,int player)
{
    // toggle box
    if(actionType == 21 && isPressed == true )
    {
        if(isCommandsActive == true)
        {
            isCommandsActive = false;
        }
        else
        {
            isCommandsActive = true;
        }
    }

    // Enter
    else if(actionType == 20 && isPressed == true && isCommandsActive == true && textImput.str().length() > 0)
    {
        std::string commandSt = textImput.str();
        textImput.str(std::string());

        /// save commands
        if(commandSt != previousCommands[0])
        {
            for(int it = COUNT_HISTORY - 2; it >= 0; it--)
            {
                previousCommands[it + 1] = previousCommands[it];
            }
            previousCommands[0] = commandSt;
        }
        currentCommand = -1;

        /// Save visible text
        for(int it = COUNT_VISIBLE - 1; it > 0; it--)
        {
            visibleText[it].setString(visibleText[it-1].getString());
        }
        visibleText[0].setString(std::string());

        /// check if its chat or command
        if(commandSt[0] == '/')
        {
            std::stringstream ss;
            std::string param[6];

            int character = 1;

            for(unsigned char it = 0; it != 6; it++)
            {
                for(char it = '?'; it != ' '&& it != '\0';)
                {
                    it = commandSt[character];
                    ss << commandSt[character];
                    character++;
                }
                ss >> param[it];
                ss.str(std::string());
            }

            for(int it = 0; it < 6; it++)
            {
                param[it].erase(std::remove(param[it].begin(), param[it].end(), ' '), param[it].end());
                param[it].erase(std::remove(param[it].begin(), param[it].end(), '\0'), param[it].end());
            }

            if(multiplayerManager != nullptr)
            {
                if(param[0] == "host")
                {
                    if(param[1] == "true")
                    {
                        multiplayerManager->startHostingServer();
                        std::string temp ("SERVER: Server is open");
                        visibleText[1].setString(temp);
                    }
                    else if(param[1] == "false")
                    {
                        multiplayerManager->terminateHost();
                    }
                    else if(param[1] == "tick")
                    {
                        multiplayerManager->host_changeTickRate(utl::asFloat(param[2]));
                    }
                    else if(param[1] == "local")
                    {
                        std::stringstream ss;
                        ss << "SERVER: Local IP: " << multiplayerManager->getLocalIP();
                        visibleText[1].setString(ss.str());
                    }
                    else if(param[1] == "public")
                    {
                        std::stringstream ss;
                        ss << "SERVER: Public IP: " << multiplayerManager->getPublicIP();
                        visibleText[1].setString(ss.str());
                    }

                }
                else if(param[0] == "client")
                {
                    if(param[1] == "join")
                    {
                        if(param[2] == "localhost")
                        {
                            if(multiplayerManager->joinServer(multiplayerManager->getLocalIP()))
                            {
                                visibleText[1].setString(std::string ("CLIENT: Connected to server"));
                            }
                            else
                            {
                                visibleText[1].setString(std::string ("CLIENT: Could not connect to server"));
                            }

                        }
                        else
                        {
                            if(multiplayerManager->joinServer(param[2]))
                            {
                                visibleText[1].setString(std::string ("CLIENT: Connected to server"));
                            }
                            else
                            {
                                visibleText[1].setString(std::string ("CLIENT: Could not connect to server"));
                            }
                        }
                    }
                    else if(param[1] == "leave")
                    {
                        multiplayerManager->terminateClient();
                    }
                }
                else if (param[0] == "s")
                {
                    multiplayerManager->startHostingServer();
                    multiplayerManager->joinServer("192.168.2.6");
                }
            }
            if(param[0] == "time")
            {
                if(param[1] == "set")
                {
                    timeManager.setTime(static_cast<char> (utl::asInt(param[2])), static_cast<char> (utl::asInt(param[3])));
                }
                else if(param[1] == "step")
                {
                    timeManager.setTimeStep(static_cast<char>(utl::asInt(param[2])));
                }
            }
            else if(param[0] == "entityList")
            {
                entityManager.console_displayEntities();
            }
            // commands involving coordinates
            else if(param[0] == "spawn" || param[0] == "tp" ||  param[0] == "teleport")
            {
                if(param[0] == "tp" ||  param[0] == "teleport")
                {
                    param[3] = param[2];
                    param[2] = param[1];
                }

                // coordinates
                sf::Vector2f coords;
                bool isGood_x = false;
                bool isGood_y = false;
                if(param[2].length() > 0 && param[3].length() > 0)
                {
                    // x coord
                    if(param[2][0] == '~')
                    {
                        param[2].erase(param[2].begin());
                        if(std::atoi(param[2].c_str()) < 10000)
                        {
                            coords.x = std::atoi(param[2].c_str()) * 32 + entityManager.getPlayerCoordinates().x;
                            isGood_x = true;
                        }
                    }
                    else if(std::atoi(param[2].c_str()) < 10000)
                    {
                        coords.x = std::atoi(param[2].c_str()) * 32;
                        isGood_x = true;
                    }
                    // y coord
                    if(param[3][0] == '~')
                    {
                        param[3].erase(param[3].begin());
                        if(std::atoi(param[3].c_str()) < 10000)
                        {
                            coords.y = std::atoi(param[3].c_str()) * 32 + entityManager.getPlayerCoordinates().y;
                            isGood_y = true;
                        }
                    }
                    else if(std::atoi(param[3].c_str()) < 10000)
                    {
                        coords.y = std::atoi(param[3].c_str()) * 32;
                        isGood_y = true;
                    }
                }
                else
                {
                    coords = entityManager.getPlayerCoordinates();
                    isGood_x = true;
                    isGood_y = true;
                }

                if(isGood_x == true && isGood_y == true)
                {
                    if(param[0] == "spawn")
                    {
                        // Monsters
                        if(param[1][0] == 'e' && param[1][1] == 'n' &&param[1][2] == 't' &&param[1][3] == 'i' && param[1][4] == 't' &&param[1][5] == 'y' &&param[1][6] == ':')
                        {
                            if(param[1] == "entity:chicken")
                            {
                                entityManager.createEntity(1, coords);
                            }
                            else if(param[1] == "entity:goblin")
                            {
                                entityManager.createEntity(2, coords);
                            }
                        }
                    }
                    else if(param[0] == "tp" || param[0] == "teleport")
                    {
                        entityManager.setPlayerCoordinates(coords);
                    }
                }
            }
        }
        else
        {
            std::stringstream ss;
            std::string temp = visibleText[1].getString();
            ss << "Player 1: " << temp;
            visibleText[1].setString(ss.str());
        }
    }
    if(isCommandsActive)
    {
        return false;
    }
    else
    {
        return true;
    }
}
