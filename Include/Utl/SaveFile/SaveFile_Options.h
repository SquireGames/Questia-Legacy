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
    char getKey_MoveUp();
    char getKey_MoveDown();
    char getKey_MoveLeft();
    char getKey_MoveRight();
    char getKey_skill_1();
    char getKey_skill_2();
    char getKey_skill_3();
    char getKey_skill_4();
    char getKey_skill_5();
    char getKey_skill_6();

    std::string getWindowMode_name();
    std::string getFps_name();
    std::string getFont_name();
    std::string getMusicVolume_name();
    std::string getGuiPack_name();
    std::string getKey_MoveUp_name();
    std::string getKey_MoveDown_name();
    std::string getKey_MoveLeft_name();
    std::string getKey_MoveRight_name();
    std::string getKey_skill_1_name();
    std::string getKey_skill_2_name();
    std::string getKey_skill_3_name();
    std::string getKey_skill_4_name();
    std::string getKey_skill_5_name();
    std::string getKey_skill_6_name();

private:
    ///save
    SaveFile saveFile;

    ///options
    //windowMode: 0 = full-screen, 1 = 720p windowed, 2+ = 1080p windowed
    int windowMode = 0;
    //fps: -1 = Unlimited, 0 = V-Sync, 1+ = x fps
    int fps = 0;
    //font: x = font file name
    std::string font = "Lato-Regular.ttf";
    //guiPack: x = guiPack folder name
    std::string guiPack = "Default";

    //musicVolume: x = volume out of 100
    int musicVolume = 0;

    //key_x: x = key saved as char
    char key_MoveUp    = 'w';
    char key_MoveDown  = 's';
    char key_MoveLeft  = 'a';
    char key_MoveRight = 'd';
    char key_skill_1 = 30;
    char key_skill_2 = 31;
    char key_skill_3 = 4;
    char key_skill_4 = ' ';
    char key_skill_5 = 'q';
    char key_skill_6 = 'e';

    ///option names
    const std::string windowMode_name  = "Window Setting";
    const std::string fps_name         = "Frames Per Second";
    const std::string font_name        = "Font";
    const std::string guiPack_name     = "Gui Pack";
    const std::string musicVolume_name = "Music Volume";

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
