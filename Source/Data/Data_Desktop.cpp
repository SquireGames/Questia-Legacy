#include "Data/Data_Desktop.h"

Data_Desktop &Data_Desktop::getInstance()
{
    static Data_Desktop instance;
    return instance;
}

Data_Desktop::Data_Desktop():
    desktopResolution(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height)
    , scaleFactor((float) 1920 / (float) desktopResolution.x, (float) 1080 / (float) desktopResolution.y)
    , FPS (0)
    , mostRecentChar(' ')
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




void Data_Desktop::changeFont(std::string fontName)
{
    if(!font1.loadFromFile(utl::conjoinString({"Media/Fonts/", fontName})))
    {
        font1.loadFromFile("Media/Fonts/acidstructure.ttf");
    }
}




