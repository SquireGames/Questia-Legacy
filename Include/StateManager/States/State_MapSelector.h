#ifndef STATE_MAPSELECTOR_H
#define STATE_MAPSELECTOR_H

#include <SFML/Graphics.hpp>
#include <StateManager/State.h>
#include <map>

#include "ResourceManager.h"
#include "GuiManager.h"
#include "Data_Desktop.h"

class State_MapSelector : public State
{
public:
    State_MapSelector(sf::RenderWindow &mWindow);
    ~State_MapSelector();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;

    std::vector<std::string> mapFiles;
    unsigned int mapCount;
    int scrollAmount;
    sf::Sprite mapBox;
    sf::RectangleShape selectedMapOverlay;
    int selectedMap;

    sf::Text userImput;
    sf::Sprite newMapTile;
    bool isMakingNewMap;
    std::map <int, std::string> options;
    std::map <int, std::string> questions;
    sf::Text optionText;
    std::string answerString;
    unsigned char optionsIterator;
    bool local_createMap();
    bool local_deleteMap();
    int deleteProgress;

    bool keyboard_up;
    bool keyboard_down;

    sf::Sprite background;

    ResourceManager resourceManager;
    GuiManager guiManager;
};

#endif // STATE_MAPSELECTOR_H
