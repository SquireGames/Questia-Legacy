#ifndef STATE_OPTIONSMENU_H
#define STATE_OPTIONSMENU_H

#include <SFML/Graphics.hpp>
#include <StateManager/State.h>
#include "ResourceManager.h"
#include "GuiManager.h"

class State_OptionsMenu : public State
{
public:
    State_OptionsMenu(sf::RenderWindow &mWindow);
    ~State_OptionsMenu();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    ResourceManager resourceManager;
    GuiManager guiManager;

    sf::RenderWindow& window;
    enum optionsEnum {display, audio, game, input};
    optionsEnum optionsTab;

    sf::Sprite background;

    sf::Sprite setting;
    sf::Text settingText;

    int scrollAmount_d;
    int scrollAmount_a;
    int scrollAmount_g;
    int scrollAmount_i;

    bool keyboard_up;
    bool keyboard_down;

    std::string checkKeyName(char c);


    /// options
    //display
    int videoMode;
    int fps;
    int font;
    // audio
    int musicVolume;
    int normalVolume;
    //input
    char key_moveUp;
    char key_moveDown;
    char key_moveLeft;
    char key_moveRight;

    char key_skill4;
    char key_skill5;
    char key_skill6;


    ///new options;
    //display
    int newVideoMode;
    int newFps;
    int newFont;
    //audio
    int newMusicVolume;
    int NewNormalVolume;
    //input
    char newKey_moveUp;
    char newKey_moveDown;
    char newKey_moveLeft;
    char newKey_moveRight;

    char newKey_skill4;
    char newKey_skill5;
    char newKey_skill6;
};

#endif // STATE_OPTIONSMENU_H
