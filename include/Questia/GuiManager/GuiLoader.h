#ifndef GUILOADER_H
#define GUILOADER_H

#include "Questia/Utl/SaveFile/SaveFile.h"
#include "Questia/GuiManager/GuiManager.h"

#include "Questia/Utl/Utl.h"
#include "Questia/Utl/FileData.h"

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
