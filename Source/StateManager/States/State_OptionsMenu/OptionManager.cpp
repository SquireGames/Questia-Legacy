#include "OptionManager.h"

OptionManager::OptionManager(GuiManagerNew* _guiManager):
    guiManager(_guiManager)
{
    if(guiManager == nullptr)
    {
        throw std::runtime_error ("OptionManager does not have access to GuiManager");
    }
}

OptionManager::~OptionManager()
{
    //do nothing with option_base
}

void OptionManager::addOption(Option_Base* option)
{
    optionVector.push_back(std::make_pair(option, OptionData()));
}

void OptionManager::initLists()
{
    for(auto& option : optionVector)
    {
        if(option.first->getList() != "nil")
        {
            std::string groupName = guiManager->createListEntry(option.first->getList());

            option.second.leftButton.buttonName =     guiManager->getGroupEntry(groupName, "leftButton");
            option.second.rightButton.buttonName =    guiManager->getGroupEntry(groupName, "rightButton");
            option.second.functionButton.buttonName = guiManager->getGroupEntry(groupName, "????????");

            option.second.leftButton.isActive = (option.second.leftButton.buttonName == "nil") ? false : true;
            option.second.rightButton.isActive = (option.second.rightButton.buttonName == "nil") ? false : true;
            option.second.functionButton.isActive = (option.second.functionButton.buttonName == "nil") ? false : true;

            option.second.textButtonName = guiManager->getGroupEntry(groupName, "optionValue");
            option.second.displayString  = option.first->getDisplayString();

            std::string optionButtonName = guiManager->getGroupEntry(groupName, "optionName");

            guiManager->setButtonAtr(option.second.textButtonName, "text", gui::ButtonAtrCharacteristic::text, *option.second.displayString);
            guiManager->setButtonAtr(optionButtonName, "text", gui::ButtonAtrCharacteristic::text, option.first->getOptionName());
        }
    }
    updateArrows();
}

bool OptionManager::handleGui()
{
    for(const auto& option : optionVector)
    {
        if(option.second.leftButton.isActive)
        {
            if(guiManager->isClicked(option.second.leftButton.buttonName))
            {
                option.first->iterateBackward();
                guiManager->setButtonAtr(option.second.textButtonName, "text", gui::ButtonAtrCharacteristic::text, *option.second.displayString);

                updateArrows();
                return true;
            }
        }

        if(option.second.rightButton.isActive)
        {
            if(guiManager->isClicked(option.second.rightButton.buttonName))
            {
                option.first->iterateForward();
                guiManager->setButtonAtr(option.second.textButtonName, "text", gui::ButtonAtrCharacteristic::text, *option.second.displayString);

                updateArrows();
                return true;
            }
        }
    }
    return false;
}

void OptionManager::updateArrows()
{
    for(const auto& option : optionVector)
    {
        if(option.first->isBegin() && option.first->isEnd())
        {
            guiManager->setButtonAtr(option.second.leftButton.buttonName,  "arrowSprite", gui::ButtonAtrCharacteristic::transparency, 0);
            guiManager->setButtonAtr(option.second.rightButton.buttonName, "arrowSprite", gui::ButtonAtrCharacteristic::transparency, 0);
        }
        else if(option.first->isBegin())
        {
            guiManager->setButtonAtr(option.second.leftButton.buttonName,  "arrowSprite", gui::ButtonAtrCharacteristic::transparency, 0);
            guiManager->setButtonAtr(option.second.rightButton.buttonName, "arrowSprite", gui::ButtonAtrCharacteristic::transparency, 100);
        }
        else if(option.first->isEnd())
        {
            guiManager->setButtonAtr(option.second.leftButton.buttonName,  "arrowSprite", gui::ButtonAtrCharacteristic::transparency, 100);
            guiManager->setButtonAtr(option.second.rightButton.buttonName, "arrowSprite", gui::ButtonAtrCharacteristic::transparency, 0);
        }
        else
        {
            guiManager->setButtonAtr(option.second.leftButton.buttonName,  "arrowSprite", gui::ButtonAtrCharacteristic::transparency, 100);
            guiManager->setButtonAtr(option.second.rightButton.buttonName, "arrowSprite", gui::ButtonAtrCharacteristic::transparency, 100);
        }
    }
}
