#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <boost/filesystem.hpp>

#include "StateManager/States/State_MapSelector.h"
#include "StateManager/States/State_Transition.h"
#include "StateManager/StateManager.h"

#define OPTION_SPACING 90

State_MapSelector::State_MapSelector(sf::RenderWindow &mWindow):
    window(mWindow)
    , resourceManager()
    , guiManager(mWindow, resourceManager, false)
    , mapCount(0)
    , keyboard_up(false)
    , keyboard_down(false)
    , isMakingNewMap(false)
    , optionsIterator(0)
    , selectedMap(-1)
    , deleteProgress (0)
{
    background.setTexture(resourceManager.getTexture("Media/Image/Menu/Options.png"));
    mapFiles = Data_Desktop::getInstance().getFiles("Maps", false);
    mapCount = mapFiles.size();

    guiManager.addButton(1, false, 1700, 1000, std::string("Media/Image/Menu/Buttons/Button_Editor.png"), std::string("Open"), 1760, 1005,1,30, sf::Color::Black, sf::Color(153,153,0,111));
    guiManager.addButton(2, false, 20, 1000, std::string("Media/Image/Menu/Buttons/Button_Editor.png"), std::string("Back"), 80, 1005,1,30, sf::Color::Black, sf::Color(153,153,0,111));
    guiManager.addButton(3, false, 20, 300, std::string("Media/Image/Menu/Buttons/Button_Editor.png"), std::string("New Map"), 50, 305,1,30, sf::Color::Black, sf::Color(153,153,0,111));
    guiManager.addButton(4, false, 20, 500, std::string("Media/Image/Menu/Buttons/Button_Editor.png"), std::string("Delete Map"), 40, 505,1,30, sf::Color::Black, sf::Color(153,153,0,111));

    for(int it = 20; it!= mapCount+20; it++)
    {
        guiManager.addButton(it, false, 385, 100 + (OPTION_SPACING * (it - 20)), std::string("Media/Image/Menu/Buttons/Options_Setting2.png"), mapFiles[it-20], 500, 120 + (OPTION_SPACING * (it - 20)) ,1,35, sf::Color::Black, sf::Color(237,210,103,100));
    }

    selectedMapOverlay.setPosition(-1000,-1000);
    selectedMapOverlay.setSize(sf::Vector2f(1150, 80));
    selectedMapOverlay.setFillColor(sf::Color(192, 192, 192, 100));

    newMapTile.setTexture(resourceManager.getTexture(std::string("Media/Image/Menu/Buttons/Options_Setting.png")));
    newMapTile.setPosition(385, 100);
    userImput.setFont(Data_Desktop::getInstance().font1);
    userImput.setPosition(850, 120);
    userImput.setCharacterSize(30);
    userImput.setColor(sf::Color::Black);
    optionText.setFont(Data_Desktop::getInstance().font1);
    optionText.setPosition(500, 120);
    optionText.setCharacterSize(30);
    optionText.setColor(sf::Color::Black);

    questions[0] = std::string("Map Name:");
    questions[1] = std::string("Map Length:");
    questions[2] = std::string("Map Height:");
}

State_MapSelector::~State_MapSelector()
{

}

void State_MapSelector::processImput(sf::Keyboard::Key key,bool isPressed)
{
    if(key == sf::Keyboard::Up || key == sf::Keyboard::W)
    {
        if(isPressed)
        {
            keyboard_up = true;
        }
        else
        {
            keyboard_up = false;
        }
    }
    else if(key == sf::Keyboard::Down || key == sf::Keyboard::S)
    {
        if(isPressed)
        {
            keyboard_down = true;
        }
        else
        {
            keyboard_down = false;
        }
    }
}

