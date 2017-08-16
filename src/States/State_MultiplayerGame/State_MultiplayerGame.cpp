#include "Questia/States/State_MultiplayerGame/State_MultiplayerGame.h"

State_MultiplayerGame::State_MultiplayerGame(std::shared_ptr<void> params):
	State(params)
	, serverConnection()
{
	Parameters paramCopy = getParameters<State_MultiplayerGame::Parameters>();
	std::cout << paramCopy.ipAddress << ":" << paramCopy.port << std::endl;
}

void State_MultiplayerGame::init()
{
	if(serverConnection.attemptConnection("192.168.1.77", 7777))
	{
		std::cout << "Connection Success!!!" << std::endl;
	}
	else
	{
		std::cout << "Connection Failure :(" << std::endl;
	}
}

State_MultiplayerGame::~State_MultiplayerGame()
{

}

void State_MultiplayerGame::processInput(std::u32string const& inputText)
{

}

void State_MultiplayerGame::update(sf::Time elapsedTime)
{

}

void State_MultiplayerGame::displayTextures()
{

}

std::shared_ptr<void> State_MultiplayerGame::createParameters(std::string ip, unsigned short port)
{
	return makeParams<State_MultiplayerGame::Parameters>(ip, port);
}
