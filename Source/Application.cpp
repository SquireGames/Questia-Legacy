#include <iostream>

#include "Application.h"

#include "StateManager/StateManager.h"
#include "StateManager/States/State_Transition.h"

#include "Data_Desktop.h"

#include "Utl/Utl.h"

const sf::Time Application::timePerFrame = sf::seconds(1.f/144.f);

Application::Application():
    mStatisticsUpdateTime()
    , mStatisticsFramesCount(0)
    , saveFile()
{
    //temp
    Data_Desktop::getInstance().changeFont(saveFile.getFont());

    switch (saveFile.getWindowMode())
    {
    case 0:
        mWindow.create(sf::VideoMode(1920, 1080),"Questia",sf::Style::Fullscreen);
        break;
    case 1:
        mWindow.create(sf::VideoMode(1280, 720),"Questia",sf::Style::Default);
        break;
    default:
        mWindow.create(sf::VideoMode(1920, 1080),"Questia",sf::Style::Default);
        break;
    }

    std::cout<<"--------------------"<<std::endl;
    std::cout<<"  Questia Executed  "<<std::endl;
    std::cout<<"--------------------"<<std::endl;
}

void Application::run()
{
    Data_Desktop::getInstance().setDesktopResolution(sf::Vector2i(mWindow.getSize().x,mWindow.getSize().y),mWindow.getPosition());

    if(saveFile.getFps() == 0)
    {
        mWindow.setVerticalSyncEnabled(true);
    }
    else if (saveFile.getFps() == -1)
    {
        mWindow.setFramerateLimit(100000);
        mWindow.setVerticalSyncEnabled(false);
    }
    else
    {
        mWindow.setFramerateLimit(saveFile.getFps());
        mWindow.setVerticalSyncEnabled(false);
    }

    sf::View beginningView;
    beginningView.setSize(1920,1080);
    beginningView.setCenter(960,540);
    mWindow.setView(beginningView);

    StateManager::getInstance().createState(new State_Transition(mWindow, 1));

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;

            processEvents();
            update(timePerFrame);
        }
        updateStatistics(elapsedTime);
        render();
    }
}

void Application::processEvents()
{
    sf::Event event;

    while(mWindow.pollEvent(event))
    {
        if(sf::Event::TextEntered == event.type)
        {
            if(event.text.unicode < 128 && event.text.unicode  != 8)
            {
                Data_Desktop::getInstance().setMostRecentChar(event.text.unicode);
            }
            if(event.text.unicode == 67)
            {
                Data_Desktop::getInstance().setMostRecentChar(10);
            }
            else if(event.text.unicode == 83)
            {
                Data_Desktop::getInstance().setMostRecentChar(11);
            }
            else if(event.text.unicode == 65)
            {
                Data_Desktop::getInstance().setMostRecentChar(12);
            }
            else if(event.text.unicode == 84)
            {
                Data_Desktop::getInstance().setMostRecentChar(17);
            }
            else if(event.text.unicode == 66)
            {
                Data_Desktop::getInstance().setMostRecentChar(14);
            }
            else if(event.text.unicode == 95)
            {
                Data_Desktop::getInstance().setMostRecentChar(15);
            }
            else if(event.text.unicode == 69)
            {
                Data_Desktop::getInstance().setMostRecentChar(16);
            }
            else if(event.text.unicode == 13)
            {
                Data_Desktop::getInstance().setMostRecentChar(' ');
            }
            else if(event.text.unicode == 27)
            {
                Data_Desktop::getInstance().setMostRecentChar(' ');
            }
            else if(event.text.unicode == 32)
            {
                Data_Desktop::getInstance().setMostRecentChar('B');
            }

            //std::cout << "input: " << event.text.unicode << std::endl;
        }

        switch(event.type)
        {
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::LControl)
            {
                Data_Desktop::getInstance().setMostRecentChar('C');
            }
            else if(event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift)
            {
                Data_Desktop::getInstance().setMostRecentChar('S');
            }
            else if(event.key.code == sf::Keyboard::LAlt || event.key.code == sf::Keyboard::RAlt)
            {
                Data_Desktop::getInstance().setMostRecentChar('A');
            }
            else if(event.key.code == sf::Keyboard::Tab)
            {
                Data_Desktop::getInstance().setMostRecentChar('T');
            }
            else if(event.key.code == sf::Keyboard::BackSpace)
            {
                Data_Desktop::getInstance().setMostRecentChar('_');
            }
            else if(event.key.code == sf::Keyboard::Up)
            {
                Data_Desktop::getInstance().setMostRecentChar(29);
            }
            else if(event.key.code == sf::Keyboard::Down)
            {
                Data_Desktop::getInstance().setMostRecentChar(30);
            }

            handlePlayerInput (event.key.code,true);
            break;
        case sf::Event::KeyReleased:
            if(event.key.code == sf::Keyboard::Return)
            {
                Data_Desktop::getInstance().setMostRecentChar('E');
            }
            handlePlayerInput (event.key.code,false);
            break;
        case sf::Event::MouseWheelMoved:
            Data_Desktop::getInstance().setMouseWheelDelta(event.mouseWheel.delta);
            // mWindow.close();
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        case sf::Event::Resized:
            Data_Desktop::getInstance().setDesktopResolution(sf::Vector2i(mWindow.getSize().x,mWindow.getSize().y),mWindow.getPosition());
            break;
        case sf::Event::MouseButtonReleased:
            Data_Desktop::getInstance().setMouseReleased(true);
            break;
        case sf::Event::MouseButtonPressed:
            Data_Desktop::getInstance().setMousePressed(true);
            break;
        default:
            break;
        }
    }
}


void Application::handlePlayerInput(sf::Keyboard::Key key,bool isPressed)
{
    StateManager::getInstance().processImputState(key, isPressed);
}

void Application::update(sf::Time elapsedTime)
{
    StateManager::getInstance().updateState(elapsedTime);
}

void Application::updateStatistics(sf::Time elapsedTime)
{
    mStatisticsUpdateTime +=elapsedTime;
    mStatisticsFramesCount += 1;

    if (mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        Data_Desktop::getInstance().set_FPS(mStatisticsFramesCount);

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsFramesCount = 0;
    }
}

void Application::render()
{
    mWindow.clear(sf::Color::White);
    StateManager::getInstance().displayTexturesState();
    mWindow.display();
}

Application::~Application()
{
    StateManager::getInstance().deleteState();
    std::cout<<"--------------------"<<std::endl;
    std::cout<<" Questia Terminated "<<std::endl;
    std::cout<<"--------------------"<<std::endl;
}
