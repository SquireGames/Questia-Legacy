#include "SaveFile_Options.h"

SaveFile_Options::SaveFile_Options()
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
    if(utl::isNumber(saveFile.getItem(key_MoveUp_name)))
    {
        key_MoveUp = utl::asInt(saveFile.getItem(key_MoveUp_name));
    }
    if(utl::isNumber(saveFile.getItem(key_MoveDown_name)))
    {
        key_MoveDown = utl::asInt(saveFile.getItem(key_MoveDown_name));
    }
    if(utl::isNumber(saveFile.getItem(key_MoveLeft_name)))
    {
        key_MoveLeft = utl::asInt(saveFile.getItem(key_MoveLeft_name));
    }
    if(utl::isNumber(saveFile.getItem(key_MoveRight_name)))
    {
        key_MoveRight = utl::asInt(saveFile.getItem(key_MoveRight_name));
    }
    if(utl::isNumber(saveFile.getItem(key_skill_1_name)))
    {
        key_skill_1 = utl::asInt(saveFile.getItem(key_skill_1_name));
    }
    if(utl::isNumber(saveFile.getItem(key_skill_2_name)))
    {
        key_skill_2 = utl::asInt(saveFile.getItem(key_skill_2_name));
    }
    if(utl::isNumber(saveFile.getItem(key_skill_3_name)))
    {
        key_skill_3 = utl::asInt(saveFile.getItem(key_skill_3_name));
    }
    if(utl::isNumber(saveFile.getItem(key_skill_4_name)))
    {
        key_skill_4 = utl::asInt(saveFile.getItem(key_skill_4_name));
    }
    if(utl::isNumber(saveFile.getItem(key_skill_5_name)))
    {
        key_skill_5 = utl::asInt(saveFile.getItem(key_skill_5_name));
    }
    if(utl::isNumber(saveFile.getItem(key_skill_6_name)))
    {
        key_skill_6 = utl::asInt(saveFile.getItem(key_skill_6_name));
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
    else if(optionName == key_MoveUp_name)
    {
        key_MoveUp = static_cast <char> (option->getValueString().at(0));
    }
    else if(optionName == key_MoveDown_name)
    {
        key_MoveDown = static_cast <char> (option->getValueString().at(0));
    }
    else if(optionName == key_MoveLeft_name)
    {
        key_MoveLeft = static_cast <char> (option->getValueString().at(0));
    }
    else if(optionName == key_MoveRight_name)
    {
        key_MoveRight = static_cast <char> (option->getValueString().at(0));
    }
    else if(optionName == key_skill_1_name)
    {
        key_skill_1 = static_cast <char> (option->getValueString().at(0));
    }
    else if(optionName == key_skill_2_name)
    {
        key_skill_2 = static_cast <char> (option->getValueString().at(0));
    }
    else if(optionName == key_skill_3_name)
    {
        key_skill_3 = static_cast <char> (option->getValueString().at(0));
    }
    else if(optionName == key_skill_4_name)
    {
        key_skill_4 = static_cast <char> (option->getValueString().at(0));
    }
    else if(optionName == key_skill_5_name)
    {
        key_skill_5 = static_cast <char> (option->getValueString().at(0));
    }
    else if(optionName == key_skill_6_name)
    {
        key_skill_6 = static_cast <char> (option->getValueString().at(0));
    }
}


void SaveFile_Options::writeOptions()
{
    saveFile.clearSave();

    saveFile.saveItem(windowModeName, windowMode);
    saveFile.saveItem(fpsName, fps);
    saveFile.saveItem(fontName, font);
    saveFile.saveItem(guiPackName, guiPack);

    saveFile.saveItem(musicVolumeName, musicVolume);

    saveFile.saveItem(key_MoveUp_name, static_cast <int>    (key_MoveUp));
    saveFile.saveItem(key_MoveDown_name, static_cast <int>  (key_MoveDown));
    saveFile.saveItem(key_MoveLeft_name, static_cast <int>  (key_MoveLeft));
    saveFile.saveItem(key_MoveRight_name, static_cast <int> (key_MoveRight));
    saveFile.saveItem(key_skill_1_name, static_cast <int> (key_skill_1));
    saveFile.saveItem(key_skill_2_name, static_cast <int> (key_skill_2));
    saveFile.saveItem(key_skill_3_name, static_cast <int> (key_skill_3));
    saveFile.saveItem(key_skill_4_name, static_cast <int> (key_skill_4));
    saveFile.saveItem(key_skill_5_name, static_cast <int> (key_skill_5));
    saveFile.saveItem(key_skill_6_name, static_cast <int> (key_skill_6));

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
char SaveFile_Options::getKey_MoveUp()
{
    return key_MoveUp;
}
char SaveFile_Options::getKey_MoveDown()
{
    return key_MoveDown;
}
char SaveFile_Options::getKey_MoveLeft()
{
    return key_MoveLeft;
}
char SaveFile_Options::getKey_MoveRight()
{
    return key_MoveRight;
}
char SaveFile_Options::getKey_skill_1()
{
    return key_skill_1;
}
char SaveFile_Options::getKey_skill_2()
{
    return key_skill_2;
}
char SaveFile_Options::getKey_skill_3()
{
    return key_skill_3;
}
char SaveFile_Options::getKey_skill_4()
{
    return key_skill_4;
}
char SaveFile_Options::getKey_skill_5()
{
    return key_skill_5;
}
char SaveFile_Options::getKey_skill_6()
{
    return key_skill_6;
}

std::string SaveFile_Options::getKey_MoveUp_name()
{
    return key_MoveUp_name;
}
std::string SaveFile_Options::getKey_MoveDown_name()
{
    return key_MoveDown_name;
}
std::string SaveFile_Options::getKey_MoveLeft_name()
{
    return key_MoveLeft_name;
}
std::string SaveFile_Options::getKey_MoveRight_name()
{
    return key_MoveRight_name;
}
std::string SaveFile_Options::getKey_skill_1_name()
{
    return key_skill_1_name;
}
std::string SaveFile_Options::getKey_skill_2_name()
{
    return key_skill_2_name;
}
std::string SaveFile_Options::getKey_skill_3_name()
{
    return key_skill_3_name;
}
std::string SaveFile_Options::getKey_skill_4_name()
{
    return key_skill_4_name;
}
std::string SaveFile_Options::getKey_skill_5_name()
{
    return key_skill_5_name;
}
std::string SaveFile_Options::getKey_skill_6_name()
{
    return key_skill_6_name;
}
