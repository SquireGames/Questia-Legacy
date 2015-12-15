#ifndef STATE_CHARACTERSELECTION_H
#define STATE_CHARACTERSELECTION_H

#include <SFML/Graphics.hpp>
#include <StateManager/State.h>

#include "ResourceManager.h"
#include "GuiManager.h"
#include "ClassManager.h"
#include "Namespace_Character.h"

class State_CharacterSelection : public State
{
public:
    State_CharacterSelection(sf::RenderWindow &mWindow);
    ~State_CharacterSelection();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;

    sf::Sprite background;

    std::vector<std::string> characterFiles;
    unsigned int characterCount;
    int scrollAmount;
    sf::Sprite mapBox;
    sf::RectangleShape selectedCharacterOverlay;
    int selectedCharacter;

    sf::Text userImput;
    sf::Sprite newCharacterTile;
    bool isMakingNewCharacter;
    std::map <int, std::string> options;
    std::map <int, std::string> questions;
    sf::Text optionText;
    std::string answerString;
    unsigned char optionsIterator;
    bool local_createCharacter();
    bool local_deleteCharacter();
    bool local_loadCharacter();
    int deleteProgress;

    bool keyboard_up;
    bool keyboard_down;

    ResourceManager resourceManager;
    GuiManager guiManager;
    GuiManager guiManager_options;

    ClassManager classManager;

    Character::ClassType selectedClassType;
};

#endif // STATE_CHARACTERSELECTION_H
