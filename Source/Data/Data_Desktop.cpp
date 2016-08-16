#include "Data/Data_Desktop.h"
#include <iostream>
#include <SFML/Window/Mouse.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include "Utl/Utl.h"

bool isInDebugMode = false;

Data_Desktop::Data_Desktop():
    save_options("options.cfg")
    , desktopResolution(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height)
    , scaleFactor((float) 1920 / (float) desktopResolution.x, (float) 1080 / (float) desktopResolution.y)
    , FPS (0)
    , mostRecentChar(' ')
    , mapSelection("NO MAP SELECTED")
    , characterSelection("NO CHARACTER SELECTED")

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
    scaleFactor = sf::Vector2f(((float) 1920 / (float) desktopResolution.x), ((float) 1080 / (float) desktopResolution.y));
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

void Data_Desktop::loadOptions()
{
    if(!save_options.readFile()) // New save
    {
        save_options.clearSave();
        save_options.saveItem("window mode",0);
        save_options.saveItem("FPS cap",0);
        save_options.saveItem("music volume",0);
        save_options.saveItem("font",1);
        save_options.saveItem("key_moveUp",    'w');
        save_options.saveItem("key_moveDown",  's');
        save_options.saveItem("key_moveLeft",  'a');
        save_options.saveItem("key_moveRight", 'd');
        save_options.saveItem("key_skill4",    'S');
        save_options.saveItem("key_skill5",    'A');
        save_options.saveItem("key_skill6",    'B');
        save_options.writeFile();
    }


    keyMap[0] = getConvertedKey(save_options.getItem("key_moveUp").at(0));
    keyMap[1] = getConvertedKey(save_options.getItem("key_moveDown").at(0));
    keyMap[2] = getConvertedKey(save_options.getItem("key_moveLeft").at(0));
    keyMap[3] = getConvertedKey(save_options.getItem("key_moveRight").at(0));
    keyMap[4] = getConvertedKey(save_options.getItem("key_skill4").at(0));
    keyMap[5] = getConvertedKey(save_options.getItem("key_skill5").at(0));
    keyMap[6] = getConvertedKey(save_options.getItem("key_skill6").at(0));
}

void Data_Desktop::writeOptions(int windowMode, int fps, int soundVolume, int font,
                                char moveUpKey, char moveDownKey, char moveLeftKey, char moveRightKey,
                                char skill4Key, char skill5Key, char skill6Key)
{

    save_options.saveItem("window mode",   windowMode);
    save_options.saveItem("FPS cap",       fps);
    save_options.saveItem("music volume",  soundVolume);
    save_options.saveItem("font",          font);
    save_options.saveItem("key_moveUp",    moveUpKey);
    save_options.saveItem("key_moveDown",  moveDownKey);
    save_options.saveItem("key_moveLeft",  moveLeftKey);
    save_options.saveItem("key_moveRight", moveRightKey);
    save_options.saveItem("key_skill4",    skill4Key);
    save_options.saveItem("key_skill5",    skill5Key);
    save_options.saveItem("key_skill6",    skill6Key);
    save_options.writeFile();

    keyMap[0] = getConvertedKey(moveUpKey);
    keyMap[1] = getConvertedKey(moveDownKey);
    keyMap[2] = getConvertedKey(moveLeftKey);
    keyMap[3] = getConvertedKey(moveRightKey);

    keyMap[4] = getConvertedKey(skill4Key);
    keyMap[5] = getConvertedKey(skill5Key);
    keyMap[6] = getConvertedKey(skill6Key);
}

void Data_Desktop::changeFont(std::string fontName)
{
    if(!font1.loadFromFile(utl::conjoinString({"Media/Fonts/", fontName})))
    {
        font1.loadFromFile("Media/Fonts/acidstructure.ttf");
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
    default:
        return sf::Keyboard::Unknown;
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


