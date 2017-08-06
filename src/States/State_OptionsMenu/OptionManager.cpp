#include "Questia/States/State_OptionsMenu/OptionManager.h"

//TODO possible class overhaul

template <class T>
Option<T>::Option()
{

}

template <class T>
void Option<T>::setType(OptionType optionType)
{
    this->optionType = optionType;
}

template <class T>
void Option<T>::init(T value)
{
    oldOption = value;
    newOption = value;

    switch (optionType)
    {
    case OptionType::choice:
    {
        for (auto it = choiceList.begin(); it != choiceList.end(); it++)
        {
            if(it->second == value)
            {
                choiceIterator = it;
                visibleOption = it->first;
                break;
            }
        }
    }
    break;
    case OptionType::functional:
        break;
    case OptionType::input:
        visibleOption = ctr::getInputName(value);
        break;
    }
}
template <>
void Option<std::string>::init(std::string value)
{
    oldOption = value;
    newOption = value;

    switch (optionType)
    {
    case OptionType::choice:
    {
        for (auto it = choiceList.begin(); it != choiceList.end(); it++)
        {
            if(it->second == value)
            {
                choiceIterator = it;
                visibleOption = it->first;
                break;
            }
        }
    }
    break;
    case OptionType::functional:
        break;
    case OptionType::input:
        visibleOption = value;
        break;
    }
}

template <class T>
bool Option<T>::isChanged()
{
    return (oldOption != newOption);
}

template <class T>
void Option<T>::setOptionName (std::string optionName)
{
    this->optionName = optionName;
}

template <class T>
std::string Option<T>::getOptionName()
{
    return optionName;
}

template <class T>
T Option<T>::getValue()
{
    return newOption;
}

template <>
std::string Option<std::string>::getValueString()
{
    return newOption;
}

template <class T>
std::string Option<T>::getValueString()
{
    return std::to_string(newOption);
}

template <>
std::string Option<ctr::Input>::getValueString()
{
    return std::to_string(static_cast<int>(newOption));
}

template <class T>
void Option<T>::addChoice (std::pair <std::string, T> option)
{
    choiceList.push_back(option);
}

template <class T>
void Option<T>::setChoices (std::list <std::pair <std::string, T> > choiceList)
{
    this->choiceList = choiceList;
}

template <class T>
void Option<T>::setList(std::string listName)
{
    this->listName = listName;
}

template <class T>
std::string Option<T>::getList()
{
    return listName;
}

template <class T>
std::string* Option<T>::getDisplayString()
{
    return &visibleOption;
}

template <class T>
OptionType Option<T>::getType()
{
    return optionType;
}

template <class T>
void Option<T>::iterateForward()
{
    if(choiceIterator != --choiceList.end())
    {
        choiceIterator++;
        visibleOption = choiceIterator->first;

        newOption = choiceIterator->second;
    }
}

template <class T>
void Option<T>::iterateBackward()
{
    if(choiceIterator != choiceList.begin())
    {
        choiceIterator--;
        visibleOption = choiceIterator->first;
        newOption = choiceIterator->second;
    }
}

