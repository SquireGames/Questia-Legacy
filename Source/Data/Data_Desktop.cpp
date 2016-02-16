#include "Data/Data_Desktop.h"
#include <iostream>
#include <SFML/Window/Mouse.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>


Data_Desktop::Data_Desktop():
    desktopResolution(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height)
    , scaleFactor((float) 1920 / (float) desktopResolution.x, (float) 1080 / (float) desktopResolution.y)
    , FPS (0)
    , mostRecentChar(' ')
    , mapSelection("NO MAP SELECTED")
    , characterSelection("NO CHARACTER SELECTED")
    , isDebuggerMode(false)
{
    std::cout<<std::endl;
    std::cout<<"DEBUG: Data_Desktop Initialized"<<std::endl;
    std::cout<<"DEBUG: Res.x: " << (float) desktopResolution.x << ", Res.y: " << (float) desktopResolution.y<<std::endl;
}

Data_Desktop::~Data_Desktop()
{
    std::cout<<"DEBUG: Data_Desktop destroyed"<<std::endl;
}

int Data_Desktop::get_FPS()
{
    return FPS;
}

///This Needed for resized screen
sf::Vector2f Data_Desktop::getScaledMousePosition(sf::RenderWindow& window)
{
    sf::Vector2f mousePosition((float)sf::Mouse::getPosition(window).x * scaleFactor.x, (float)sf::Mouse::getPosition(window).y * scaleFactor.y);
    return mousePosition;
}

void Data_Desktop::set_FPS(int f)
{
    FPS = f;
}

void Data_Desktop::setDesktopResolution(sf::Vector2i newRes, sf::Vector2i Position)
{
    desktopResolution = newRes;
    scaleFactor = sf::Vector2f(((float) 1920 / (float) desktopResolution.x) , ((float) 1080 / (float) desktopResolution.y));
}

Data_Desktop &Data_Desktop::getInstance()
{
    static Data_Desktop instance;
    return instance;
}

std::vector<std::string> Data_Desktop::getFiles(std::string directory, bool isWithDirectory)
{
    std::vector <std::string> fileNames;
    boost::filesystem::path directoryFolder {directory};
    if(boost::filesystem::exists(directoryFolder))
    {
        if(boost::filesystem::is_directory(directoryFolder))
        {
            for(boost::filesystem::directory_entry& x: boost::filesystem::directory_iterator(directoryFolder))
            {
                std::stringstream ss;
                std::string st;
                if(isWithDirectory)
                {
                    ss<<x.path().string();
                }
                else
                {
                    ss<<x.path().filename().string();
                }
                ss>>st;
                fileNames.push_back(st);
            }
        }
    }
    return fileNames;
}

int Data_Desktop::loadOptions()
{
    std::string config("options.cfg");
    std::ifstream openFile;
    openFile.open(config);
    if(openFile.is_open() && openFile.good())
    {

        std::stringstream sStream;
        std::map <int, std::string> optionsVector;
        int level = 0;

        while(!openFile.eof())
        {
            char line[200];
            for(int y = 0; y!= 200; y++)
            {
                line[y] = ' ';
            }
            openFile.getline(line, 200);
            int it = 0;

            for(it; it != 200; it++)
            {
                if(line[it] == ':')
                {
                    for(int x = 1; x < 10; x++)
                    {
                        if(line[it+x] != '(' &&line[it+x] != ' ')
                        {
                            sStream << line[it+x];
                        }
                        else
                        {
                            x = 10;
                        }
                    }
                    std::string optionString;
                    sStream >> optionString;
                    optionsVector[level] = optionString;
                    it = 199;
                    sStream.clear();
                }
            }
            level++;
        }

        std::cout<< "Window mode:  " << optionsVector[0] << std::endl << "Sound mode:  " << optionsVector[1] << std::endl;

        windowType = std::atoi(optionsVector[0].c_str());
        maxFPS = std::atoi(optionsVector[1].c_str());
        musicVolume = std::atoi(optionsVector[2].c_str());
        fontType = std::atoi(optionsVector[3].c_str());

        keyMap[0] = getConvertedKey(optionsVector[5].at(0));
        keyMap[1] = getConvertedKey(optionsVector[6].at(0));
        keyMap[2] = getConvertedKey(optionsVector[7].at(0));
        keyMap[3] = getConvertedKey(optionsVector[8].at(0));

        keyMap[4] = getConvertedKey(optionsVector[9].at(0));
        keyMap[5] = getConvertedKey(optionsVector[10].at(0));
        keyMap[6] = getConvertedKey(optionsVector[11].at(0));


        key_moveUp = optionsVector[5].at(0);
        key_moveDown = optionsVector[6].at(0);
        key_moveLeft = optionsVector[7].at(0);
        key_moveRight = optionsVector[8].at(0);

        key_skill4 = optionsVector[9].at(0);
        key_skill5 = optionsVector[10].at(0);
        key_skill6 = optionsVector[11].at(0);

        changeFont(fontType);

        switch(std::atoi(optionsVector[0].c_str()))
        {
        case 0:
            return 0;
            break;
        case 1:
            return 1;
            break;
        default:
            break;
        }
    }
    writeOptions(0, 0, 50, 1, 'w', 's', 'a', 'd', 'S', 'A', 'B');
    font1.loadFromFile("Media/Fonts/Lato-Medium.ttf");
    return 0;
}

