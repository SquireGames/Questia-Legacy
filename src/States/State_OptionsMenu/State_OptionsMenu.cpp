#include "Questia/States/State_OptionsMenu/State_OptionsMenu.h"

State_OptionsMenu::State_OptionsMenu()
{

}

void State_OptionsMenu::init()
{
	optionManager = std::unique_ptr<OptionManager>(new OptionManager(&eng->gui()));
	eng->gui().loadGui("options");
	eng->win().setView(sf::View(sf::FloatRect(0,0,1920,1080)));

	SV_Options& saveFile = eng->sv();

	///options
	///display
	//windowMode
	option_windowMode.setType(OptionType::choice);
	option_windowMode.setList("displayList");
	option_windowMode.setOptionName(saveFile.getWindowMode_name());
	option_windowMode.addChoice(std::make_pair("Fullscreen", 0));
	option_windowMode.addChoice(std::make_pair("Windowed",   1));
	//fps
	option_fps.setType(OptionType::choice);
	option_fps.setList("displayList");
	option_fps.setOptionName(saveFile.getFps_name());
	option_fps.addChoice(std::make_pair("V-Sync", 0));
	option_fps.addChoice(std::make_pair("60  Fps", 60));
	option_fps.addChoice(std::make_pair("128 Fps", 128));
	option_fps.addChoice(std::make_pair("144 Fps", 144));
	option_fps.addChoice(std::make_pair("256 Fps", 256));
	option_fps.addChoice(std::make_pair("Unlimited", -1));
	//font
	option_font.setType(OptionType::choice);
	option_font.setList("displayList");
	option_font.setOptionName(saveFile.getFont_name());
	for(const auto& it : utl::getFiles("Media/Fonts", false))
	{
		if(it.size() > 4)
		{
			option_font.addChoice(std::make_pair(it.substr(0, it.size() - 4), it));
		}
	}
	
	//guiPack
	option_guiPack.setType(OptionType::choice);
	option_guiPack.setList("displayList");
	option_guiPack.setOptionName(saveFile.getGuiPack_name());
	for(const auto& it : utl::getFiles("Data/Gui Pack", false))
	{
		option_guiPack.addChoice(std::make_pair(it, it));
	}

	///audio
	//music volume
	option_musicVolume.setType(OptionType::choice);
	option_musicVolume.setList("audioList");
	option_musicVolume.setOptionName(saveFile.getMusicVolume_name());
	option_musicVolume.setChoices( {std::make_pair("Muted", 0), std::make_pair("10%", 10), std::make_pair("20%", 20), std::make_pair("30%", 30), std::make_pair("40%", 40), std::make_pair("50%", 50),
	                                std::make_pair("60%", 60), std::make_pair("70%", 70), std::make_pair("80%", 80), std::make_pair("90%", 90), std::make_pair("100%", 100)
	                               });

	///input
	//move up key
	option_key_moveUp.setType(OptionType::input);
	option_key_moveUp.setList("inputList");
	option_key_moveUp.setOptionName(saveFile.getKey_moveUp_name());
	//move down key
	option_key_moveDown.setType(OptionType::input);
	option_key_moveDown.setList("inputList");
	option_key_moveDown.setOptionName(saveFile.getKey_moveDown_name());
	//move left key
	option_key_moveLeft.setType(OptionType::input);
	option_key_moveLeft.setList("inputList");
	option_key_moveLeft.setOptionName(saveFile.getKey_moveLeft_name());
	//move right key
	option_key_moveRight.setType(OptionType::input);
	option_key_moveRight.setList("inputList");
	option_key_moveRight.setOptionName(saveFile.getKey_moveRight_name());
	//skill 1 key
	option_key_skill_1.setType(OptionType::input);
	option_key_skill_1.setList("inputList");
	option_key_skill_1.setOptionName(saveFile.getKey_skill_1_name());
	//skill 2 key
	option_key_skill_2.setType(OptionType::input);
	option_key_skill_2.setList("inputList");
	option_key_skill_2.setOptionName(saveFile.getKey_skill_2_name());
	//skill 3 key
	option_key_skill_3.setType(OptionType::input);
	option_key_skill_3.setList("inputList");
	option_key_skill_3.setOptionName(saveFile.getKey_skill_3_name());
	//skill 4 key
	option_key_skill_4.setType(OptionType::input);
	option_key_skill_4.setList("inputList");
	option_key_skill_4.setOptionName(saveFile.getKey_skill_4_name());
	//skill 5 key
	option_key_skill_5.setType(OptionType::input);
	option_key_skill_5.setList("inputList");
	option_key_skill_5.setOptionName(saveFile.getKey_skill_5_name());
	//skill 6 key
	option_key_skill_6.setType(OptionType::input);
	option_key_skill_6.setList("inputList");
	option_key_skill_6.setOptionName(saveFile.getKey_skill_6_name());

	//starting values
	option_windowMode.init(saveFile.getWindowMode());
	option_fps.init(saveFile.getFps());
	option_font.init(saveFile.getFont());
	option_musicVolume.init(saveFile.getMusicVolume());
	option_guiPack.init(saveFile.getGuiPack());
	option_key_moveUp.init(static_cast<ctr::Input>(saveFile.getKey_moveUp()));
	option_key_moveDown.init(static_cast<ctr::Input>(saveFile.getKey_moveDown()));
	option_key_moveLeft.init(static_cast<ctr::Input>(saveFile.getKey_moveLeft()));
	option_key_moveRight.init(static_cast<ctr::Input>(saveFile.getKey_moveRight()));
	option_key_skill_1.init(static_cast<ctr::Input>(saveFile.getKey_skill_1()));
	option_key_skill_2.init(static_cast<ctr::Input>(saveFile.getKey_skill_2()));
	option_key_skill_3.init(static_cast<ctr::Input>(saveFile.getKey_skill_3()));
	option_key_skill_4.init(static_cast<ctr::Input>(saveFile.getKey_skill_4()));
	option_key_skill_5.init(static_cast<ctr::Input>(saveFile.getKey_skill_5()));
	option_key_skill_6.init(static_cast<ctr::Input>(saveFile.getKey_skill_6()));

	//storing
	optionManager->addOption(&option_windowMode);
	optionManager->addOption(&option_fps);
	optionManager->addOption(&option_font);
	optionManager->addOption(&option_musicVolume);
	optionManager->addOption(&option_guiPack);
	optionManager->addOption(&option_key_moveUp);
	optionManager->addOption(&option_key_moveDown);
	optionManager->addOption(&option_key_moveLeft);
	optionManager->addOption(&option_key_moveRight);
	optionManager->addOption(&option_key_skill_1);
	optionManager->addOption(&option_key_skill_2);
	optionManager->addOption(&option_key_skill_3);
	optionManager->addOption(&option_key_skill_4);
	optionManager->addOption(&option_key_skill_5);
	optionManager->addOption(&option_key_skill_6);

	//initialization
	optionManager->initLists();

	///hiding of unneeded lists
	GuiBuilder& guiBuilder = eng->gui().edit();
	guiBuilder.setListAtr("displayList", gui::BtnChar::isVisible, true);
	guiBuilder.setListAtr("audioList"  , gui::BtnChar::isVisible, false);
	guiBuilder.setListAtr("gameList"   , gui::BtnChar::isVisible, false);
	guiBuilder.setListAtr("inputList"  , gui::BtnChar::isVisible, false);
}

