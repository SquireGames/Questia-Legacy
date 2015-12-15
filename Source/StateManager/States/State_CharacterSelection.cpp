#include <iostream>
#include <string>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include "StateManager/States/State_CharacterSelection.h"
#include "StateManager/StateManager.h"
#include "StateManager/States/State_Transition.h"

#define OPTION_SPACING 90

State_CharacterSelection::State_CharacterSelection(sf::RenderWindow &mWindow):
    window(mWindow)
    , resourceManager()
    , guiManager(mWindow, resourceManager, false)
    , guiManager_options(mWindow, resourceManager, false)
    , classManager(false)
    , characterCount(0)
    , keyboard_up(false)
    , keyboard_down(false)
    , isMakingNewCharacter(false)
    , optionsIterator(0)
    , selectedCharacter(-1)
    , deleteProgress (0)

    , selectedClassType(Character::ClassType::none)
{
    background.setTexture(resourceManager.getTexture("Media/Image/Menu/Options.png"));

    characterFiles = Data_Desktop::getInstance().getFiles("Saves/Characters", false);
    characterCount = characterFiles.size();

    guiManager.addButton(1, false, 1700, 1000, std::string("Media/Image/Menu/Buttons/Button_Editor.png"), std::string("Play"), 1760, 1005,1,30, sf::Color::Black, sf::Color(153,153,0,111));
    guiManager.addButton(2, false, 20, 1000, std::string("Media/Image/Menu/Buttons/Button_Editor.png"), std::string("Back"), 80, 1005,1,30, sf::Color::Black, sf::Color(153,153,0,111));
    guiManager.addButton(3, false, 20, 300, std::string("Media/Image/Menu/Buttons/Button_Editor.png"), std::string("New Character"), 30, 308,1,25, sf::Color::Black, sf::Color(153,153,0,111));
    guiManager.addButton(4, false, 20, 500, std::string("Media/Image/Menu/Buttons/Button_Editor.png"), std::string("Delete Character"), 30, 508,1,25, sf::Color::Black, sf::Color(153,153,0,111));

    for(int it = 20; it != characterCount + 20; it++)
    {
        guiManager.addButton(it, false, 385, 100 + (OPTION_SPACING * (it - 20)), std::string("Media/Image/Menu/Buttons/Options_Setting2.png"), characterFiles[it-20], 500, 120 + (OPTION_SPACING * (it - 20)) ,1,35, sf::Color::Black, sf::Color(237,210,103,100));
    }

    selectedCharacterOverlay.setPosition(-1000,-1000);
    selectedCharacterOverlay.setSize(sf::Vector2f(1150, 80));
    selectedCharacterOverlay.setFillColor(sf::Color(192, 192, 192, 100));

    newCharacterTile.setTexture(resourceManager.getTexture(std::string("Media/Image/Menu/Buttons/Options_Setting.png")));
    newCharacterTile.setPosition(385, 100);
    userImput.setFont(Data_Desktop::getInstance().font1);
    userImput.setPosition(850, 120);
    userImput.setCharacterSize(30);
    userImput.setColor(sf::Color::Black);
    optionText.setFont(Data_Desktop::getInstance().font1);
    optionText.setPosition(450, 120);
    optionText.setCharacterSize(30);
    optionText.setColor(sf::Color::Black);

    questions[0] = std::string("Character Name:");
    questions[1] = std::string("Class:");

    //test
    std::cout << classManager.returnCharacterInformation(Character::ClassType::ranger, Character::InformationType::description);
    std::cout << classManager.returnCharacterInformation(Character::ClassType::knight, Character::InformationType::description);

}

State_CharacterSelection::~State_CharacterSelection()
{

}

void State_CharacterSelection::processImput(sf::Keyboard::Key key,bool isPressed)
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

