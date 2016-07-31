#include "State_OptionsMenu.h"

State_OptionsMenu::State_OptionsMenu(sf::RenderWindow &mWindow):
    window(mWindow)
    , resourceManager()
    , guiManager(window, resourceManager)
    , optionManager(&guiManager)
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
    option_windowMode.setOptionName("Window Setting");
    option_windowMode.addChoice(std::make_pair("Fullscreen", 0));
    option_windowMode.addChoice(std::make_pair("Windowed",   1));
    //fps
    option_fps.setList("displayList");
    option_fps.setOptionName("Frames Per Second");
    option_fps.addChoice(std::make_pair ("V-Sync", 0));
    option_fps.addChoice(std::make_pair ("60  Fps", 60));
    option_fps.addChoice(std::make_pair ("144 Fps", 144));
    option_fps.addChoice(std::make_pair ("288 Fps", 288));
    option_fps.addChoice(std::make_pair ("Unlimited", -1));
    //font
    option_font.setList("displayList");
    option_font.setOptionName("Font");
    option_font.addChoice(std::make_pair ("Lato-Medium", 1));
    option_font.addChoice(std::make_pair ("Lato-Regular", 2));
    option_font.addChoice(std::make_pair ("acidstructure", 3));
    //music volume
    option_musicVolume.setList("audioList");
    option_musicVolume.setOptionName("Music Volume");
    option_musicVolume.setChoices({std::make_pair("Muted", 0), std::make_pair("10%", 10), std::make_pair("20%", 20), std::make_pair("30%", 30), std::make_pair("40%", 40), std::make_pair("50%", 50),
                                   std::make_pair("60%", 60), std::make_pair("70%", 70), std::make_pair("80%", 80), std::make_pair("90%", 90), std::make_pair("100%", 100)
                                  });
    //starting values
    option_windowMode.init(0);
    option_fps.init(0);
    option_font.init(1);
    option_musicVolume.init(0);
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
        guiManager.setListAtr(activeSelector, gui::ButtonCharacteristic::addToScroll_x, -40);
    }
    else if(mouseScroll == -1)
    {
        guiManager.setListAtr(activeSelector, gui::ButtonCharacteristic::addToScroll_x, 40);
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
    }
}

void State_OptionsMenu::displayTextures()
{
    guiManager.drawButtons();
}


