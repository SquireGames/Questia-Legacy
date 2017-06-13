#ifndef OPTIONSMANAGER_H
#define OPTIONSMANAGER_H

#include <string>
#include <list>

#include "QuestiaEng/Utl/Controls/Input.h"
#include "QuestiaEng/GuiManager/GuiManager.h"
#include "QuestiaEng/SV_Options.h"

enum class OptionType {choice, functional, input};

class Option_Base
{
public:
	Option_Base() = default;
	virtual ~Option_Base() = default;

	virtual std::string getValueString() = 0;

	virtual OptionType getType() = 0;
	virtual void setInput(ctr::Input input) = 0;

	virtual bool isChanged() = 0;

	virtual std::string getList() = 0;
	virtual void setList(std::string) = 0;

	virtual void iterateForward() = 0;
	virtual void iterateBackward() = 0;
	virtual void callFunction() = 0;

	virtual bool isEnd() = 0;
	virtual bool isBegin() = 0;

	virtual std::string* getDisplayString() = 0;
	virtual std::string getOptionName() = 0;
};

template <class T>
class Option : public Option_Base
{
public:
	Option();

	//generic
	void setType(OptionType optionType);
	void setOptionName(std::string optionName);
	void setList(std::string listName);

	T getValue();
	std::string getList();
	std::string getOptionName();
	std::string getValueString();
	std::string* getDisplayString();
	OptionType getType();

	void init(T value);
	bool isChanged();

	//choice
	void addChoice(std::pair <std::string, T> option);
	void setChoices(std::list <std::pair <std::string, T> > choiceList);
	void iterateForward();
	void iterateBackward();
	bool isEnd();
	bool isBegin();

	//functional
	void callFunction();

	//input
	void setInput(ctr::Input input);

private:
	//options
	T oldOption;
	T newOption;
	std::string visibleOption = "NONE";
	std::string optionName = "NONE";

	OptionType optionType = OptionType::choice;

	//list
	std::string listName = "nil";

	//choices
	std::list <std::pair <std::string, T> > choiceList;
	typename std::list <std::pair <std::string, T> >::iterator choiceIterator = choiceList.begin();
};

struct ButtonData
{
	std::string buttonName = "nil";
	bool isActive = false;
};

struct OptionData
{
	ButtonData leftButton;
	ButtonData rightButton;
	ButtonData functionButton;

	std::string textButtonName = "nil";
	std::string* displayString = nullptr;
};

class OptionManager
{
public:
	//ctor and dtor
	OptionManager(GuiManager* guiManager);
	~OptionManager();

	void addOption(Option_Base* option);
	void initLists();

	void saveOptions(SV_Options& saveFile);

	bool handleGui();
	void handleInput(ctr::Input input);

	void setMouseReleased();
	void checkMouseInput();

	bool isMouseOverAssignedInput();
	void resetClicks() {mouseReleases = 1;};

private:
	GuiManager* guiManager;

	void initSprites();
	void updateArrows();
	std::string assignInput = "nil";

	std::vector <std::pair <Option_Base*, OptionData> > optionVector;

	bool mouseReleases = 0;
};


#endif // OPTIONSMANAGER_H
