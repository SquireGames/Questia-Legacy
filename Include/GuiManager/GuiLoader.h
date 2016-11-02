#ifndef GUILOADER_H
#define GUILOADER_H

#include "SaveFile.h"
#include "GuiManager.h"

#include "Utl/Utl.h"
#include "FileData.h"

class GuiLoader
{
public:
    GuiLoader();
    ~GuiLoader();

    void loadGui(GuiManager& guiManager, std::string gui);
    void setGuiPack(std::string guiPack);

private:
    std::string primaryPack = "Default";
    std::string secondaryPack = "Default";

    SaveFile guiFile;

    gui::ButtonAtr getButtonAtr(std::string buttonAtr);
    gui::ButtonAtrCharacteristic getButtonAtrCharacteristic(std::string buttonAtrCharacteristic);
    gui::ButtonCharacteristic getButtonCharacteristic(std::string buttonCharacteristic);
};

#endif // GUILOADER_H
