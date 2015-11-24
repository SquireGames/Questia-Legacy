#include <iostream>
#include <sstream>

#include "StateManager/States/State_OptionsMenu.h"
#include "StateManager/StateManager.h"
#include "StateManager/States/State_Transition.h"

State_OptionsMenu::State_OptionsMenu(sf::RenderWindow &mWindow):
    window(mWindow)
    , resourceManager()
    , optionsTab(display)
    , guiManager(mWindow, resourceManager, false)

    , scrollAmount_d(0)
    , scrollAmount_a(0)
    , scrollAmount_g(0)
    , scrollAmount_i(0)

    , keyboard_up(false)
    , keyboard_down(false)

    , videoMode(Data_Desktop::getInstance().getWindowType())
    , font(Data_Desktop::getInstance().getFont())
    , musicVolume(Data_Desktop::getInstance().getMusicVolume())
    , fps(Data_Desktop::getInstance().getMaxFPS())

    , key_moveUp(Data_Desktop::getInstance().getCharUp())
    , key_moveDown(Data_Desktop::getInstance().getCharDown())
    , key_moveLeft(Data_Desktop::getInstance().getCharLeft())
    , key_moveRight(Data_Desktop::getInstance().getCharRight())
    , key_skill4(Data_Desktop::getInstance().getCharSkill4())
    , key_skill5(Data_Desktop::getInstance().getCharSkill5())
    , key_skill6(Data_Desktop::getInstance().getCharSkill6())

    , newVideoMode(videoMode)
    , newFont(font)
    , newMusicVolume (musicVolume)
    , newFps(fps)

    , newKey_moveUp(key_moveUp)
    , newKey_moveDown(key_moveDown)
    , newKey_moveLeft(key_moveLeft)
    , newKey_moveRight(key_moveRight)
    , newKey_skill4(key_skill4)
    , newKey_skill5(key_skill5)
    , newKey_skill6(key_skill6)
{
    background.setTexture(resourceManager.getTexture("Media/Image/Menu/Options.png"));
    setting.setTexture(resourceManager.getTexture("Media/Image/Menu/Buttons/Options_Setting.png"));

    settingText.setFont(Data_Desktop::getInstance().font1);
    settingText.setCharacterSize(30);
    settingText.setColor(sf::Color::Black);

    guiManager.addButton(2000, false, 78, 45, std::string("Media/Image/Menu/Buttons/Options_Tab.png"), std::string("Display"), 205,53,1,50, sf::Color::Black, sf::Color(153,153,0,111));
    guiManager.addButton(2001, false, 528, 45, std::string("Media/Image/Menu/Buttons/Options_Tab.png"), std::string("Audio"),  675,53,1,50, sf::Color::Black, sf::Color(153,153,0,111));
    guiManager.addButton(2002, false, 978, 45, std::string("Media/Image/Menu/Buttons/Options_Tab.png"), std::string("Game"),   1130,53,1,50, sf::Color::Black, sf::Color(153,153,0,111));
    guiManager.addButton(2003, false, 1428, 45, std::string("Media/Image/Menu/Buttons/Options_Tab.png"), std::string("Input"), 1580,53,1,50, sf::Color::Black, sf::Color(153,153,0,111));

    // Window mode
    guiManager.addButton(5, true, 800, 260, std::string("Media/Image/Menu/Buttons/Options_Arrow.png"), std::string(""), 205,53,1,50, sf::Color::Transparent, sf::Color(153,153,0,0));
    guiManager.rotateSprite(5, 180);
    guiManager.addButton(6, true, 1400, 260, std::string("Media/Image/Menu/Buttons/Options_Arrow.png"), std::string(""), 205,53,1,50, sf::Color::Transparent, sf::Color(153,153,0,0));
    // FPS
    guiManager.addButton(7, true, 800, 360, std::string("Media/Image/Menu/Buttons/Options_Arrow.png"), std::string(""), 205,53,1,50, sf::Color::Transparent, sf::Color(153,153,0,0));
    guiManager.rotateSprite(7, 180);
    guiManager.addButton(8, true, 1400, 360, std::string("Media/Image/Menu/Buttons/Options_Arrow.png"), std::string(""), 205,53,1,50, sf::Color::Transparent, sf::Color(153,153,0,0));
    //Font
    guiManager.addButton(9, true, 800, 460, std::string("Media/Image/Menu/Buttons/Options_Arrow.png"), std::string(""), 205,53,1,50, sf::Color::Transparent, sf::Color(153,153,0,0));
    guiManager.rotateSprite(9, 180);
    guiManager.addButton(10, true, 1400, 460, std::string("Media/Image/Menu/Buttons/Options_Arrow.png"), std::string(""), 205,53,1,50, sf::Color::Transparent, sf::Color(153,153,0,0));


    //Music volume
    guiManager.addButton(20, true, 800, 260, std::string("Media/Image/Menu/Buttons/Options_Arrow.png"), std::string(""), 205,53,1,50, sf::Color::Transparent, sf::Color(153,153,0,0));
    guiManager.rotateSprite(20, 180);
    guiManager.addButton(21, true, 1400, 260, std::string("Media/Image/Menu/Buttons/Options_Arrow.png"), std::string(""), 205,53,1,50, sf::Color::Transparent, sf::Color(153,153,0,0));


    //Key binding up down left right
    guiManager.addButton(1000, true, 910, 265, std::string("Media/Image/Menu/Buttons/Options_Button_a.png"), std::string(""), 800, 260 ,1,50, sf::Color::Black, sf::Color(237,210,103,0));
    guiManager.addButton(1001, true, 910, 365, std::string("Media/Image/Menu/Buttons/Options_Button_a.png"), std::string(""), 800, 260 ,1,50, sf::Color::Black, sf::Color(237,210,103,0));
    guiManager.addButton(1002, true, 910, 465, std::string("Media/Image/Menu/Buttons/Options_Button_a.png"), std::string(""), 800, 260 ,1,50, sf::Color::Black, sf::Color(237,210,103,0));
    guiManager.addButton(1003, true, 910, 565, std::string("Media/Image/Menu/Buttons/Options_Button_a.png"), std::string(""), 800, 260 ,1,50, sf::Color::Black, sf::Color(237,210,103,0));

    //skill 4 5 6
    guiManager.addButton(1004, true, 910, 965, std::string("Media/Image/Menu/Buttons/Options_Button_a.png"), std::string(""), 800, 260 ,1,50, sf::Color::Black, sf::Color(237,210,103,0));
    guiManager.addButton(1005, true, 910, 1065, std::string("Media/Image/Menu/Buttons/Options_Button_a.png"), std::string(""), 800, 260 ,1,50, sf::Color::Black, sf::Color(237,210,103,0));
    guiManager.addButton(1006, true, 910, 1165, std::string("Media/Image/Menu/Buttons/Options_Button_a.png"), std::string(""), 800, 260 ,1,50, sf::Color::Black, sf::Color(237,210,103,0));


    //Back and Apply
    guiManager.addButton(100, false, 1700, 1000, std::string("Media/Image/Menu/Buttons/Button_Editor.png"), std::string("Apply"), 1760, 1005,1,30, sf::Color::Black, sf::Color(153,153,0,111));
    guiManager.addButton(101, false, 20, 1000, std::string("Media/Image/Menu/Buttons/Button_Editor.png"), std::string("Back"), 80, 1005,1,30, sf::Color::Black, sf::Color(153,153,0,111));
}

