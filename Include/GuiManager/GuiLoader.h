#ifndef GUILOADER_H
#define GUILOADER_H

#include "SaveFile.h"
#include "GuiManager.h"

#include "Utl/Utl.h"

class GuiLoader
{
public:
    GuiLoader();
    ~GuiLoader();

    void loadGui(GuiManagerNew& guiManager, std::string gui);

private:
    std::string primaryPack = "Default";
    std::string secondaryPack = "nil";

    SaveFile guiFile;

    gui::ButtonAtr getButtonAtr(std::string buttonAtr);
    gui::ButtonAtrCharacteristic getButtonAtrCharacteristic(std::string buttonAtrCharacteristic);
    gui::ButtonCharacteristic getButtonCharacteristic(std::string buttonCharacteristic);
};

#endif // GUILOADER_H
