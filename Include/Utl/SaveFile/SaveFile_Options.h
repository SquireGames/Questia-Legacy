#ifndef SAVEFILE_OPTIONS_H
#define SAVEFILE_OPTIONS_H

#include "SaveFile.h"
#include "Option_Base.h"
#include "FileData.h"
#include "Utl.h"

class SaveFile_Options
{
public:
    SaveFile_Options();
    ~SaveFile_Options();

    void saveOption(Option_Base* option, std::string optionName);
    void writeOptions();

    void reloadOptions();

    int getWindowMode();
    int getFps();
    std::string getFont();
    int getMusicVolume();
    std::string getGuiPack();

    std::string getWindowModeName();
    std::string getFpsName();
    std::string getFontName();
    std::string getMusicName();
    std::string getGuiPackName();

    std::string getMoveUpName()
    {
        return key_MoveUp_name;
    }

private:

    //save
    SaveFile saveFile;

    //options
    int windowMode;
    int fps;
    std::string font;
    int musicVolume;
    std::string guiPack;
    const std::string windowModeName  = "Window Setting";
    const std::string fpsName         = "Frames Per Second";
    const std::string fontName        = "Font";
    const std::string musicVolumeName = "Music Volume";
    const std::string guiPackName     = "Gui Pack";

    //key bindings
    const std::string key_MoveUp_name    = "Move Up";
    const std::string key_MoveDown_name  = "Move Down";
    const std::string key_MoveLeft_name  = "Move Left";
    const std::string key_MoveRight_name = "Move Right";
    const std::string key_skill_1_name = "Skill 1";
    const std::string key_skill_2_name = "Skill 2";
    const std::string key_skill_3_name = "Skill 3";
    const std::string key_skill_4_name = "Skill 4";
    const std::string key_skill_5_name = "Skill 5";
    const std::string key_skill_6_name = "Skill 6";
};

#endif // SAVEFILE_OPTIONS_H