State_OptionsMenu::~State_OptionsMenu()
{

}

void State_OptionsMenu::processImput(sf::Keyboard::Key key,bool isPressed)
{
    if(key == sf::Keyboard::Up)
    {
        keyboard_up = isPressed;
    }
    else if(key == sf::Keyboard::Down)
    {
        keyboard_down = isPressed;
    }
}

void State_OptionsMenu::update(sf::Time elapsedTime)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        bool change = false;
        if(guiManager.testButton(2000))
        {
            optionsTab = display;
            change = true;
        }
        else if(guiManager.testButton(2001))
        {
            optionsTab = audio;
            change = true;
        }
        else if(guiManager.testButton(2002))
        {
            optionsTab = game;
            change = true;
        }
        else if(guiManager.testButton(2003))
        {
            optionsTab = input;
            change = true;
        }

        if(change)
        {
            for(int x = 5; x <= 10; x++)
            {
                guiManager.changeVisibility(x, true);
            }

            for(int x = 20; x <= 21; x++)
            {
                guiManager.changeVisibility(x, true);
            }

            for(int x = 1000; x <= 1006; x++)
            {
                guiManager.changeVisibility(x, true);
            }
        }

        switch (optionsTab)
        {
        case display:
            if(guiManager.testButton(5))
            {
                if(newVideoMode > 0)
                {
                    newVideoMode--;
                }
                else
                {
                    newVideoMode = 1;
                }
            }
            else if(guiManager.testButton(6))
            {
                if(newVideoMode < 1)
                {
                    newVideoMode++;
                }
                else
                {
                    newVideoMode = 0;
                }
            }
            //~~~~~~

            else if(guiManager.testButton(7))
            {
                if(newFps == 0)
                {
                    newFps = 144;
                }
                else if(newFps == 30)
                {
                    newFps = 0;
                }
                else if(newFps == 60)
                {
                    newFps = 30;
                }
                else if(newFps == 120)
                {
                    newFps = 60;
                }
                else if(newFps == 144)
                {
                    newFps = 120;
                }
                else
                {
                    newFps = 0;
                }
            }
            else if(guiManager.testButton(8))
            {
                if(newFps == 0)
                {
                    newFps = 30;
                }
                else if(newFps == 30)
                {
                    newFps = 60;
                }
                else if(newFps == 60)
                {
                    newFps = 120;
                }
                else if(newFps == 120)
                {
                    newFps = 144;
                }
                else if(newFps == 144)
                {
                    newFps = 0;
                }
                else
                {
                    newFps = 0;
                }
            }

            //~~~~~
            else if(guiManager.testButton(9))
            {
                if(newFont > 1)
                {
                    newFont--;
                }
                else
                {
                    newFont = 3;
                }
            }
            else if(guiManager.testButton(10))
            {
                if(newFont < 3)
                {
                    newFont++;
                }
                else
                {
                    newFont = 1;
                }
            }
            break;

        case audio:

            if(guiManager.testButton(20))
            {
                if(newMusicVolume == 0)
                {
                    newMusicVolume = 100;
                }
                else
                {
                    newMusicVolume += - 10;
                }
            }
            else if(guiManager.testButton(21))
            {
                if(newMusicVolume == 100)
                {
                    newMusicVolume = 0;
                }
                else
                {
                    newMusicVolume += 10;
                }
            }
            break;
        case game:

            break;
        case input:

            break;
        }

        //~~~~~~~~
        if(guiManager.testButton(100))
        {
            if(newVideoMode != videoMode)
            {
                switch(newVideoMode)
                {
                case 0:
                    window.close();
                    window.create(sf::VideoMode(1920, 1080),"Questia",sf::Style::Fullscreen);
                    break;
                case 1:
                    window.close();
                    window.create(sf::VideoMode(1280, 720),"Questia",sf::Style::Default);
                    break;
                }
                Data_Desktop::getInstance().setDesktopResolution(sf::Vector2i(window.getSize().x,window.getSize().y),window.getPosition());
            }
            if(newFont != fps)
            {
                if(newFps == 0)
                {
                    window.setVerticalSyncEnabled(true);
                }
                else
                {
                    window.setVerticalSyncEnabled(false);
                    window.setFramerateLimit(newFps);
                }
            }
            if(font != newFont)
            {
                Data_Desktop::getInstance().changeFont(newFont);
            }

            Data_Desktop::getInstance().writeOptions(newVideoMode, newFps, newMusicVolume, newFont,
                    newKey_moveUp,  newKey_moveDown,  newKey_moveLeft,  newKey_moveRight
                    , newKey_skill4, newKey_skill5, newKey_skill6);
            StateManager::getInstance().changeState(new State_Transition(window, 3));

        }
        else if(guiManager.testButton(101))
        {
            StateManager::getInstance().changeState(new State_Transition(window, 1));
        }
    }

    if(optionsTab == input)
    {
        if(guiManager.testButton(1000))
        {
            char temp = Data_Desktop::getInstance().getMostRecentChar();
            if(temp != ' ')
            {
                newKey_moveUp = temp;
            }
        }

        if(guiManager.testButton(1001))
        {
            char temp = Data_Desktop::getInstance().getMostRecentChar();
            if(temp != ' ')
            {
                newKey_moveDown = temp;
            }
        }

        if(guiManager.testButton(1002))
        {
            char temp = Data_Desktop::getInstance().getMostRecentChar();
            if(temp != ' ')
            {
                newKey_moveLeft = temp;
            }
        }

        if(guiManager.testButton(1003))
        {
            char temp = Data_Desktop::getInstance().getMostRecentChar();
            if(temp != ' ')
            {
                newKey_moveRight = temp;
            }
        }
        if(guiManager.testButton(1004))
        {
            char temp = Data_Desktop::getInstance().getMostRecentChar();
            if(temp != ' ')
            {
                newKey_skill4 = temp;
            }
        }
        if(guiManager.testButton(1005))
        {
            char temp = Data_Desktop::getInstance().getMostRecentChar();
            if(temp != ' ')
            {
                newKey_skill5  = temp;
            }
        }
        if(guiManager.testButton(1006))
        {
            char temp = Data_Desktop::getInstance().getMostRecentChar();
            if(temp != ' ')
            {
                newKey_skill6 = temp;
            }
        }

    }

    scrollSelector:

    switch (optionsTab)
    {
    case display:
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
            scrollAmount_d += 28;
            for(int x = 5; x <= 10; x++)
            {
                sf::Vector2i tempCoords = guiManager.getButtonCoords(x);
                guiManager.moveSprite(x, tempCoords.x , tempCoords.y+ 28);
            }
            break;
        case -1:
            scrollAmount_d -= 28;
            for(int x = 5; x <= 10; x++)
            {
                sf::Vector2i tempCoords = guiManager.getButtonCoords(x);
                guiManager.moveSprite(x, tempCoords.x, tempCoords.y - 28);
            }
            break;
        }
        break;
    case audio:
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
            scrollAmount_a += 28;
            for(int x = 20; x <= 21; x++)
            {
                sf::Vector2i tempCoords = guiManager.getButtonCoords(x);
                guiManager.moveSprite(x, tempCoords.x , tempCoords.y+ 28);
            }

            break;
        case -1:
            scrollAmount_a -= 28;
            for(int x = 20; x <= 21; x++)
            {
                sf::Vector2i tempCoords = guiManager.getButtonCoords(x);
                guiManager.moveSprite(x, tempCoords.x, tempCoords.y - 28);
            }
            break;
        }
        break;
    case game:
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
            goto scrollSelector;;
        case 1:
            scrollAmount_g += 28;
            /*
            for(int x = 0; x <= 0; x++)
            {
                sf::Vector2i tempCoords = guiManager.getButtonCoords(x);
                guiManager.moveSprite(x, tempCoords.x , tempCoords.y+ + 28);
            }

            break;
            case -1:
            scrollAmount_g -= 28;
            for(int x = 20; x <= 21; x++)
            {
                sf::Vector2i tempCoords = guiManager.getButtonCoords(x);
                guiManager.moveSprite(x, tempCoords.x, tempCoords.y - 28);
            }
            break;
            */
        }
        break;
    case input:
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
            scrollAmount_i += 28;
            for(int x = 1000; x <= 1006; x++)
            {
                sf::Vector2i tempCoords = guiManager.getButtonCoords(x);
                guiManager.moveSprite(x, tempCoords.x , tempCoords.y + 28);
            }
            break;
        case -1:
            scrollAmount_i -= 28;
            for(int x = 1000; x <= 1006; x++)
            {
                sf::Vector2i tempCoords = guiManager.getButtonCoords(x);
                guiManager.moveSprite(x, tempCoords.x, tempCoords.y - 28);
            }
            break;
        }
        break;
    }
}

