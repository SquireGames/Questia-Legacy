#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>

#include "QuestiaEng/Engine.h"

#include "Questia/States/State_MainMenu/State_MainMenu.h"
#include "Questia/States/State_Game/State_Game.h"
#include "Questia/States/State_OptionsMenu/State_OptionsMenu.h"
#include "Questia/States/State_Loading.h"

class Application
{
public:
	//ctor + dtor
    Application();
    ~Application();
	
	//start of the application
    void run();
	
private:
	Engine eng;
};
#endif // APPLICATION_H
 