void State_MapSelector::update(sf::Time elapsedTime)
{
    if(isMakingNewMap)
    {
        int tempIterator = 0;
        for(; tempIterator != questions.size() && optionsIterator != questions.size();)
        {
            optionText.setString(questions[optionsIterator]);
            tempIterator++;
        }
        if(optionsIterator == questions.size())
        {
            if(local_createMap())
            {
                mapFiles = Data_Desktop::getInstance().getFiles("Maps", false);
                mapCount = mapFiles.size();
                for(int it = 20; it!= mapCount+20; it++)
                {
                    guiManager.addButton(it, false, 385, 100 + (OPTION_SPACING * (it - 20)), std::string("Media/Image/Menu/Buttons/Options_Setting2.png"), mapFiles[it-20], 500, 120 + (OPTION_SPACING * (it - 20)) ,1,35, sf::Color::Black, sf::Color(237,210,103,100));
                }
                isMakingNewMap = false;
            }
            else
            {
                for(int it = 20; it!= mapCount+20; it++)
                {
                    guiManager.changeVisibility(it, false);
                }
                isMakingNewMap = false;
            }
            options.clear();
            optionsIterator = 0;
        }
        char imputChar = Data_Desktop::getInstance().getMostRecentChar();
        if(imputChar != ' ' && imputChar != 'S' && imputChar !='E')
        {
            std::stringstream ss;
            if(imputChar == '_')// backspace
            {
                if(answerString.length() > 0)
                {
                    answerString.erase(answerString.size() - 1, 1);
                }
                userImput.setString(answerString);
            }
            else
            {
                bool isGood = true;
                if(imputChar == 10)
                {
                    imputChar = 'C';
                }
                else if(imputChar == 11)
                {
                    imputChar = 'S';
                }
                else if(imputChar == 12)
                {
                    imputChar = 'A';
                }
                else if(imputChar == 17)
                {
                    imputChar = 'T';
                }
                else if(imputChar == 14)
                {
                    imputChar = 'B';
                }
                else if(imputChar == 15)
                {
                    imputChar = '_';
                }
                else if(imputChar == 16)
                {
                    imputChar = 'E';
                }
                else if(imputChar == 'B')
                {
                    imputChar = ' ';
                }


                ss << answerString;
                if(isGood)
                {
                    ss << imputChar;
                }
                ss >> answerString;

                userImput.setString(answerString);
                ss.clear();
            }
            userImput.setColor(sf::Color::Black);
        }
        else if(imputChar == 'E')
        {
            if(answerString.length() > 0 && answerString.length() < 40)
            {
                if(optionsIterator == 1 || optionsIterator == 2)
                {
                    if(std::atoi(answerString.c_str()) > 1 && std::atoi(answerString.c_str()) < 400)
                    {
                        options[optionsIterator] = answerString;
                        optionsIterator++;
                        answerString = "";
                        userImput.setString(answerString);
                        userImput.setColor(sf::Color::Black);
                    }
                    else
                    {
                        userImput.setColor(sf::Color::Red);
                        userImput.setString(answerString);
                    }
                }
                else
                {
                    options[optionsIterator] = answerString;
                    optionsIterator++;
                    answerString = "";
                    userImput.setString(answerString);
                    userImput.setColor(sf::Color::Black);
                }
            }
            else
            {
                userImput.setColor(sf::Color::Red);
                userImput.setString(answerString);
            }
        }
        guiManager.changeVisibility(1, true);
        guiManager.changeVisibility(3, true);
        guiManager.changeVisibility(4, true);
    }
    else
    {
        guiManager.changeVisibility(1, false);
        guiManager.changeVisibility(3, false);
        guiManager.changeVisibility(4, false);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(guiManager.testButton(1)) // open
        {
            if(Data_Desktop::getInstance().getMapSelection() != "NO MAP SELECTED")
            {
                StateManager::getInstance().changeState(new State_Transition(window, 5));
            }
        }
        else if(guiManager.testButton(2)) // menu
        {
            StateManager::getInstance().changeState(new State_Transition(window, 1));
        }
        else if(guiManager.testButton(3)) // new Map
        {
            for(int it = 20; it!= mapCount+20; it++)
            {
                guiManager.changeVisibility(it, true);
            }
            isMakingNewMap = true;
        }
        else if(guiManager.testButton(4)) // delete Map
        {
            deleteProgress++;
            if(deleteProgress > 2)
            {
                deleteProgress = 0;
                for(int it = 20; it!= mapCount+20; it++)
                {
                    guiManager.deleteButton(it);
                }
                if(local_deleteMap())
                {

                }
                selectedMap = -1;
                selectedMapOverlay.setPosition(-1000,-1000);
                mapFiles = Data_Desktop::getInstance().getFiles("Maps", false);
                mapCount = mapFiles.size();
                for(int it = 20; it!= mapCount+20; it++)
                {
                    guiManager.addButton(it, false, 385, 100 + (OPTION_SPACING * (it - 20)), std::string("Media/Image/Menu/Buttons/Options_Setting2.png"), mapFiles[it-20], 500, 120 + (OPTION_SPACING * (it - 20)) ,1,35, sf::Color::Black, sf::Color(237,210,103,100));
                }
            }
        }
        else
        {
            for(int it = 20; it!= mapCount+20; it++)
            {
                if(guiManager.testButton(it))
                {
                    selectedMapOverlay.setPosition(guiManager.getButtonCoords(it).x, guiManager.getButtonCoords(it).y);
                    Data_Desktop::getInstance().setMapSelection(mapFiles[it-20]);
                    selectedMap = it - 20;
                }
            }
        }
    }
    if(!isMakingNewMap)
    {
scrollSelector:
        switch (Data_Desktop::getInstance().getMouseWheelDelta())
        {
        case 0:
            if(keyboard_up == true)
            {
                Data_Desktop::getInstance().setMouseWheelDelta(1);
            }
            else if(keyboard_down == true)
            {
                Data_Desktop::getInstance().setMouseWheelDelta(-1);
            }
            else
            {
                break;
            }
            goto scrollSelector;
        case 1:
            scrollAmount += 28;
            for(int it = 20; it!= mapCount+20; it++)
            {
                sf::Vector2i tempCoords = guiManager.getButtonCoords(it);
                guiManager.moveSprite(it, tempCoords.x , tempCoords.y + 28);
                if(Data_Desktop::getInstance().getMapSelection()== mapFiles[it-20])
                {
                    selectedMapOverlay.setPosition(guiManager.getButtonCoords(it).x, guiManager.getButtonCoords(it).y);
                }
            }
            break;
        case -1:
            scrollAmount -= 28;
            for(int it = 20; it!= mapCount+20; it++)
            {
                sf::Vector2i tempCoords = guiManager.getButtonCoords(it);
                guiManager.moveSprite(it, tempCoords.x, tempCoords.y - 28);
                if(Data_Desktop::getInstance().getMapSelection() == mapFiles[it-20])
                {
                    selectedMapOverlay.setPosition(guiManager.getButtonCoords(it).x, guiManager.getButtonCoords(it).y);
                }
            }
            break;
        }
    }
}

