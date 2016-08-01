#include "SaveFile_Options.h"

SaveFile_Options::SaveFile_Options():
    windowMode(0)
    , fps(0)
    , font("Lato-Regular.ttf")
    , musicVolume(0)
    , guiPack("Default")
{
    saveFile.setFilePath("options.cfg");

    if(!utl::doesExist("options.cfg"))
    {
        writeOptions();
    }

    reloadOptions();
}

SaveFile_Options::~SaveFile_Options()
{

}

void SaveFile_Options::reloadOptions()
{
    saveFile.readFile();
    if(utl::isNumber(saveFile.getItem(windowModeName)))
    {
        windowMode = utl::asInt(saveFile.getItem(windowModeName));
    }
    if(utl::isNumber(saveFile.getItem(fpsName)))
    {
        fps = utl::asInt(saveFile.getItem(fpsName));
    }
    if(saveFile.getItem(fontName) != "nil")
    {
        font = saveFile.getItem(fontName);
    }
    if(utl::isNumber(saveFile.getItem(musicVolumeName)))
    {
        musicVolume = utl::asInt(saveFile.getItem(musicVolumeName));
    }
    if(saveFile.getItem(guiPackName) != "nil")
    {
        guiPack = saveFile.getItem(guiPackName);
    }
}

void SaveFile_Options::saveOption(Option_Base* option, std::string optionName)
{
    if(optionName == windowModeName)
    {
        if(utl::isNumber(option->getValueString()))
        {
            windowMode = utl::asInt(option->getValueString());
        }
    }
    else if(optionName == fpsName)
    {
        if(utl::isNumber(option->getValueString()))
        {
            fps = utl::asInt(option->getValueString());
        }
    }
    else if(optionName == fontName)
    {
        font = option->getValueString();
    }
    else if(optionName == musicVolumeName)
    {
        if(utl::isNumber(option->getValueString()))
        {
            musicVolume = utl::asInt(option->getValueString());
        }
    }
    else if(optionName == guiPackName)
    {
        guiPack = option->getValueString();
    }
}


void SaveFile_Options::writeOptions()
{
    saveFile.clearSave();

    saveFile.saveItem(windowModeName, windowMode);
    saveFile.saveItem(fpsName, fps);
    saveFile.saveItem(fontName, font);
    saveFile.saveItem(musicVolumeName, musicVolume);
    saveFile.saveItem(guiPackName, guiPack);

    saveFile.writeFile();
}

int SaveFile_Options::getWindowMode()
{
    return windowMode;
}
int SaveFile_Options::getFps()
{
    return fps;
}
std::string SaveFile_Options::getFont()
{
    return font;
}
int SaveFile_Options::getMusicVolume()
{
    return musicVolume;
}
std::string SaveFile_Options::getGuiPack()
{
    return guiPack;
}
std::string SaveFile_Options::getWindowModeName()
{
    return windowModeName;
}
std::string SaveFile_Options::getFpsName()
{
    return fpsName;
}
std::string SaveFile_Options::getFontName()
{
    return fontName;
}
std::string SaveFile_Options::getMusicName()
{
    return musicVolumeName;
}
std::string SaveFile_Options::getGuiPackName()
{
    return guiPackName;
}
