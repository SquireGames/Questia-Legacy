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
    void handleInput(char input);

    void setMouseReleased();
    void checkMouseInput();

    bool isMouseOverAssignedInput();

private:
    GuiManagerNew* guiManager;

    void initSprites();
    void updateArrows();
    std::string assignInput = "nil";

    std::vector <std::pair <Option_Base*, OptionData> > optionVector;

    bool mouseReleases = 0;
};

#endif // OPTIONMANAGER_H