void Data_Desktop::writeOptions(int windowMode, int fps, int soundVolume, int font,
                                char moveUpKey, char moveDownKey, char moveLeftKey, char moveRightKey,
                                char skill4Key, char skill5Key, char skill6Key)
{
    std::string config("options.cfg");
    std::ofstream newConfig;
    newConfig.open(config, std::ofstream::out);
    newConfig << "windowMode:"<< windowMode <<" (0 - Fullscreen, 1 - Windowed)" << std::endl;
    newConfig << "fps:"<< fps <<" (0 - V-Sync, 1+ - FPS Max)" << std::endl;
    newConfig << "sound:"<< soundVolume <<" (Percent)" << std::endl;
    newConfig << "font:"<< font <<" (0 - default.ttf, 1+ - in game fonts)" << std::endl;

    newConfig << std::endl;

    newConfig << "key_moveUp:" << moveUpKey << " (key)"<< std::endl;
    newConfig << "key_moveDown:" << moveDownKey << " (key)"<< std::endl;
    newConfig << "key_moveLeft:" << moveLeftKey << " (key)"<< std::endl;
    newConfig << "key_moveRight:" << moveRightKey << " (key)"<< std::endl;

    newConfig << "key_skill4:" << skill4Key << " (key)"<< std::endl;
    newConfig << "key_skill5:" << skill5Key << " (key)"<< std::endl;
    newConfig << "key_skill6:" << skill6Key << " (key)"<< std::endl;

    musicVolume = soundVolume;
    windowType = windowMode;
    maxFPS = fps;
    fontType = font;

    key_moveUp = moveUpKey;
    key_moveDown = moveDownKey;
    key_moveLeft = moveLeftKey;
    key_moveRight = moveRightKey;

    key_skill4 = skill4Key;
    key_skill5 = skill5Key;
    key_skill6 = skill6Key;

    keyMap[0] = getConvertedKey(moveUpKey);
    keyMap[1] = getConvertedKey(moveDownKey);
    keyMap[2] = getConvertedKey(moveLeftKey);
    keyMap[3] = getConvertedKey(moveRightKey);

    keyMap[4] = getConvertedKey(skill4Key);
    keyMap[5] = getConvertedKey(skill5Key);
    keyMap[6] = getConvertedKey(skill6Key);
}

void Data_Desktop::changeFont(int font)
{
    switch(font)
    {
    case 0:
        font1.loadFromFile("Media/Fonts/default.ttf");
        break;
    case 1:
        font1.loadFromFile("Media/Fonts/Lato-Medium.ttf");
        break;
    case 2:
        font1.loadFromFile("Media/Fonts/Lato-Regular.ttf");
        break;
    case 3:
        font1.loadFromFile("Media/Fonts/acidstructure.ttf");
        break;
    }
}

