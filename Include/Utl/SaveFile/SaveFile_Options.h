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

    std::string getWindowModeName();
    std::string getFpsName();
    std::string getFontName();
    std::string getMusicName();

private:

    //save
    SaveFile saveFile;

    //options
    int windowMode;
    int fps;
    std::string font;
    int musicVolume;
    const std::string windowModeName = "Window Setting";
    const std::string fpsName = "Frames Per Second";
    const std::string fontName = "Font";
    const std::string musicVolumeName = "Music Volume";
};

#endif // SAVEFILE_OPTIONS_H