template <class T>
bool Option<T>::isEnd()
{
    if(choiceIterator == --choiceList.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool Option<T>::isBegin()
{
    if(choiceIterator == choiceList.begin())
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
void Option<T>::callFunction()
{
    //not implemented
}

template <class T>
void Option<T>::setInput(ctr::Input input)
{

}

template <>
void Option<ctr::Input>::setInput(ctr::Input input)
{
    visibleOption = ctr::getInputName(input);
    newOption = input;
}

template class Option<bool>;
template class Option<char>;
template class Option<int>;
template class Option<float>;
template class Option<std::string>;
template class Option<ctr::Input>;

OptionManager::OptionManager(GuiManager* guiManager):
    guiManager(guiManager)
{

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
			GuiBuilder& guiBuilder = guiManager->edit();
			
            std::string groupName = guiBuilder.createListEntry(option.first->getList());

            option.second.leftButton.buttonName =     guiBuilder.getGroupEntry(groupName, "leftButton");
            option.second.rightButton.buttonName =    guiBuilder.getGroupEntry(groupName, "rightButton");
            option.second.functionButton.buttonName = guiBuilder.getGroupEntry(groupName, "funcButton");

            switch (option.first->getType())
            {
            case OptionType::choice:
                option.second.leftButton.isActive =     (option.second.leftButton.buttonName !=     "nil");
                option.second.rightButton.isActive =    (option.second.rightButton.buttonName !=    "nil");
                break;
            case OptionType::functional:
            case OptionType::input:
                option.second.functionButton.isActive = (option.second.functionButton.buttonName != "nil");
                break;
            }

            option.second.textButtonName = guiBuilder.getGroupEntry(groupName, "optionValue");
            option.second.displayString  = option.first->getDisplayString();

            std::string optionButtonName = guiBuilder.getGroupEntry(groupName, "optionName");

            guiBuilder.setBtnAtr(option.second.textButtonName, "text", gui::BtnAtrChar::text, *option.second.displayString);
            guiBuilder.setBtnAtr(optionButtonName, "text", gui::BtnAtrChar::text, option.first->getOptionName());
        }
    }
    initSprites();
    updateArrows();
}

bool OptionManager::handleGui()
{
	GuiBuilder& guiBuilder = guiManager->edit();
	
    //triggered on click
    for(const auto& option : optionVector)
    {
        if(option.second.leftButton.isActive)
        {
            if(guiManager->isHovered(option.second.leftButton.buttonName))
            {
                option.first->iterateBackward();
                guiBuilder.setBtnAtr(option.second.textButtonName, "text", gui::BtnAtrChar::text, *option.second.displayString);

                updateArrows();
                return true;
            }
        }
        if(option.second.rightButton.isActive)
        {
            if(guiManager->isHovered(option.second.rightButton.buttonName))
            {
                option.first->iterateForward();
                guiBuilder.setBtnAtr(option.second.textButtonName, "text", gui::BtnAtrChar::text, *option.second.displayString);

                updateArrows();
                return true;
            }
        }
        if(option.second.functionButton.isActive)
        {
            if(assignInput == option.second.textButtonName)
            {
                if(!guiManager->isHovered(option.second.functionButton.buttonName))
                {
                    assignInput = "nil";
                    return true;
                }
            }
            else if(guiManager->isHovered(option.second.functionButton.buttonName))
            {
                assignInput = option.second.textButtonName;
                return true;
            }
        }
    }
    return false;
}

void OptionManager::initSprites()
{
	GuiBuilder& guiBuilder = guiManager->edit();
	
    for(const auto& option : optionVector)
    {
        switch(option.first->getType())
        {
        case OptionType::choice:
            guiBuilder.setButton(option.second.functionButton.buttonName, gui::BtnChar::isActive, false);
            guiBuilder.setBtnAtr(option.second.functionButton.buttonName,  "funcSprite", gui::BtnAtrChar::transparency, 0);
            break;
        case OptionType::functional:
        case OptionType::input:
            guiBuilder.setButton(option.second.leftButton.buttonName, gui::BtnChar::isActive, false);
            guiBuilder.setButton(option.second.rightButton.buttonName, gui::BtnChar::isActive, false);
            guiBuilder.setBtnAtr(option.second.leftButton.buttonName,  "arrowSprite", gui::BtnAtrChar::transparency, 0);
            guiBuilder.setBtnAtr(option.second.rightButton.buttonName, "arrowSprite", gui::BtnAtrChar::transparency, 0);
            break;
        }
    }
}

void OptionManager::updateArrows()
{
	GuiBuilder& guiBuilder = guiManager->edit();
	
    for(const auto& option : optionVector)
    {
        if(option.first->getType() == OptionType::choice)
        {
            if(option.first->isBegin() && option.first->isEnd())
            {
                guiBuilder.setBtnAtr(option.second.leftButton.buttonName,  "arrowSprite", gui::BtnAtrChar::transparency, 0);
                guiBuilder.setBtnAtr(option.second.rightButton.buttonName, "arrowSprite", gui::BtnAtrChar::transparency, 0);
            }
            else if(option.first->isBegin())
            {
                guiBuilder.setBtnAtr(option.second.leftButton.buttonName,  "arrowSprite", gui::BtnAtrChar::transparency, 0);
                guiBuilder.setBtnAtr(option.second.rightButton.buttonName, "arrowSprite", gui::BtnAtrChar::transparency, 100);
            }
            else if(option.first->isEnd())
            {
                guiBuilder.setBtnAtr(option.second.leftButton.buttonName,  "arrowSprite", gui::BtnAtrChar::transparency, 100);
                guiBuilder.setBtnAtr(option.second.rightButton.buttonName, "arrowSprite", gui::BtnAtrChar::transparency, 0);
            }
            else
            {
                guiBuilder.setBtnAtr(option.second.leftButton.buttonName,  "arrowSprite", gui::BtnAtrChar::transparency, 100);
                guiBuilder.setBtnAtr(option.second.rightButton.buttonName, "arrowSprite", gui::BtnAtrChar::transparency, 100);
            }
        }
    }
}

void OptionManager::saveOptions(SV_Options& saveFile)
{
    for(const auto& it : optionVector)
    {
        if(it.first->isChanged())
        {
            saveFile.saveOption(it.first->getOptionName(), it.first->getValueString());
        }
    }
}

void OptionManager::handleInput(ctr::Input input)
{
    if(assignInput != "nil")
    {
        for(auto& option : optionVector)
        {
            if((option.second.textButtonName == assignInput) &&
                    option.first->getType() == OptionType::input &&
                    guiManager->isHovered(option.second.functionButton.buttonName))
            {
                option.first->setInput(input);
                guiManager->edit().setBtnAtr(option.second.textButtonName, "text", gui::BtnAtrChar::text, *option.second.displayString);
                return;
            }
        }
        assignInput = "nil";
    }
}

bool OptionManager::isMouseOverAssignedInput()
{
    if(assignInput != "nil")
    {
        for(const auto& option : optionVector)
        {
            if(option.second.functionButton.isActive)
            {
                if(assignInput == option.second.textButtonName)
                {
                    if(guiManager->isHovered(option.second.functionButton.buttonName))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void OptionManager::setMouseReleased()
{
    if(isMouseOverAssignedInput())
    {
        mouseReleases++;
        return;
    }
    mouseReleases = 0;
}

void OptionManager::checkMouseInput()
{
    if(mouseReleases >= 1 && (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)||
                              sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)||
                              sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)||
                              sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton1)||
                              sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton2)))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            handleInput(ctr::Input::LMouse);
        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        {
            handleInput(ctr::Input::RMouse);
        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
        {
            handleInput(ctr::Input::MMouse);
        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton1))
        {
            handleInput(ctr::Input::Macro1);
        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton2))
        {
            handleInput(ctr::Input::Macro2);
        }
        mouseReleases = 0;
    }
}

