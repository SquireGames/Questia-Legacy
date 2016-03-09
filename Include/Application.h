#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>

#include "Data_Desktop.h"
#include "Data/SaveFile.h"

class Application
{
public:
    Application();
    ~Application();
    void run();

private:
    void handlePlayerInput(sf::Keyboard::Key key,bool isPressed);
    void processEvents();
    void update(sf::Time elapsedTime);
    void updateStatistics(sf::Time elapsedTime);
    void render();

    sf::RenderWindow mWindow;

    static const sf::Time timePerFrame;
    sf::Time mStatisticsUpdateTime;
    int mStatisticsFramesCount;

    SaveFile save_options;
};

#endif // APPLICATION_H