sf::Keyboard::Key Data_Desktop::getConvertedKey(char key)
{
    switch (key)
    {
    case 'a' :
        return sf::Keyboard::A;
    case 'b' :
        return sf::Keyboard::B;
    case 'c' :
        return sf::Keyboard::C;
    case 'd':
        return sf::Keyboard::D;
    case 'e':
        return sf::Keyboard::E;
    case 'f':
        return sf::Keyboard::F;
    case 'g':
        return sf::Keyboard::G;
    case 'h':
        return sf::Keyboard::H;
    case 'i':
        return sf::Keyboard::I;
    case 'j':
        return sf::Keyboard::J;
    case 'k':
        return sf::Keyboard::K;
    case 'l':
        return sf::Keyboard::L;
    case 'm':
        return sf::Keyboard::M;
    case 'n':
        return sf::Keyboard::N;
    case 'o':
        return sf::Keyboard::O;
    case 'p':
        return sf::Keyboard::P;
    case 'q':
        return sf::Keyboard::Q;
    case 'r':
        return sf::Keyboard::R;
    case 's':
        return sf::Keyboard::S;
    case 't':
        return sf::Keyboard::T;
    case 'u':
        return sf::Keyboard::U;
    case 'v':
        return sf::Keyboard::V;
    case 'w':
        return sf::Keyboard::W;
    case 'x':
        return sf::Keyboard::X;
    case 'y':
        return sf::Keyboard::Y;
    case 'z':
        return sf::Keyboard::Z;
    case '0':
        return sf::Keyboard::Num0;
    case '1':
        return sf::Keyboard::Num1;
    case '2':
        return sf::Keyboard::Num2;
    case '3':
        return sf::Keyboard::Num3;
    case '4':
        return sf::Keyboard::Num4;
    case '5':
        return sf::Keyboard::Num5;
    case '6':
        return sf::Keyboard::Num6;
    case '7':
        return sf::Keyboard::Num7;
    case '8':
        return sf::Keyboard::Num8;
    case '9':
        return sf::Keyboard::Num9;
    case ',':
        return sf::Keyboard::Comma;
    case '.':
        return sf::Keyboard::Period;
    case '/':
        return sf::Keyboard::Slash;
    case ';':
        return sf::Keyboard::SemiColon;
    case '[':
        return sf::Keyboard::LBracket;
    case ']':
        return sf::Keyboard::RBracket;
    case '\\':
        return sf::Keyboard::BackSlash;
    case '-':
        return sf::Keyboard::Dash;
    case '+':
        return sf::Keyboard::Add;
    case '`':
        return sf::Keyboard::Tilde;

    case 'C':
        return sf::Keyboard::LControl;
    case 'S':
        return sf::Keyboard::LShift;
    case 'A':
        return sf::Keyboard::LAlt;
    case 'T':
        return sf::Keyboard::Tab;
    case 'B':
        return sf::Keyboard::Space;
    case '_':
        return sf::Keyboard::BackSpace;
    case 'E':
        return sf::Keyboard::Return;
    }
}

sf::Keyboard::Key Data_Desktop::getKey(int keyNumber)
{
    return keyMap[keyNumber];
}

void Data_Desktop::writeGameOptions(sf::Vector2f coordinates)
{
    std::string fileName_mapInfo    = "mapInfo";
    std::string result_mapInfo;
    std::stringstream ss2;
    ss2 << "Saves/Characters/" << characterSelection << "/" << fileName_mapInfo << ".txt";
    ss2 >> result_mapInfo;

    std::ofstream characterMapInfo;
    characterMapInfo.open(result_mapInfo, std::ofstream::out);
    if(characterMapInfo.is_open())
    {
        characterMapInfo << "Map:" << "Tutorial_1" << std::endl;
        characterMapInfo << "Coordinates_x:" << (int) coordinates.x << std::endl;
        characterMapInfo << "Coordinates_y:" << (int) coordinates.y << std::endl;
    }
}