State_OptionsMenu::~State_OptionsMenu()
{
	eng->gui().edit().purgeButtons();
}

void State_OptionsMenu::processInput(std::u32string const& inputText)
{

}

void State_OptionsMenu::update(sf::Time elapsedTime)
{
	GuiBuilder& guiBuilder = eng->gui().edit();
	
	if(eng->lastKey() != ctr::Input::None)
	{
		optionManager->handleInput(eng->lastKey());
	}

	if(!optionManager->isMouseOverAssignedInput())
	{
		if(ctr::checkInput(ctr::Input::W))
		{
			guiBuilder.setListAtr(activeSelector, gui::BtnChar::addToScroll_y, 15);
		}
		if(ctr::checkInput(ctr::Input::S))
		{
			guiBuilder.setListAtr(activeSelector, gui::BtnChar::addToScroll_y, -15);
		}
		optionManager->resetClicks();
	}
	const int mouseScroll = eng->mouse().getScroll();
	if(mouseScroll == 1)
	{
		guiBuilder.setListAtr(activeSelector, gui::BtnChar::addToScroll_y, 40);
	}
	else if(mouseScroll == -1)
	{
		guiBuilder.setListAtr(activeSelector, gui::BtnChar::addToScroll_y, -40);
	}

	//mouse input for key binding
	optionManager->checkMouseInput();
	if(eng->mouse().isMouseReleased(ctr::Input::LMouse))
	{
		optionManager->setMouseReleased();
	}

	///gui check
	if(eng->mouse().isMousePressed(ctr::Input::LMouse))
	{
		if(optionManager->handleGui()) {}

		//switches
		if(eng->gui().isHovered("displaySwitch"))
		{
			activeSelector = "displayList";
			guiBuilder.setListAtr("displayList", gui::BtnChar::isVisible, true);
			guiBuilder.setListAtr("audioList",   gui::BtnChar::isVisible, false);
			guiBuilder.setListAtr("gameList",    gui::BtnChar::isVisible, false);
			guiBuilder.setListAtr("inputList",   gui::BtnChar::isVisible, false);
		}
		else if(eng->gui().isHovered("audioSwitch"))
		{
			activeSelector = "audioList";
			guiBuilder.setListAtr("displayList", gui::BtnChar::isVisible, false);
			guiBuilder.setListAtr("audioList",   gui::BtnChar::isVisible, true);
			guiBuilder.setListAtr("gameList",    gui::BtnChar::isVisible, false);
			guiBuilder.setListAtr("inputList",   gui::BtnChar::isVisible, false);
		}
		else if(eng->gui().isHovered("gameSwitch"))
		{
			activeSelector = "gameList";
			guiBuilder.setListAtr("displayList", gui::BtnChar::isVisible, false);
			guiBuilder.setListAtr("audioList",   gui::BtnChar::isVisible, false);
			guiBuilder.setListAtr("gameList",    gui::BtnChar::isVisible, true);
			guiBuilder.setListAtr("inputList",   gui::BtnChar::isVisible, false);
		}
		else if(eng->gui().isHovered("inputSwitch"))
		{
			activeSelector = "inputList";
			guiBuilder.setListAtr("displayList", gui::BtnChar::isVisible, false);
			guiBuilder.setListAtr("audioList",   gui::BtnChar::isVisible, false);
			guiBuilder.setListAtr("gameList",    gui::BtnChar::isVisible, false);
			guiBuilder.setListAtr("inputList",   gui::BtnChar::isVisible, true);
		}
		//regular
		else if(eng->gui().isHovered("mainMenu"))
		{
			eng->state().changeState("MainMenu");
		}
		else if(eng->gui().isHovered("apply"))
		{
			optionManager->saveOptions(eng->sv());
			eng->sv().writeOptions();

			//window modes
			if(option_windowMode.isChanged())
			{
				switch(option_windowMode.getValue())
				{
				case 0:
					eng->win().create(sf::VideoMode(1920, 1080),"Questia",sf::Style::Fullscreen);
					break;
				case 1:
					eng->win().create(sf::VideoMode(1280, 720),"Questia",sf::Style::Default);
					break;
				}
				eng->fixWindowScale();
			}
			//fps
			if(option_fps.getValue() == 0)
			{
				eng->win().setVerticalSyncEnabled(true);
			}
			else if(option_fps.getValue() == -1)
			{
				eng->win().setFramerateLimit(100000);
				eng->win().setVerticalSyncEnabled(false);
			}
			else
			{
				eng->win().setFramerateLimit(option_fps.getValue());
				eng->win().setVerticalSyncEnabled(false);
			}
			//font
			if(option_font.isChanged())
			{
				sf::Font newFont;
				if(newFont.loadFromFile("Media/Fonts/" + option_font.getValue()))
				{
					guiBuilder.setFont(newFont);
				}
			}
			//music
			//...

			eng->state().changeState("Options");
			//for gui
		}
	}
}

void State_OptionsMenu::displayTextures()
{
	eng->gui().draw();
}
