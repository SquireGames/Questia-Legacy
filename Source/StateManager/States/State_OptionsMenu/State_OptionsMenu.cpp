#include "State_OptionsMenu.h"

State_OptionsMenu::State_OptionsMenu(sf::RenderWindow &mWindow):
    window(mWindow)
    , resourceManager()
    , guiManager(window, resourceManager)
    , optionManager(&guiManager)
    , saveFile()
    , activeSelector("displayList")
    , key_up_isPressed(false)
    , key_down_isPressed(false)
{
    ///gui
    //font
    guiManager.setFont(Data_Desktop::getInstance().font1);
    //loader
    guiLoader.loadGui(guiManager, "options");

    ///options
    //windowMode
    option_windowMode.setList("displayList");
    option_windowMode.setOptionName(saveFile.getWindowModeName());
    option_windowMode.addChoice(std::make_pair("Fullscreen", 0));
    option_windowMode.addChoice(std::make_pair("Windowed",   1));
    //fps
    option_fps.setList("displayList");
    option_fps.setOptionName(saveFile.getFpsName());
    option_fps.addChoice(std::make_pair ("V-Sync", 0));
    option_fps.addChoice(std::make_pair ("60  Fps", 60));
    option_fps.addChoice(std::make_pair ("144 Fps", 144));
    option_fps.addChoice(std::make_pair ("288 Fps", 288));
    option_fps.addChoice(std::make_pair ("Unlimited", -1));
    //font
    option_font.setList("displayList");
    option_font.setOptionName(saveFile.getFontName());
    option_font.addChoice(std::make_pair ("Lato-Regular", "Lato-Regular.ttf"));
    option_font.addChoice(std::make_pair ("Lato-Medium", "Lato-Medium.ttf"));
    option_font.addChoice(std::make_pair ("acidstructure", "acidstructure.ttf"));
    //music volume
    option_musicVolume.setList("audioList");
    option_musicVolume.setOptionName(saveFile.getMusicName());
    option_musicVolume.setChoices({std::make_pair("Muted", 0), std::make_pair("10%", 10), std::make_pair("20%", 20), std::make_pair("30%", 30), std::make_pair("40%", 40), std::make_pair("50%", 50),
                                   std::make_pair("60%", 60), std::make_pair("70%", 70), std::make_pair("80%", 80), std::make_pair("90%", 90), std::make_pair("100%", 100)
                                  });
    //starting values
    option_windowMode.init(saveFile.getWindowMode());
    option_windowMode.init(saveFile.getWindowMode());
    option_fps.init(saveFile.getFps());
    option_font.init(saveFile.getFont());
    option_musicVolume.init(saveFile.getMusicVolume());
    //storing
    optionManager.addOption(&option_windowMode);
    optionManager.addOption(&option_fps);
    optionManager.addOption(&option_font);
    optionManager.addOption(&option_musicVolume);
    //initialization
    optionManager.initLists();

    ///hiding of unneeded lists
    guiManager.setListAtr("displayList", gui::ButtonCharacteristic::isVisible, true);
    guiManager.setListAtr("audioList", gui::ButtonCharacteristic::isVisible, false);
    guiManager.setListAtr("gameList", gui::ButtonCharacteristic::isVisible, false);
    guiManager.setListAtr("inputList", gui::ButtonCharacteristic::isVisible, false);
}

State_OptionsMenu::~State_OptionsMenu()
{
    std::cout << "Options Menu Destroyed" << std::endl;
}

void State_OptionsMenu::processImput(sf::Keyboard::Key key,bool isPressed)
{
    if(key == sf::Keyboard::Up)
    {
        key_up_isPressed = isPressed;
    }
    else if(key == sf::Keyboard::Down)
    {
        key_down_isPressed = isPressed;
    }
}

