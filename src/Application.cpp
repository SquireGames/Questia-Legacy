#include "Questia/Application.h"

Application::Application():
	eng("Questia", 128, 0, 0, 0, "Alpha")
{
	eng.state().reg("MainMenu", 	[]() {return new State_MainMenu();});
	eng.state().reg("Game", 		[]() {return new State_Game();});
	eng.state().reg("Options", 		[]() {return new State_OptionsMenu();});
	eng.state().reg("Loading",  	[]() {return new State_Loading();});

	eng.state().changeState("MainMenu");

	eng.gui().setGuiPack("Default");
}

Application::~Application()
{

}

void Application::run()
{
	//while the application is still running
	while(eng.run())
	{
		//while the application is due to update
		while(eng.tick())
		{
			eng.processInput();
			eng.state().sUpdate();
		}

		//render when possible, but only to the framerate limit
		eng.state().sDisplay();
		eng.render();
	}
}