std::string State_OptionsMenu::checkKeyName(char c)
{
    if(c == 'C')
    {
        return std::string("Control");
    }
    if(c == 'S')
    {
        return std::string("Shift");
    }
    if(c == 'A')
    {
        return std::string("Alt");
    }
    if(c == 'T')
    {
        return std::string("Tab");
    }
    if(c == 'B')
    {
        return std::string("Space");
    }
    if(c == '_')
    {
        return std::string("Back Space");
    }
    if(c == 'E')
    {
        return std::string("Enter");
    }
    std::stringstream ss;
    ss << c;
    std::string r;
    ss >> r;
    return r;
}

void State_OptionsMenu::displayTextures()
{
    window.draw(background);
    guiManager.buttonCheck();

    switch (optionsTab)
    {
    case display:
        setting.setPosition(385, 250 + scrollAmount_d);
        window.draw(setting);
        settingText.setPosition(440, 270 + scrollAmount_d);
        settingText.setString("Window mode");
        window.draw(settingText);
        settingText.setPosition(1020, 270 + scrollAmount_d);
        switch (newVideoMode)
        {
        case 0:
            settingText.setString("Full Screen");
            break;
        case 1:
            settingText.setString("Windowed");
            break;
        }
        window.draw(settingText);
        guiManager.changeVisibility(5, false);
        guiManager.changeVisibility(6, false);
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        setting.setPosition(385, 350 + scrollAmount_d);
        window.draw(setting);
        settingText.setPosition(440, 370 + scrollAmount_d);
        settingText.setString("Frames Per Second");
        window.draw(settingText);
        settingText.setPosition(1020, 370 + scrollAmount_d);
        switch (newFps)
        {
        case 0:
            settingText.setString("V-Sync");
            break;
        case 30:
            settingText.setString("Peasant Mode   (30 Hz)");
            break;
        case 60:
            settingText.setString("Normal  Mode   (60 Hz)");
            break;
        case 120:
            settingText.setString("Fluid Mode      (120 Hz)");
            break;
        case 144:
            settingText.setString("Glorious Mode (144 Hz)");
            break;

        }
        window.draw(settingText);
        guiManager.changeVisibility(7, false);
        guiManager.changeVisibility(8, false);

        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        setting.setPosition(385, 450 + scrollAmount_d);
        window.draw(setting);
        settingText.setPosition(440, 470 + scrollAmount_d);
        settingText.setString("Font");
        window.draw(settingText);
        settingText.setPosition(1020, 470 + scrollAmount_d);
        switch (newFont)
        {
        case 0:
            settingText.setString("Custom");
            break;
        case 1:
            settingText.setString("Lato-Medium");
            break;
        case 2:
            settingText.setString("Lato-Regular");
            break;
        case 3:
            settingText.setString("acidstructure");
            break;
        }

        window.draw(settingText);
        guiManager.changeVisibility(9, false);
        guiManager.changeVisibility(10, false);

        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        break;
    case audio:
        setting.setPosition(385, 250 + scrollAmount_a);
        window.draw(setting);
        settingText.setPosition(440, 270 + scrollAmount_a);
        settingText.setString("Music Volume");
        window.draw(settingText);
        settingText.setPosition(1020, 270 + scrollAmount_a);
        switch (newMusicVolume)
        {
        case 0:
            settingText.setString("No music");
            break;
        case 10:
            settingText.setString("10%");
            break;
        case 20:
            settingText.setString("20%");
            break;
        case 30:
            settingText.setString("30%");
            break;
        case 40:
            settingText.setString("40%");
            break;
        case 50:
            settingText.setString("50%");
            break;
        case 60:
            settingText.setString("60%");
            break;
        case 70:
            settingText.setString("70%");
            break;
        case 80:
            settingText.setString("80%");
            break;
        case 90:
            settingText.setString("90%");
            break;
        case 100:
            settingText.setString("100%");
            break;
        }
        window.draw(settingText);
        guiManager.changeVisibility(20, false);
        guiManager.changeVisibility(21, false);

        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        break;
    case game:


        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        break;
    case input:
        setting.setPosition(385, 250 + scrollAmount_i);
        window.draw(setting);
        settingText.setPosition(440, 270 + scrollAmount_i);
        settingText.setString("Move up");
        window.draw(settingText);

        guiManager.changeVisibility(1000, false);

        if(guiManager.testButton(1000))
        {
            settingText.setPosition(970, 270 + scrollAmount_i);
            settingText.setString("Hover and press key");
            window.draw(settingText);
        }
        else
        {
            settingText.setString(checkKeyName(newKey_moveUp));
            if(settingText.getString().getSize() > 2)
            {
                settingText.setPosition(1100 - 35, 270 + scrollAmount_i);
            }
            else
            {
                settingText.setPosition(1100, 270 + scrollAmount_i);
            }
            window.draw(settingText);
        }

        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        setting.setPosition(385, 350 + scrollAmount_i);
        window.draw(setting);
        settingText.setPosition(440, 370 + scrollAmount_i);
        settingText.setString("Move down");
        window.draw(settingText);

        guiManager.changeVisibility(1001, false);

        if(guiManager.testButton(1001))
        {
            settingText.setPosition(970, 370 + scrollAmount_i);
            settingText.setString("Hover and press key");
            window.draw(settingText);
        }
        else
        {
            settingText.setString(checkKeyName(newKey_moveDown));
            if(settingText.getString().getSize() > 2)
            {
                settingText.setPosition(1100 - 35, 370 + scrollAmount_i);
            }
            else
            {
                settingText.setPosition(1100, 370 + scrollAmount_i);
            }

            window.draw(settingText);
        }

        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        setting.setPosition(385, 450 + scrollAmount_i);
        window.draw(setting);
        settingText.setPosition(440, 470 + scrollAmount_i);
        settingText.setString("Move left");
        window.draw(settingText);

        guiManager.changeVisibility(1002, false);

        if(guiManager.testButton(1002))
        {
            settingText.setPosition(970, 470 + scrollAmount_i);
            settingText.setString("Hover and press key");
            window.draw(settingText);
        }
        else
        {
            settingText.setString(checkKeyName(newKey_moveLeft));
            if(settingText.getString().getSize() > 2)
            {
                settingText.setPosition(1100 - 35, 470 + scrollAmount_i);
            }
            else
            {
                settingText.setPosition(1100, 470 + scrollAmount_i);
            }

            window.draw(settingText);
        }

        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        setting.setPosition(385, 550 + scrollAmount_i);
        window.draw(setting);

        settingText.setPosition(440, 570 + scrollAmount_i);
        settingText.setString("Move right");
        window.draw(settingText);

        guiManager.changeVisibility(1003, false);

        if(guiManager.testButton(1003))
        {
            settingText.setPosition(970, 570 + scrollAmount_i);
            settingText.setString("Hover and press key");
            window.draw(settingText);
        }
        else
        {
            settingText.setString(checkKeyName(newKey_moveRight));
            if(settingText.getString().getSize() > 2)
            {
                settingText.setPosition(1100 - 35, 570 + scrollAmount_i);
            }
            else
            {
                settingText.setPosition(1100, 570 + scrollAmount_i);
            }

            window.draw(settingText);
        }

        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        setting.setPosition(385, 650 + scrollAmount_i);
        window.draw(setting);

        settingText.setPosition(440, 670 + scrollAmount_i);
        settingText.setString("Skill 1");
        window.draw(settingText);

        settingText.setPosition(1050, 670 + scrollAmount_i);
        settingText.setString("Mouse 1");
        window.draw(settingText);


        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        setting.setPosition(385, 750 + scrollAmount_i);
        window.draw(setting);

        settingText.setPosition(440, 770 + scrollAmount_i);
        settingText.setString("Skill 2");
        window.draw(settingText);

        settingText.setPosition(1010, 770 + scrollAmount_i);
        settingText.setString("Middle Mouse");
        window.draw(settingText);


        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        setting.setPosition(385, 850 + scrollAmount_i);
        window.draw(setting);

        settingText.setPosition(440, 870 + scrollAmount_i);
        settingText.setString("Skill 3");
        window.draw(settingText);

        settingText.setPosition(1050, 870 + scrollAmount_i);
        settingText.setString("Mouse 2");
        window.draw(settingText);


        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        setting.setPosition(385, 950 + scrollAmount_i);
        window.draw(setting);

        settingText.setPosition(440, 970 + scrollAmount_i);
        settingText.setString("Skill 4");
        window.draw(settingText);

        guiManager.changeVisibility(1004, false);

        if(guiManager.testButton(1004))
        {
            settingText.setPosition(970, 970 + scrollAmount_i);
            settingText.setString("Hover and press key");
            window.draw(settingText);
        }
        else
        {
            settingText.setString(checkKeyName(newKey_skill4));
            if(settingText.getString().getSize() > 2)
            {
                settingText.setPosition(1100 - 35, 970 + scrollAmount_i);
            }
            else
            {
                settingText.setPosition(1100, 970 + scrollAmount_i);
            }
        }
        window.draw(settingText);


        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        setting.setPosition(385, 1050 + scrollAmount_i);
        window.draw(setting);

        settingText.setPosition(440, 1070 + scrollAmount_i);
        settingText.setString("Skill 5");
        window.draw(settingText);

        settingText.setPosition(985, 1070 + scrollAmount_i);


        guiManager.changeVisibility(1005, false);

        if(guiManager.testButton(1005))
        {
            settingText.setPosition(970, 1070 + scrollAmount_i);
            settingText.setString("Hover and press key");
            window.draw(settingText);
        }
        else
        {
            settingText.setString(checkKeyName(newKey_skill5));
            if(settingText.getString().getSize() > 2)
            {
                settingText.setPosition(1100 - 35, 1070 + scrollAmount_i);
            }
            else
            {
                settingText.setPosition(1100, 1070 + scrollAmount_i);
            }
        }
        window.draw(settingText);


        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        setting.setPosition(385, 1150 + scrollAmount_i);
        window.draw(setting);

        settingText.setPosition(440, 1170 + scrollAmount_i);
        settingText.setString("Skill 6");
        window.draw(settingText);


        guiManager.changeVisibility(1006, false);

        if(guiManager.testButton(1006))
        {
            settingText.setPosition(970, 1170 + scrollAmount_i);
            settingText.setString("Hover and press key");
            window.draw(settingText);
        }
        else
        {
            settingText.setString(checkKeyName(newKey_skill6));
            if(settingText.getString().getSize() > 2)
            {
                settingText.setPosition(1100 - 35, 1170 + scrollAmount_i);
            }
            else
            {
                settingText.setPosition(1100, 1170 + scrollAmount_i);
            }
        }
        window.draw(settingText);

        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        break;
    }
    guiManager.drawGui();
}