void State_OptionsMenu::update(sf::Time elapsedTime)
{
    ///update mouse
    guiManager.setMousePosition(std::make_pair(Data_Desktop::getInstance().getScaledMousePosition(window).x,Data_Desktop::getInstance().getScaledMousePosition(window).y));

    ///scroll input
    if(key_up_isPressed)
    {
        guiManager.setListAtr(activeSelector, gui::ButtonCharacteristic::addToScroll_y, -15);
    }
    if(key_down_isPressed)
    {
        guiManager.setListAtr(activeSelector, gui::ButtonCharacteristic::addToScroll_y, 15);
    }
    const int mouseScroll = Data_Desktop::getInstance().getMouseWheelDelta();
    if(mouseScroll == 1)
    {
        guiManager.setListAtr(activeSelector, gui::ButtonCharacteristic::addToScroll_y, -40);
    }
    else if(mouseScroll == -1)
    {
        guiManager.setListAtr(activeSelector, gui::ButtonCharacteristic::addToScroll_y, 40);
    }

    ///gui check
    if(Data_Desktop::getInstance().isMousePressed())
    {
        if(optionManager.handleGui()) {}
        //switches
        else if(guiManager.isClicked("displaySwitch"))
        {
            activeSelector = "displayList";
            guiManager.setListAtr("displayList", gui::ButtonCharacteristic::isVisible, true);
            guiManager.setListAtr("audioList", gui::ButtonCharacteristic::isVisible, false);
            guiManager.setListAtr("gameList", gui::ButtonCharacteristic::isVisible, false);
            guiManager.setListAtr("inputList", gui::ButtonCharacteristic::isVisible, false);
        }
        else if(guiManager.isClicked("audioSwitch"))
        {
            activeSelector = "audioList";
            guiManager.setListAtr("displayList", gui::ButtonCharacteristic::isVisible, false);
            guiManager.setListAtr("audioList", gui::ButtonCharacteristic::isVisible, true);
            guiManager.setListAtr("gameList", gui::ButtonCharacteristic::isVisible, false);
            guiManager.setListAtr("inputList", gui::ButtonCharacteristic::isVisible, false);
        }
        else if(guiManager.isClicked("gameSwitch"))
        {
            activeSelector = "gameList";
            guiManager.setListAtr("displayList", gui::ButtonCharacteristic::isVisible, false);
            guiManager.setListAtr("audioList", gui::ButtonCharacteristic::isVisible, false);
            guiManager.setListAtr("gameList", gui::ButtonCharacteristic::isVisible, true);
            guiManager.setListAtr("inputList", gui::ButtonCharacteristic::isVisible, false);
        }
        else if(guiManager.isClicked("inputSwitch"))
        {
            activeSelector = "inputList";
            guiManager.setListAtr("displayList", gui::ButtonCharacteristic::isVisible, false);
            guiManager.setListAtr("audioList", gui::ButtonCharacteristic::isVisible, false);
            guiManager.setListAtr("gameList", gui::ButtonCharacteristic::isVisible, false);
            guiManager.setListAtr("inputList", gui::ButtonCharacteristic::isVisible, true);
        }
        //regular
        else if(guiManager.isClicked("mainMenu"))
        {
            StateManager::getInstance().changeState(new State_Transition(window, 1));
        }
        else if(guiManager.isClicked("apply"))
        {
            optionManager.saveOptions(saveFile);
            saveFile.writeOptions();

            if(option_windowMode.isChanged())
            {
                switch (option_windowMode.getValue())
                {
                case 0:
                    window.create(sf::VideoMode(1920, 1080),"Questia",sf::Style::Fullscreen);
                    break;
                case 1:
                    window.create(sf::VideoMode(1280, 720),"Questia",sf::Style::Default);
                    break;
                }
                Data_Desktop::getInstance().setDesktopResolution(sf::Vector2i(window.getSize().x,window.getSize().y),window.getPosition());
            }
            if(option_fps.isChanged())
            {
                if(option_fps.getValue() == 0)
                {
                    window.setVerticalSyncEnabled(true);
                }
                else if (option_fps.getValue() == -1)
                {
                    window.setFramerateLimit(100000);
                    window.setVerticalSyncEnabled(false);
                }
                else
                {
                    window.setFramerateLimit(option_fps.getValue());
                    window.setVerticalSyncEnabled(false);
                }
            }
            if(option_font.isChanged())
            {
                Data_Desktop::getInstance().changeFont(option_font.getValue());
            }

            StateManager::getInstance().changeState(new State_Transition(window, 3));
        }
    }
}

void State_OptionsMenu::displayTextures()
{
    guiManager.drawButtons();
}


