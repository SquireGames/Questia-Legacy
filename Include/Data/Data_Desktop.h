#ifndef DATA_DESKTOP_H
#define DATA_DESKTOP_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <sstream>


class Data_Desktop
{
public:
    Data_Desktop();
    ~Data_Desktop();

    static Data_Desktop &getInstance();

    sf::Vector2f getScaledMousePosition(sf::RenderWindow& window);
    int get_FPS();
    void set_FPS(int f);

    void setDesktopResolution(sf::Vector2i newRes, sf::Vector2i Position);

    // Options
    int loadOptions();
    void writeOptions(int windowMode, int soundVolume, int font, int fps,
                        char moveUpKey, char moveDownKey, char moveLeftKey, char moveRightKey,
                        char skill4Key, char skill5Key, char skill6Key);

    std::vector<std::string> getFiles(std::string directory, bool isWithDirectory);

    void changeFont(int font);
    sf::Font font1;

    int getMusicVolume(){return musicVolume;}
    int getWindowType(){return windowType;}
    int getFont() {return fontType;}
    int getMaxFPS(){return maxFPS;}

    char getCharUp(){return key_moveUp;}
    char getCharDown(){return key_moveDown;}
    char getCharLeft(){return key_moveLeft;}
    char getCharRight(){return key_moveRight;}

    char getCharSkill4(){return key_skill4;}
    char getCharSkill5(){return key_skill5;}
    char getCharSkill6(){return key_skill6;}

    sf::Keyboard::Key getKey(int keyNumber);

    void setMostRecentChar(char c)
    {
        mostRecentChar = c;
    }
    char getMostRecentChar()
    {
        char temp = mostRecentChar;
        mostRecentChar = ' ';
        return temp;
    }

    void setMouseWheelDelta(int delta)
    {
        mouseWheelDelta = delta;
    }
    int getMouseWheelDelta()
    {
        int tempMouseWheelDelta = mouseWheelDelta;
        mouseWheelDelta = 0;
        return tempMouseWheelDelta;
    }




private:
    sf::Vector2i desktopResolution;
    sf::Vector2f scaleFactor;

    int musicVolume;
    int windowType;
    int maxFPS;
    int fontType;

    bool isDebuggerMode;

    //Unimplemented
    int normalVolume;

    int FPS;

    //key binds
    std::map <int, sf::Keyboard::Key> keyMap;
    sf::Keyboard::Key getConvertedKey(char key);

    char key_moveUp;
    char key_moveDown;
    char key_moveLeft;
    char key_moveRight;

    char key_skill4;
    char key_skill5;
    char key_skill6;

    char mostRecentChar;
    int mouseWheelDelta;



    // map selection
public:
    std::string getMapSelection(){return mapSelection;}
    void setMapSelection(std::string newMap){mapSelection = newMap;}
private:
    std::string mapSelection;

    // character info
public:
    void writeGameOptions(sf::Vector2f coordinates);

    std::string getCharacterSelection(){return characterSelection;}
    void setCharacterSelection(std::string newCharacter){characterSelection = newCharacter;}

    std::string getSaved_coordinates_x(){return saved_coordinates_x;}
    void setSaved_coordinates_x(std::string _saved_coordinates_x){saved_coordinates_x = _saved_coordinates_x;}

    std::string getSaved_coordinates_y(){return saved_coordinates_y;}
    void setSaved_coordinates_y(std::string _saved_coordinates_y){saved_coordinates_y = _saved_coordinates_y;}

private:
    std::string characterSelection;
    std::string saved_coordinates_x;
    std::string saved_coordinates_y;
    int saved_hp, saved_mp, saved_st;
};

#endif // DATA_DESKTOP_H
