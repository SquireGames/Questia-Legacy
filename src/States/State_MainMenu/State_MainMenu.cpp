#include "Questia/States/State_MainMenu/State_MainMenu.h"
#include "Questia/States/State_MultiplayerGame/State_MultiplayerGame.h"



State_MainMenu::State_MainMenu()
{
	
}

void State_MainMenu::init()
{
	eng->gui().loadGui("mainMenu");
	eng->gui().edit().setBtnAtr("versionText", "text", gui::BtnAtrChar::text, eng->gui().edit().getText("T_Version") + U" " + utl::toU32(eng->getVersion()));
	eng->gui().edit().setBtnAtr("versionText_eng", "text", gui::BtnAtrChar::text, eng->gui().edit().getText("T_Eng_Version") + U" " + utl::toU32(eng->getVersion_eng()));
}

State_MainMenu::~State_MainMenu()
{
	eng->gui().edit().purgeButtons();
}

void State_MainMenu::processInput(std::u32string const& inputText)
{
	
}

void State_MainMenu::update(sf::Time elapsedTime)
{
	if(eng->mouse().isMouseReleased(ctr::Input::LMouse))
	{
		if(eng->gui().isHovered("play"))
		{
			eng->state().changeState("Game");
		}
		else if(eng->gui().isHovered("options"))
		{
			eng->state().changeState("Options");
		}
		else if(eng->gui().isHovered("exit"))
		{
			eng->terminate();
		}
	}
}

void State_MainMenu::displayTextures()
{
	eng->gui().draw();
}

