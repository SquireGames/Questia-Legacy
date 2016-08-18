#ifndef OPTIONMANAGER_H
#define OPTIONMANAGER_H

#include <vector>

#include "Option.h"
#include "Option_Base.h"

#include "SaveFile_Options.h"

#include "GuiManager.h"

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
    OptionManager(GuiManagerNew* _guiManager);
    ~OptionManager();

    void addOption(Option_Base* option);
    void initLists();

    void saveOptions(SaveFile_Options& saveFile);

    bool handleGui();

private:
    GuiManagerNew* guiManager;

    void updateArrows();

    std::vector <std::pair <Option_Base*, OptionData> > optionVector;
};

#endif // OPTIONMANAGER_H