void State_CharacterSelection::update(sf::Time elapsedTime)
{
    if(isMakingNewCharacter)
    {
        int tempIterator = 0;
        for(; tempIterator != questions.size() && optionsIterator != questions.size();)
        {
            optionText.setString(questions[optionsIterator]);
            tempIterator++;
        }
        if(optionsIterator == questions.size())
        {
            if(local_createCharacter())
            {
                characterFiles = Data_Desktop::getInstance().getFiles("Saves/Characters", false);
                characterCount = characterFiles.size();
                for(int it = 20; it!= characterCount+20; it++)
                {
                    guiManager.addButton(it, false, 385, 100 + (OPTION_SPACING * (it - 20)), std::string("Media/Image/Menu/Buttons/Options_Setting2.png"), characterFiles[it-20], 500, 120 + (OPTION_SPACING * (it - 20)) ,1,35, sf::Color::Black, sf::Color(237,210,103,100));
                }
                isMakingNewCharacter = false;
            }
            else
            {
                for(int it = 20; it!= characterCount+20; it++)
                {
                    guiManager.changeVisibility(it, false);
                }
                isMakingNewCharacter = false;
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
        else if(imputChar == 'E') // Enter
        {
            if(optionsIterator == 1)
            {
                if(selectedClassType != Character::ClassType::none)
                {
                    std::string playerClass;

                    switch(selectedClassType)
                    {
                    case Character::ClassType::knight:
                        playerClass = "1";
                        break;
                    case Character::ClassType::ranger:
                        playerClass = "2";
                        break;
                    case Character::ClassType::mage:
                        playerClass = "3";
                        break;
                    }
                    options[optionsIterator] = playerClass;
                    optionsIterator++;
                    answerString = "";
                    userImput.setString(answerString);
                }
            }
            else if(answerString.length() > 0 && answerString.length() < 40)
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
        if(isMakingNewCharacter == false)
        {
            if(guiManager.testButton(1)) // open
            {
                if(Data_Desktop::getInstance().getCharacterSelection() != "NO CHARACTER SELECTED")
                {
                    if(local_loadCharacter())
                    {
                        StateManager::getInstance().changeState(new State_Transition(window, 2));
                    }
                }
            }
            if(guiManager.testButton(2)) // menu
            {
                StateManager::getInstance().changeState(new State_Transition(window, 1));
            }
            else if(guiManager.testButton(3)) // new Character
            {
                for(int it = 20; it!= characterCount+20; it++)
                {
                    guiManager.changeVisibility(it, true);
                }
                selectedCharacterOverlay.setPosition(-1000,-1000);
                isMakingNewCharacter = true;
            }
            else if(guiManager.testButton(4)) // delete Character
            {
                // Click 3 times to delete
                deleteProgress++;
                if(deleteProgress > 2)
                {
                    deleteProgress = 0;
                    for(int it = 20; it!= characterCount+20; it++)
                    {
                        guiManager.deleteButton(it);
                    }
                    if(local_deleteCharacter())
                    {

                    }
                    selectedCharacter = -1;
                    selectedCharacterOverlay.setPosition(-1000,-1000);
                    characterFiles = Data_Desktop::getInstance().getFiles("Saves/Characters", false);
                    characterCount = characterFiles.size();
                    for(int it = 20; it!= characterCount+20; it++)
                    {
                        guiManager.addButton(it, false, 385, 100 + (OPTION_SPACING * (it - 20)), std::string("Media/Image/Menu/Buttons/Options_Setting2.png"), characterFiles[it-20], 500, 120 + (OPTION_SPACING * (it - 20)) ,1,35, sf::Color::Black, sf::Color(237,210,103,100));
                    }
                }
            }
            else
            {
                for(int it = 20; it!= characterCount + 20; it++)
                {
                    if(guiManager.testButton(it))
                    {
                        selectedCharacterOverlay.setPosition(guiManager.getButtonCoords(it).x, guiManager.getButtonCoords(it).y);
                        Data_Desktop::getInstance().setCharacterSelection(characterFiles[it-20]);
                        selectedCharacter = it - 20;
                    }
                }
            }
        }
        else // If not making new character...
        {
            if(guiManager.testButton(2)) // menu
            {
                for(int it = 20; it!= characterCount+20; it++)
                {
                    guiManager.addButton(it, false, 385, 100 + (OPTION_SPACING * (it - 20)), std::string("Media/Image/Menu/Buttons/Options_Setting2.png"), characterFiles[it-20], 500, 120 + (OPTION_SPACING * (it - 20)) ,1,35, sf::Color::Black, sf::Color(237,210,103,100));
                }
                isMakingNewCharacter = false;
                options.clear();
                optionsIterator = 0;
                answerString = "";
                userImput.setString("");
            }
        }
    }
    if(!isMakingNewCharacter)
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
            for(int it = 20; it!= characterCount+20; it++)
            {
                sf::Vector2i tempCoords = guiManager.getButtonCoords(it);
                guiManager.moveSprite(it, tempCoords.x , tempCoords.y + 28);
                if(Data_Desktop::getInstance().getCharacterSelection()== characterFiles[it-20])
                {
                    selectedCharacterOverlay.setPosition(guiManager.getButtonCoords(it).x, guiManager.getButtonCoords(it).y);
                }
            }
            break;
        case -1:
            scrollAmount -= 28;
            for(int it = 20; it!= characterCount+20; it++)
            {
                sf::Vector2i tempCoords = guiManager.getButtonCoords(it);
                guiManager.moveSprite(it, tempCoords.x, tempCoords.y - 28);
                if(Data_Desktop::getInstance().getCharacterSelection() == characterFiles[it-20])
                {
                    selectedCharacterOverlay.setPosition(guiManager.getButtonCoords(it).x, guiManager.getButtonCoords(it).y);
                }
            }
            break;
        }
    }
}

void State_CharacterSelection::displayTextures()
{
    window.draw(background);
    guiManager.buttonCheck();
    guiManager_options.buttonCheck();
    guiManager.drawGui();
    guiManager_options.drawGui();
    window.draw(selectedCharacterOverlay);

    if(isMakingNewCharacter)
    {


        //if(optionsIterator != 1
        //  && optionsIterator != 2)
        {
            window.draw(newCharacterTile);
            window.draw(userImput);
            window.draw(optionText);
        }
    }
}

bool State_CharacterSelection::local_createCharacter()
{
    //std::string skills;
    //std::string inventory;
    //std::string quests;

    std::string fileName_character  = "character";
    std::string fileName_mapInfo    = "mapInfo";
    std::string fileName_tempInfo   = "tempInfo";

    std::string result_name;
    std::string result_mapInfo;
    std::string result_tempInfo;

    std::stringstream ss;
    ss << "Saves/Characters/" << options[0] << "/" << fileName_character << ".txt";
    ss >> result_name;
    std::stringstream ss2;
    ss2 << "Saves/Characters/" << options[0] << "/" << fileName_mapInfo << ".txt";
    ss2 >> result_mapInfo;
    std::stringstream ss3;
    ss3 << "Saves/Characters/" << options[0] << "/" << fileName_tempInfo << ".txt";
    ss3 >> result_tempInfo;

    boost::filesystem::path directory("Saves/Characters/" + options[0]);
    if(!(boost::filesystem::exists(directory)))
    {
        if(boost::filesystem::create_directory(directory))
        {
            std::cout << "Character folder was made: " << options[0] << std::endl;
        }
        else
        {
            std::cout << "Character folder failed to be made: " << options[0] << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "Character already exists!: " << options[0] << std::endl;
        return false;
    }
    switch(std::atoi(options[1].c_str()))
    {
    case 1:
        options[1] = "knight";
        break;
    case 2:
        options[1] = "ranger";
        break;
    case 3:
        options[1] = "mage";
        break;
    }

    std::ofstream characterTxt;
    characterTxt.open(result_name, std::ofstream::out);
    if(characterTxt.is_open())
    {
        characterTxt << "Name:" << options[0] << std::endl;
        characterTxt << "Class:" << options[1] << std::endl;
    }
    else
    {
        return false;
    }

    std::ofstream characterMapInfo;
    characterMapInfo.open(result_mapInfo, std::ofstream::out);
    if(characterMapInfo.is_open())
    {
        characterMapInfo << "Map:" << "Tutorial_1" << std::endl;
        characterMapInfo << "Coordinates_x:" << "800" << std::endl;
        characterMapInfo << "Coordinates_y:" << "2400" << std::endl;
    }
    else
    {
        return false;
    }

    std::ofstream characterTempInfo;
    characterTempInfo.open(result_tempInfo, std::ofstream::out);
    if(characterTempInfo.is_open())
    {
        characterTempInfo << "HP:" << "unassigned" << std::endl;
        characterTempInfo << "SP:" << "unassigned" << std::endl;
        characterTempInfo << "MP:" << "unassigned" << std::endl;
    }
    else
    {
        return false;
    }

    return true;
}

bool State_CharacterSelection::local_deleteCharacter()
{
    if(selectedCharacter != -1)
    {
        boost::filesystem::path directory(("Saves/Characters/" + characterFiles[selectedCharacter]));
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
        std::cout << "No Character selected!" << std::endl;
    }
    return false;
}

bool State_CharacterSelection::local_loadCharacter()
{
    std::stringstream ss;
    ss << "Saves/Characters/" << Data_Desktop::getInstance().getCharacterSelection() << "/mapInfo.txt";
    std::ifstream openFile;
    openFile.open(ss.str());
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
                    for(int x = 1; x < 20; x++)
                    {
                        if(line[it+x] != '(' && line[it+x] != ' ' && line[it+x] != '\0')
                        {
                            sStream << line[it+x];
                        }
                        else
                        {
                            x = 20;
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

        Data_Desktop::getInstance().setMapSelection(optionsVector[0]);
        Data_Desktop::getInstance().setSaved_coordinates_x(optionsVector[1]);
        Data_Desktop::getInstance().setSaved_coordinates_y(optionsVector[2]);

        return true;
    }
    return false;
}


