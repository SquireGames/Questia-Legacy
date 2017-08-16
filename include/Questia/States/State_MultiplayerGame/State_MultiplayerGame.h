#ifndef STATE_MULTIPLAYERGAME_H
#define STATE_MULTIPLAYERGAME_H

#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/Engine.h"

#include "QuestiaEng/Multiplayer/Client/ClientsideConnection.h"

class State_MultiplayerGame : public State
{
public:
	State_MultiplayerGame(std::shared_ptr<void> params);
	virtual void init() final;
	~State_MultiplayerGame();
	
	virtual void processInput(std::u32string const& inputText) final;
	virtual void update(sf::Time elapsedTime) final;
	virtual void displayTextures() final;
	
	static std::shared_ptr<void> createParameters(std::string ip, unsigned short port);

private:
	ClientsideConnection serverConnection;
	
	struct Parameters
	{
		std::string ipAddress;
		unsigned short port;
	};
};

#endif // STATE_MULTIPLAYERGAME_H
