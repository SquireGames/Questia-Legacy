#include "Questia/States/State_Game/State_Game.h"

State_Game::State_Game():
	pos(0,0)
	, gameView(sf::FloatRect(1920/2,1080/2,1920,1080))
	, guiView(sf::FloatRect(0,0,1920,1080))
{
}
void State_Game::init()
{
	eng->tile().loadMap("Demo_1");
	eng->tile().setViewportSize(1920, 1080);
}

State_Game::~State_Game()
{
	eng->gui().purgeButtons();
}

void State_Game::processInput(std::u32string const& inputText)
{
	
}
void State_Game::update(sf::Time elapsedTime)
{
	const int speed = 3;
	if(ctr::checkInput(ctr::Input::W))
	{
		pos = pos - utl::Vector2f(0, speed);
	}
	if(ctr::checkInput(ctr::Input::A))
	{
		pos = pos - utl::Vector2f(speed, 0);
	}
	if(ctr::checkInput(ctr::Input::S))
	{
		pos = pos + utl::Vector2f(0, speed);
	}
	if(ctr::checkInput(ctr::Input::D))
	{
		pos = pos + utl::Vector2f(speed, 0);
	}
	eng->tile().setPosition(pos.x, pos.y);
	gameView.setCenter(pos.sf());
}
void State_Game::displayTextures()
{
	eng->win().setView(gameView);
	eng->tile().draw();
	
	eng->win().setView(guiView);
}