void State_MapSelector::displayTextures()
{
    window.draw(background);
    guiManager.buttonCheck();
    guiManager.drawGui();
    window.draw(selectedMapOverlay);

    if(isMakingNewMap)
    {
        window.draw(newMapTile);
        window.draw(userImput);
        window.draw(optionText);
    }
}

bool State_MapSelector::local_createMap()
{
    std::string mapName;
    mapName = "map_0";
    std::string mapName2;
    mapName2 = "map_1";
    std::string spawnTxt;
    spawnTxt = "spawn";
    std::string tilesTxt;
    tilesTxt = "tiles";
    std::string result;
    std::string result2;
    std::stringstream ss;
    ss << "Maps/" << options[0] << "/" << mapName << ".txt";
    ss >> result;
    ss.clear();
    ss << "Maps/" <<options[0] << "/" << mapName2 << ".txt";
    ss >> result2;
    ss.clear();
    ss << "Maps/" <<options[0] << "/" << spawnTxt << ".txt";
    ss >> spawnTxt;
    ss.clear();
    ss << "Maps/" <<options[0] << "/" << tilesTxt << ".txt";
    ss >> tilesTxt;

    boost::filesystem::path directory("Maps/" + options[0]);
    if(!(boost::filesystem::exists(directory)))
    {
        if(boost::filesystem::create_directory(directory))
        {
            std::cout << "Map folder was made: " << options[0] << std::endl;
        }
        else
        {
            std::cout << "Map folder failed to be made: " << options[0] << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "Map already exists!: " << options[0] << std::endl;
        return false;
    }

    std::ofstream newMap;
    newMap.open(result, std::ofstream::out);
    if(newMap.is_open())
    {
        newMap << std::endl;
        for (int x=0; x < std::atoi(options[2].c_str()); x++)
        {
            if(x!=0)
            {
                newMap << std::endl;
            }
            for (int y=0; y < std::atoi(options[1].c_str()); y++)
            {
                newMap << "1,1|";
            }
        }

        std::ofstream newMap2;
        newMap2.open(result2, std::ofstream::out);
        if(newMap2.is_open())
        {
            newMap2 << std::endl;
            for (int x=0; x <std::atoi(options[2].c_str()); x++)
            {
                if(x!=0)
                {
                    newMap2 << std::endl;
                }
                for (int y=0; y < std::atoi(options[1].c_str()); y++)
                {
                    newMap2 << "0,0|";
                }
            }

            std::ofstream newSpawn;
            newSpawn.open(spawnTxt, std::ofstream::out);
            if(newSpawn.is_open())
            {
                std::ofstream newTiles;
                newTiles.open(tilesTxt, std::ofstream::out);
                if(newTiles.is_open())
                {
                    newTiles << "1,1";
                    std::cout << "Map was made: "<< options[0] << std::endl;
                    return true;
                }
            }
        }
        else
        {
            std::cout << "failed to make map2" << std::endl;
        }
    }
    else
    {
        std::cout << "failed to make map" << std::endl;
    }
    return false;
}

bool State_MapSelector::local_deleteMap()
{
    if(selectedMap != -1)
    {
        boost::filesystem::path directory(("Maps/" + mapFiles[selectedMap]));
        if((boost::filesystem::exists(directory)))
        {
            if((boost::filesystem::remove_all(directory)))
            {
                std::cout << "Directory Deleted: " <<  directory.string() << std::endl;
                return true;
            }
            else
            {
                std::cout << "Failed to delete directory: " <<  directory.string() << std::endl;
            }
        }
        else
        {
            std::cout << "Directory does not exist: " << directory.string() << std::endl;
        }
    }
    else
    {
        std::cout << "No map selected!" << std::endl;
    }
    return false;
}

