#include "Questia/States/State_Game/State_Game.h"

State_Game::State_Game():
	threadPool(4)
	, pos(0,0)
	, gameView(sf::FloatRect(1920/2,1080/2,1920,1080))
	, guiView(sf::FloatRect(0,0,1920,1080))
{
}
void State_Game::init()
{
	eng->gui().loadGui("game");

	eng->ent().reg("Orb", [](int id, EntityManager& e, ResourceManager* r, utl::Vector2f coords) {return new Entity_Orb(id, e, r, coords);});

	eng->tile().setViewportSize(1920, 1080);
	eng->tile().loadMap("Demo_1");

	//threadPool.addTask([]() {std::cout << "A" << std::endl;});

	eng->ent().spawn("Orb", utl::Vector2f(25,25));
}

State_Game::~State_Game()
{
	eng->gui().edit().purgeButtons();
	threadPool.kill();
}

void State_Game::processInput(std::u32string const& inputText)
{

}
void State_Game::update(sf::Time elapsedTime)
{
	eng->ent().update();

	const int speed = 10;
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

	eng->tile().setPosition(pos);
	gameView.setCenter(pos.sf());

	//std::cout << "-------" << std::endl;
	threadPool.runTasks();
	//std::cout << "-------" << std::endl;
}
void State_Game::displayTextures()
{
	eng->win().setView(gameView);
	eng->tile().draw();
	eng->ent().draw(DrawLayer::Entity_Regular);

	eng->win().setView(guiView);
	eng->gui().draw();
}
